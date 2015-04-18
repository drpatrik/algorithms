// Monty Hall Simulation
// Patrik Tennberg, 2014

#include <random>
#include <vector>
#include <string>
#include <algorithm>

const size_t N = 1000000;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("you must specify number of doors\n");
    return -1;
  }
  const size_t n_doors = std::stoll(argv[1], 0, 10);

  if (n_doors < 3) {
    printf("must be at least 3 doors\n");
    return -1;
  }
  std::mt19937 engine {std::random_device{}()};
  std::uniform_int_distribution<size_t> distribution {0, n_doors - 1};

  size_t change = 0, stay = 0;
  std::vector<bool> doors(n_doors, false);

  srand(time(NULL));
  doors[0] = true;
  for (size_t i = 0; i < N; i++) {
    std::random_shuffle(std::begin(doors), std::end(doors));
    // contestant's first choice
    const size_t first_choice = distribution(engine);

    // game host opens a goat door
    size_t open_door = 0;

    while (doors[open_door] || open_door == first_choice) {
      open_door++;
    }
    // contestant change door
    size_t second_choice;

    do {
      second_choice = distribution(engine);
    } while (second_choice == first_choice || second_choice == open_door);

    stay += doors[first_choice];
    change += doors[second_choice];
  }
  printf("%2.5f > %2.5f\n", double(change) / N, double(stay) / N);

  return 0;
}
