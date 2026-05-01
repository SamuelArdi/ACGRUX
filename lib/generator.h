#pragma

#include <vector>
#include <string>
#include <map>

#ifndef GENERATOR_H
#define GENERATOR_H

using Vec = std::vector<std::string>;
using Map = std::map<std::string, bool>;

struct GenVecs {
  Vec touges;
  Vec downhillCars;
  Vec uphillCars;

  Vec circuits;
  Vec circuitCars;

  Vec special;
  Vec ballast;
};

auto generateTouge() -> std::string;
auto generateTougeCar() -> std::string;

auto generateCircuit() -> std::string;
auto generateCircuitCars() -> std::string;

auto generateSpecial() -> std::string;
auto generateBallast() -> int;

#endif
