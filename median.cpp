#include <fstream>
#include <vector>
#include <memory>
#include <cassert>
#include <cstdlib>

uint64_t get_curr_tsp() {
   struct timespec ts [1];
   clock_gettime (CLOCK_REALTIME, ts);

   return ts->tv_sec * 1000000000UL + ts->tv_nsec;
}

class Array {
 public:
  explicit Array(size_t size, int* array) : head_(0), size_(size), array_(array) {}

  ~Array() noexcept { delete[] array_; }

  inline int peek() const { return (head_ != size_) ? array_[head_] : -1;  }

  inline void commit() { head_++; }

 private:
  size_t head_;
  size_t size_;
  int *array_;
};

class DataSet {
 public:
  DataSet() : total_size_(0) {}

  inline size_t total_size() const { return total_size_; }

  void append(size_t size, int* array) {
    total_size_ += size;
    arrays_.emplace_back(std::make_shared<Array>(size, array));
  }

  int next() const {
    int min = -1;
    Array* obj = nullptr;

    for (const auto& arr : arrays_) {
      if (-1 == min || arr->peek() <= min) {
        min = arr->peek();
        obj = arr.get();
      }
    }
    assert(obj != nullptr);
    obj->commit();

    return min;
  }

  auto median() const {
    int duplicates = 0;
    int current_value = 0;

    for (size_t i = 0; i < size_t(total_size_ / 2); ++i) {
      float next_value = next();

      duplicates += (current_value == next_value);
      current_value = next_value;
    }

    return std::make_pair((total_size_ % 2 == 0) ? (current_value + next()) / 2.0 : next(), duplicates);
  }

 private:
  size_t total_size_;
  std::vector<std::shared_ptr<Array>> arrays_;
};

DataSet read_files(int argc, const char* argv[]) {
  DataSet data_set;
  int size = 0;

  for (int i = 1; i < argc; ++i) {
    FILE* fp = fopen(argv[i], "r");

    if (nullptr == fp) {
      printf("File not found - %s", argv[i]);
      exit(0);
    }

    fscanf(fp, "%d", &size);
    int* arr = new int[size];

    for (int j = 0; j < size; ++j) {
      fscanf(fp, "%d", &arr[j]);
    }
    fclose(fp);
    data_set.append(size, arr);
  }

  return data_set;
}

int main(int argc, const char* argv[]) {
  auto data_set = read_files(argc, argv);

  uint64_t t1 = get_curr_tsp();

  auto [median, duplicates] = data_set.median();

  double elapsed = get_curr_tsp() - t1;

  printf("Median,n duplicates = (%.10g, %d), size = %zu\n", median, duplicates, data_set.total_size());
  printf("%.3g ns/value\n", elapsed / data_set.total_size());
}
