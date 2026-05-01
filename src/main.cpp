#include "FL/Fl_Double_Window.H"
#include "FL/Fl_Flex.H"
#include "FL/Fl_Check_Button.H"
#include "FL/Fl_Button.H"
#include "FL/Fl_Widget.H"
#include "FL/Fl_Hor_Value_Slider.H"
#include "FL/Fl_Output.H"
#include "FL/Fl_Native_File_Chooser.H"
#include "FL/Fl_Multiline_Output.H"

#include <iostream>

struct WIDGET_SIZES {
  int x; int w;
  int y; int h;
} Options, Ballast, Profile, Generate, FileOps;

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
  auto* options = new Fl_Flex(5, 5, 135, 100, Fl_Flex::VERTICAL);

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
  auto* ballast = new Fl_Flex(Options.w + 10, 5, 210, 35, Fl_Flex::HORIZONTAL);

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
  auto* profile = new Fl_Flex(Options.x, Options.h + 15, Options.w, 25, Fl_Flex::HORIZONTAL);

  auto* profileInput = new Fl_Output(0, 0, 0, 0);
  profileInput->value("YAML Profile");
  profile->fixed(profileInput, 90);

  auto* profileSelect = new Fl_Button(0, 0, 0, 0, "Browse");

  // Fl_Native_File_Chooser chooseFile;
  // chooseFile.title("Select Profile");
  // chooseFile.type(Fl_Native_File_Chooser::BROWSE_FILE);
  // chooseFile.filter("YAML Files\t*.{yaml,yml}");
  // chooseFile.directory(".");
  // chooseFile.preset_file("default.yaml");

  // switch (chooseFile.show()) {
  //   case -1:
  //   std::cerr << "ERROR, " << chooseFile.errmsg() << std::endl;
  //   break;
  //   case 1:
  //   std::cerr << "CANCEL" << std::endl;
  //   break;
  //   default:
  //   std::cout << "PICKED: " << chooseFile.filename() << std::endl;
  //   break;
  // }

  profile->gap(2);
  profile->end();

  setWidgetSizes(profile, Profile);

  auto* fileOps = new Fl_Flex(Options.x, (Profile.y + Profile.h) + 5, Options.w, 105, Fl_Flex::VERTICAL);

  auto* openFile = new Fl_Button(0, 0, 0, 0, "Open YAML");
  auto* refreshFile = new Fl_Button(0, 0, 0, 0, "Load YAML");
  // auto* generateFile = new Fl_Button(0, 0, 0, 0, "Generate Default YAML");

  fileOps->gap(5);
  fileOps->end();

  setWidgetSizes(fileOps, FileOps);
}

auto buildGenerate() -> void {
  auto* generate = new Fl_Flex(Options.w + 10, Ballast.h + 22, Ballast.w, 52, Fl_Flex::VERTICAL);

  auto* generateProfileBtn = new Fl_Button(0, 0, 0, 0, "Generate Default YAML");
  auto* generateBtn = new Fl_Button(0, 0, 0, 0, "Generate");

  generate->gap(2);
  generate->end();

  setWidgetSizes(generate, Generate);
}

auto buildGenerateOutput() -> void {
  auto* output = new Fl_Multiline_Output(Options.w + 10, (Generate.y + Generate.h) + 5, Ballast.w, (Profile.h + FileOps.h) + 7);
}

auto main(int argc, char** argv) -> int {
  buildWindow();
  buildOptions();
  buildBallast();
  buildProfile();
  buildGenerate();
  buildGenerateOutput();
  AppWindow->end();
  AppWindow->show(argc, argv);
  return Fl::run();
}
