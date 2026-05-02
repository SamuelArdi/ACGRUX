#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstddef>
#include <filesystem>

#include "FL/Fl_Widget.H"
#include "FL/Fl_Native_File_Chooser.H"
#include "FL/Fl_Output.H"
#include "FL/fl_ask.H"
#include "FL/Fl_Output.H"

#include "yaml-cpp/yaml.h"
#include <yaml-cpp/exceptions.h>

#ifndef PROFILE_HPP
#define PROFILE_HPP

auto selectProfile(Fl_Widget* w, void* d) -> void;
auto openYaml(Fl_Widget* w, void* d) -> void;
auto loadYaml(Fl_Widget* w, void* d) -> void;
auto generateYaml(Fl_Widget* w, void* d) -> void;

#endif
