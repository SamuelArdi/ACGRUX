#pragma

#include <vector>
#include <string>
#include <map>

#include <FL/Fl_Widget.H>

#ifndef GENERATOR_H
#define GENERATOR_H

// TODO: Dont use Classes
class Generator {
using Vec = std::vector<std::string>;
using Map = std::map<std::string, bool>;
public:
  static auto changeState(Map& map, const std::string& val) -> void;

  auto generateTouge() -> std::string;
  auto generateTougeCar() -> std::string;

  auto generateCircuit() -> std::string;
  auto generateCircuitCars() -> std::string;

  auto generateSpecial() -> std::string;
  auto generateBallast() -> int;

private:
  std::string touge;
  char tougeID;

  Vec touges;
  Vec downhillCars;
  Vec uphillCars;

  Vec circuits;
  Vec circuitCars;

  Vec special;
  int ballast;
};

#endif
