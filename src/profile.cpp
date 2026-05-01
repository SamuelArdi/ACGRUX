#include "../lib/profile.hpp"
#include "../lib/generator.hpp"
#include <FL/fl_ask.H>
#include <cstddef>
#include <yaml-cpp/exceptions.h>

std::string filePath;

auto selectProfile(Fl_Widget* w, void* d) -> void {
  auto getFilename = [](std::string path) {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
      return path;
    }
    return path.substr(pos + 1);
  };

  auto* cpy = (Fl_Output*)d;

  Fl_Native_File_Chooser chooseFile;
  chooseFile.title("Select Profile");
  chooseFile.type(Fl_Native_File_Chooser::BROWSE_FILE);
  chooseFile.filter("YAML Files\t*.{yaml,yml}");
  chooseFile.directory(".");
  chooseFile.preset_file("default.yaml");

  switch (chooseFile.show()) {
    case -1:
    std::cerr << "ERROR, " << chooseFile.errmsg() << std::endl;
    break;
    case 1:
    std::cerr << "CANCEL" << std::endl;
    break;
    default:
    std::cout << "PICKED: " << chooseFile.filename() << std::endl;
    filePath = chooseFile.filename();
    cpy->value(getFilename(chooseFile.filename()).c_str());
    break;
  }
}

auto openYaml(Fl_Widget* w, void* d) -> void {
  auto fileExists = [](const std::string path) {
    std::ifstream f(path.c_str());
    return f.good();
  };

  if (!fileExists(filePath)) {
    std::cerr << "FILE DOES NOT EXIST" << std::endl;
    fl_beep(FL_BEEP_ERROR);
    fl_alert("Failed to open file, this is most likely because the file doesn't exist or a incorrect name.");
    return;
  }

  std::string cmd = "xdg-open " + filePath;
  system(cmd.c_str());
}

auto loadYaml(Fl_Widget* w, void* d) -> void {
  auto parseProfile = [](const std::string &profile) -> std::map<std::string, std::vector<std::string>> {
    try {
      YAML::Node file = YAML::LoadFile(profile);
      auto parsedFile = file.as<std::map<std::string, std::vector<std::string>>>();
      return parsedFile;
    } catch (YAML::BadFile) {
      fl_beep(FL_BEEP_ERROR);
      fl_alert("Failed to parse YAML/YML file, did you select the correct profile?");
      return {};
    }
  };

  std::map<std::string, std::vector<std::string>> parsedProfile = parseProfile(filePath);

  GenVecs::touges = parsedProfile["touge"];
  GenVecs::downhillCars = parsedProfile["downhillCars"];
  GenVecs::uphillCars = parsedProfile["uphillCars"];

  GenVecs::circuits = parsedProfile["circuits"];
  GenVecs::circuitCars = parsedProfile["circuitCars"];

  GenVecs::special = parsedProfile["special"];
}

auto generateYaml(Fl_Widget* w, void* d) -> void;
