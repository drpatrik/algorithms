// Patrik Tennberg, 2012

#include <stdlib.h>
#include <stdio.h>
#include <curand_kernel.h>

#define CudaSafeCall(err) __cudaSafeCall(err, __FILE__, __LINE__)

inline void __cudaSafeCall(cudaError err, const char *file, const int line) {
  if (cudaSuccess != err) {
    fprintf(stderr, "cudaSafeCall() failed at %s:%i : %s\n", file, line,
            cudaGetErrorString(err));
    exit(-1);
  }
  return;
}

typedef unsigned long long int uint64;

__global__ void setup_kernel(curandState *globalStates) {
  int tid = (blockIdx.x * blockDim.x) + threadIdx.x;

  curand_init(tid, tid, 0, &globalStates[tid]);
}

template <int num_threads, int points_per_thread>
__global__ void inside_circle_kernel(curandState *globalStates,
                                     uint64 *per_block_results) {
  __shared__ uint64 output[num_threads];

  const int tid = (blockIdx.x * blockDim.x) + threadIdx.x;

  curandState localState = globalStates[tid];

  uint64 inside = 0;

  for (int i = 0; i < points_per_thread; i++) {
    const float x = curand_uniform(&localState);
    const float y = curand_uniform(&localState);

    if (x * x + y * y <= 1.0) {
      inside++;
    }
  }
  globalStates[tid] = localState;
  output[threadIdx.x] = inside;
  // wait until all threads in the block have updated their partial sums
  __syncthreads();

  // thread 0 of every block writes the final result
  if (threadIdx.x == 0) {
    inside = 0;
    for (int i = 0; i < blockDim.x; i++) {
      inside += output[i];
    }
    per_block_results[blockIdx.x] = inside;
  }
}

__global__ void reduction_kernel(uint64 *result,
                                 const uint64 *per_block_results, size_t N) {
  uint64 partialSum = 0;

  for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < N;
       i += blockDim.x * gridDim.x) {
    partialSum += per_block_results[i];
  }
  atomicAdd(result, partialSum);
}

uint64 verify_result(const uint64 gpu_result, const uint64 *d_per_block_results,
                     const size_t N) {
  uint64 h_per_block_results[N];

  CudaSafeCall(cudaMemcpy(h_per_block_results, d_per_block_results,
                          sizeof(h_per_block_results), cudaMemcpyDeviceToHost));

  uint64 total_inside = 0;

  for (int i = 0; i < N; i++) {
    total_inside += h_per_block_results[i];
  }
  if (gpu_result != total_inside) {
    printf("Diff: %lld != %lld\n", gpu_result, total_inside);
  }
  return total_inside;
}

int main(void) {
  const int N = 600000;  // Total number of threads
  const int points_per_thread = 2048;
  const unsigned int num_threads = 1024;
  const unsigned int num_blocks = (N + num_threads - 1) / num_threads;
  const unsigned int red_num_blocks =
      (num_blocks + num_threads - 1) / num_threads;
  const uint64 scenarious = points_per_thread * num_threads * num_blocks;

  // Initialize curand
  curandState *d_devStates;

  CudaSafeCall(
      cudaMalloc(&d_devStates, num_blocks * num_threads * sizeof(curandState)));

  setup_kernel<<<num_blocks, num_threads>>>(d_devStates);
  CudaSafeCall(
      cudaThreadSynchronize());  // We need to wait since the kernel can timeout
                                 // Estimate Pi
  uint64 *d_per_block_results;

  CudaSafeCall(cudaMalloc(&d_per_block_results,
                          num_blocks * sizeof(*d_per_block_results)));
  CudaSafeCall(cudaMemset(d_per_block_results, 0,
                          num_blocks * sizeof(*d_per_block_results)));

  printf("Estimating PI with %lld scenarious using %u blocks and %u threads\n",
         scenarious, num_blocks, num_threads);
  inside_circle_kernel<num_threads,
                       points_per_thread><<<num_blocks, num_threads>>>(
      d_devStates, d_per_block_results);
  CudaSafeCall(cudaThreadSynchronize());
  // Reduce partial sums
  uint64 *d_total_inside;

  CudaSafeCall(cudaMalloc(&d_total_inside, sizeof(uint64)));
  CudaSafeCall(cudaMemset(d_total_inside, 0, sizeof(uint64)));

  printf("Reducing %u values, using %u block(s) and %u threads\n", num_blocks,
         red_num_blocks, num_threads);
  reduction_kernel<<<red_num_blocks, num_threads>>>(
      d_total_inside, d_per_block_results, num_blocks);
  CudaSafeCall(cudaThreadSynchronize());
  // Verify result from kernels
  uint64 total_inside = 0;

  CudaSafeCall(cudaMemcpy(&total_inside, d_total_inside, sizeof(total_inside),
                          cudaMemcpyDeviceToHost));

  verify_result(total_inside, d_per_block_results, num_blocks);
  // Display our Pi estimate
  const double pi = 4.0 * double(total_inside) / scenarious;

  printf("estimated pi = %f, expected = 3.141592653589793238462643\n", pi);

  CudaSafeCall(cudaFree(d_devStates));
  CudaSafeCall(cudaFree(d_per_block_results));
  CudaSafeCall(cudaFree(d_total_inside));

  return 0;
}