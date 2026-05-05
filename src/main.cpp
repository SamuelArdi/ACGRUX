#include <cstddef>
#include <iostream>
#include <string>

#include "FL/Fl_Double_Window.H"
#include "FL/Fl_Flex.H"
#include "FL/Fl_Check_Button.H"
#include "FL/Fl_Button.H"
#include "FL/Fl_Widget.H"
#include "FL/Fl_Hor_Value_Slider.H"
#include "FL/Fl_Output.H"
#include "FL/Fl_Multiline_Output.H"
#include "FL/Enumerations.H"

#include "../lib/generator.hpp"
#include "../lib/profile.hpp"

struct WIDGET_SIZES {
  int x; int w;
  int y; int h;
} Options, Ballast, Profile, FileOps, Generate, Output;

auto setWidgetSizes(Fl_Widget* widget, WIDGET_SIZES& widgetClass) {
  widgetClass.x = widget->x();
  widgetClass.y = widget->y();

  widgetClass.w = widget->w();
  widgetClass.h = widget->h();
}

// TODO: use constants for widget placements

// window
Fl_Double_Window* AppWindow;
auto buildWindow() -> void {
  const auto WINDOW_WIDTH = 360;
  const auto WINDOW_HEIGHT = 256;

  AppWindow = new Fl_Double_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Assetto Corsa T&C Generator: Revitalized UX");
  AppWindow->xclass("acgrux");
}

// options
auto buildOptions() -> void {
  auto* options = new Fl_Flex(5, 5, 135, 100, Fl_Flex::VERTICAL);

  Opts::tougesOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Touge");
  Opts::tougeCarsOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Touge Cars");

  Opts::circuitsOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Circuit");
  Opts::circuitCarsOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Circuit Cars");

  Opts::specialOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Special");
  Opts::ballastOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Ballast");

  // default them to true except ballast
  Opts::tougesOpt->value(1);
  Opts::tougeCarsOpt->value(1);

  Opts::circuitsOpt->value(1);
  Opts::circuitCarsOpt->value(1);

  Opts::specialOpt->value(1);

  options->gap(5);
  options->end();

  setWidgetSizes(options, Options);
}

// ballast
Fl_Hor_Value_Slider* ballastSlider;
auto buildBallast() -> void {
  auto* ballast = new Fl_Flex(Options.w + 10, 5, 210, 35, Fl_Flex::HORIZONTAL);

  ballastSlider = new Fl_Hor_Value_Slider(0, 0, 0, 0, "Set Ballast");
  ballastSlider->step(1);
  ballastSlider->bounds(1, 200);
  ballastSlider->value(1);
  ballastSlider->deactivate(); // off by default

  Opts::ballastOpt->callback([](Fl_Widget* w, void* d)-> void  {
    auto currentState = Opts::ballastOpt->value();
    if (currentState == 0) {
      ballastSlider->deactivate();
    } else {
      ballastSlider->activate();
    }
  });

  ballastSlider->when(FL_WHEN_CHANGED);
  ballastSlider->callback([](Fl_Widget* w, void* d)-> void {
    GenVecs::ballast = static_cast<int>(ballastSlider->value());
  });

  ballast->end();

  setWidgetSizes(ballast, Ballast);
}

// file operations
Fl_Output* setProfile;
auto buildProfile() -> void {
  auto* profile = new Fl_Flex(Options.x, Options.h + 15, Options.w, 25, Fl_Flex::HORIZONTAL);

  setProfile = new Fl_Output(0, 0, 0, 0);
  setProfile->value("YAML Profile");
  profile->fixed(setProfile, 90);

  auto* profileSelect = new Fl_Button(0, 0, 0, 0, "Browse");
  profileSelect->callback(selectProfile, setProfile);

  profile->gap(2);
  profile->end();

  setWidgetSizes(profile, Profile);

  auto* fileOps = new Fl_Flex(Options.x, (Profile.y + Profile.h) + 5, Options.w, 105, Fl_Flex::VERTICAL);

  auto* openFile = new Fl_Button(0, 0, 0, 0, "Open YAML");
  openFile->callback(openYaml, openFile);

  auto* loadFile = new Fl_Button(0, 0, 0, 0, "Load YAML");
  loadFile->callback(loadYaml, loadFile);

  fileOps->gap(5);
  fileOps->end();

  setWidgetSizes(fileOps, FileOps);
}

Fl_Multiline_Output* output;
auto buildOutput() -> void {
  output = new Fl_Multiline_Output(Options.w + 10, (Profile.y + Generate.h) + 5, Ballast.w, (Profile.h + FileOps.h) + 7);
  output->set_output();
  output->wrap(1);

  setWidgetSizes(output, Output);
}

auto buildGenerate() -> void {
  auto* generate = new Fl_Flex(Options.w + 10, Ballast.h + 22, Ballast.w, 52, Fl_Flex::VERTICAL);

  auto* generateProfileBtn = new Fl_Button(0, 0, 0, 0, "Generate Default YAML");
  generateProfileBtn->callback(generateYaml, setProfile);

  auto* generateBtn = new Fl_Button(0, 0, 0, 0, "Generate");
  generateBtn->callback(Generator, output);

  generate->gap(2);
  generate->end();

  setWidgetSizes(generate, Generate);
}

auto main(int argc, char** argv) -> int {
  buildWindow();
  buildOptions();
  buildBallast();
  buildProfile();
  buildOutput();
  buildGenerate();
  AppWindow->end();
  AppWindow->show(argc, argv);
  return Fl::run();
}
