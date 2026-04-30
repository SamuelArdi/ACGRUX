#include <algorithm>
#include <iostream>
#include <map>

#include "FL/Fl.H"
#include "FL/Fl_Double_Window.H"
#include "FL/Fl_Flex.H"
#include "FL/Fl_Check_Button.H"
#include "FL/fl_callback_macros.H"
#include <FL/Enumerations.H>

#include "../lib/generator.h"

Fl_Double_Window* AppWindow;

auto buildWindow() -> void {
  const auto WINDOW_WIDTH = 360;
  const auto WINDOW_HEIGHT = 256;

  AppWindow = new Fl_Double_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Assetto Corsa T&C Generator: UX");
  AppWindow->xclass("acgrux");
}

auto buildOptions() -> std::map<std::string, bool> {
  auto* options = new Fl_Flex(0, 0, 135, 100, Fl_Flex::VERTICAL);

  std::map<std::string, bool> opts = {
    {"touges", false},
    {"tougeCars", false},

    {"circuits", false},
    {"circuitCars", false},

    {"special", false},
    {"ballast", false}
  };

  using Vec = std::map<std::string, bool>;
  using String = std::string;

  auto* tougesOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Touge");

  auto* tougeCarsOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Touge Cars");

  auto* circuitsOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Circuit");
  auto* circuitCarsOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Circuit Cars");

  auto* specialOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Special");

  tougesOpt->callback(Generator::changeState, (void *)this);

  options->gap(5);
  options->end();

  return opts;
}

auto main(int argc, char** argv) -> int {
  buildWindow();
  buildOptions();

  AppWindow->end();
  AppWindow->show(argc, argv);
  return Fl::run();
}
