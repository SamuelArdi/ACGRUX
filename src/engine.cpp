#include "../lib/engine.hpp"

auto vectorRng(std::vector<std::string> v) -> std::string {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<> dist(0, v.size() - 1);

  std::uniform_int_distribution<> shuffle(1, 7);
  for (int i = 0; i < shuffle(gen); ++i) {
    std::shuffle(v.begin(), v.end(), gen);
  }
  return v[dist(gen)];
}

auto ballastRng(int max) -> int {
  auto seedSeq = []() -> std::seed_seq {
    std::random_device src;
    unsigned int random_data[10];
    for (auto& elem : random_data) {
      elem = src();
    }
    return std::seed_seq(random_data + 0, random_data + 10);
  };

  auto seed = seedSeq();
  std::default_random_engine gen(seed);
  std::uniform_int_distribution<> dist(1, max);
  return dist(gen);
};

auto boolRng() -> bool {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<> dist(0, 1);
  return static_cast<bool>(dist(gen));
}

auto useSpecial() -> bool {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::discrete_distribution<> dist({0.425, 0.425, 0.15});
  return (dist(gen) + 1) == 3;
}
