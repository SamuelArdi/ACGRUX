#include "FL/Fl_Double_Window.H"
#include "FL/Fl_Flex.H"
#include "FL/Fl_Check_Button.H"
#include "FL/Fl_Button.H"
#include "FL/Fl_Widget.H"
#include "FL/Fl_Hor_Value_Slider.H"
#include "FL/Fl_Input.H"
#include "FL/Fl_Box.H"

#include "../lib/generator.h"

struct WIDGET_SIZES {
  int x; int w;
  int y; int h;
} Options, Ballast, FileOps;

auto setWidgetSizes(Fl_Widget* widget, WIDGET_SIZES& widgetClass) {
  widgetClass.x = widget->x();
  widgetClass.y = widget->y();

  widgetClass.w = widget->w();
  widgetClass.h = widget->h();
}

// window
Fl_Double_Window* AppWindow;
auto buildWindow() -> void {
  const auto WINDOW_WIDTH = 360;
  const auto WINDOW_HEIGHT = 256;

  AppWindow = new Fl_Double_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Assetto Corsa T&C Generator: Revitalized UX");
  AppWindow->xclass("acgrux");
}

// options
struct opts {
  Fl_Check_Button* tougesOpt;
  Fl_Check_Button* tougeCarsOpt;

  Fl_Check_Button* circuitsOpt;
  Fl_Check_Button* circuitCarsOpt;

  Fl_Check_Button* specialOpt;
  Fl_Check_Button* ballastOpt;
};
opts opt;

auto buildOptions() -> void {
  auto* options = new Fl_Flex(0, 0, 135, 100, Fl_Flex::VERTICAL);

  opt.tougesOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Touge");
  opt.tougeCarsOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Touge Cars");

  opt.circuitsOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Circuit");
  opt.circuitCarsOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Circuit Cars");

  opt.specialOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Special");
  opt.ballastOpt = new Fl_Check_Button(0, 0, 0, 0, "Enable Ballast");

  options->gap(5);
  options->end();

  setWidgetSizes(options, Options);
}

// ballast
Fl_Hor_Value_Slider* ballastSlider;
auto buildBallast() -> void {
  auto* ballast = new Fl_Flex(Options.w + 10, 0, 205, 35, Fl_Flex::HORIZONTAL);

  ballastSlider = new Fl_Hor_Value_Slider(0, 0, 0, 0, "Set Ballast");
  ballastSlider->step(1);
  ballastSlider->bounds(1, 200);
  ballastSlider->value(1);
  ballastSlider->deactivate(); // off by default

  opt.ballastOpt->callback([](Fl_Widget* w, void* d) {
    auto currentState = opt.ballastOpt->value();
    if (currentState == 0) {
      ballastSlider->deactivate();
    } else {
      ballastSlider->activate();
    }
  });

  ballast->end();

  setWidgetSizes(ballast, Ballast);
}

// file operations
auto buildProfile() -> void {
  auto* fileOps = new Fl_Flex(0, Options.h + 15, Options.w, 130, Fl_Flex::VERTICAL);

  auto* profileInput = new Fl_Input(0, 0, 0, 0, "YAML Profile");
  auto* openFile = new Fl_Button(0, 0, 0, 0, "Open YAML");
  auto* refreshFile = new Fl_Button(0, 0, 0, 0, "Refresh YAML");
  auto* generateFile = new Fl_Button(0, 0, 0, 0, "Generate Default YAML");

  fileOps->gap(5);
  fileOps->end();
}

auto main(int argc, char** argv) -> int {
  buildWindow();
  buildOptions();
  buildBallast();
  buildProfile();

  AppWindow->end();
  AppWindow->show(argc, argv);
  return Fl::run();
}
