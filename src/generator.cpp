#include "../lib/generator.h"

using Vec = std::vector<std::string>;
using Map = std::map<std::string, bool>;

auto Generator::changeState(Map& map, const std::string& val) -> void {
  bool state = map[val];
  map[val] = !state;
}
