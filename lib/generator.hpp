#pragma

#include <vector>
#include <string>
#include <map>

#include "FL/fl_ask.H"
#include "FL/Fl_Widget.H"
#include "FL/Fl_Check_Button.H"
#include "FL/Fl_Hor_Value_Slider.H"

#ifndef GENERATOR_HPP
#define GENERATOR_HPP

using Vec = std::vector<std::string>;
using Map = std::map<std::string, bool>;

struct Opts {
  inline static Fl_Check_Button* tougesOpt;
  inline static Fl_Check_Button* tougeCarsOpt;

  inline static Fl_Check_Button* circuitsOpt;
  inline static Fl_Check_Button* circuitCarsOpt;

  inline static Fl_Check_Button* specialOpt;
  inline static Fl_Check_Button* ballastOpt;
};

struct GenVecs {
  inline static Vec touges;
  inline static Vec downhillCars;
  inline static Vec uphillCars;

  inline static Vec circuits;
  inline static Vec circuitCars;

  inline static Vec special;
  inline static int ballast;
};

struct GenHelper {
  inline static char tougeID;
};

auto generateTouge() -> std::string;
auto generateTougeCar() -> std::string;

auto generateCircuit() -> std::string;
auto generateCircuitCar() -> std::string;

auto generateSpecial() -> std::string;
auto generateBallast(Fl_Widget* w, void* d) -> int;

auto Generator(Fl_Widget* w, void* d) -> void;

#endif
