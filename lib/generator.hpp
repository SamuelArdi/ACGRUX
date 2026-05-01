#pragma

#include <vector>
#include <string>
#include <map>

#ifndef GENERATOR_HPP
#define GENERATOR_HPP

using Vec = std::vector<std::string>;
using Map = std::map<std::string, bool>;

struct GenVecs {
  inline static Vec touges;
  inline static Vec downhillCars;
  inline static Vec uphillCars;

  inline static Vec circuits;
  inline static Vec circuitCars;

  inline static Vec special;
  inline static int ballast;
};

auto generateTouge() -> std::string;
auto generateTougeCar() -> std::string;

auto generateCircuit() -> std::string;
auto generateCircuitCars() -> std::string;

auto generateSpecial() -> std::string;
auto generateBallast() -> int;

#endif
