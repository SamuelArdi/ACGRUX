#include "../lib/generator.hpp"
#include "../lib/engine.hpp"
#include <FL/fl_ask.H>
#include <string>

auto generateTouge() -> std::string {
  if (GenVecs::touges.empty()) {
    std::cerr << "TOUGES VECTOR EMPTY" << std::endl;
    fl_beep(FL_BEEP_MESSAGE);
    fl_message("The touges entry is empty.");
    return "";
  }

  std::string currentTouge = vectorRng(GenVecs::touges);
  GenHelper::tougeID = currentTouge.back();

  std::string tougeCpy = currentTouge;
  tougeCpy.pop_back();
  switch (GenHelper::tougeID) {
    case '+':
    return "Touge: " + tougeCpy + " Uphill";

    case '-':
    return "Touge: " + tougeCpy + " Downhill";

    default:
    return "Touge: " + currentTouge;
  }
}
auto generateTougeCar() -> std::string {
  bool c1 = GenVecs::downhillCars.empty();
  bool c2 = GenVecs::uphillCars.empty();

  if (c1 && c2) {
    std::cerr << "DOWNHILL AND UPHILL VECTORS EMPTY" << std::endl;
    fl_beep(FL_BEEP_MESSAGE);
    fl_message("Both downhill and uphill cars entries are empty.");
    return "";
  }

  switch (GenHelper::tougeID) {
    case '+':
    return "\nCar: " + vectorRng(GenVecs::uphillCars);

    case '-':
    return "\nCar: " + vectorRng(GenVecs::downhillCars);

    default:
    std::vector<std::string> combinedCars;
    combinedCars.insert(combinedCars.end(), GenVecs::downhillCars.begin(), GenVecs::downhillCars.end());
    combinedCars.insert(combinedCars.end(), GenVecs::uphillCars.begin(), GenVecs::uphillCars.end());
    return "\nCar: " + vectorRng(combinedCars);
  }
}

auto generateCircuit() -> std::string {
  if (GenVecs::circuits.empty()) {
    std::cerr << "CIRCUITS VECTOR EMPTY" << std::endl;
    fl_beep(FL_BEEP_MESSAGE);
    fl_message("The circuits entry is empty.");
    return "";
  }
  return "Circuit: " + vectorRng(GenVecs::circuits);
};
auto generateCircuitCar() -> std::string {
  if (GenVecs::circuitCars.empty()) {
    std::cerr << "CIRCUIT CARS VECTOR EMPTY" << std::endl;
    fl_beep(FL_BEEP_MESSAGE);
    fl_message("The circuit cars entry is empty.");
    return "";
  }
  return "Car: " + vectorRng(GenVecs::circuitCars);
};

auto generateSpecial() -> std::string {
  if (GenVecs::special.empty()) {
    std::cerr << "SPECIAL VECTOR EMPTY" << std::endl;
    fl_beep(FL_BEEP_MESSAGE);
    fl_message("The special entry is empty.");
    return "";
  }
  return "Special: " + vectorRng(GenVecs::special);
};

auto Generator(Fl_Widget *w, void* d) -> void {
  auto setBool = [](int num)-> bool  {
    return static_cast<bool>(num);
  };

  auto checkEmptyString = [](const std::string& str, std::string (*genFunc)())-> void{
    bool check = str.empty();
    if (check) {
      return;
    }

    std::string selection = genFunc();
    fl_message("%s", selection.c_str());
  };

  // manually setting opts as bool
  bool specialOpt = setBool(Opts::specialOpt->value());

  bool tougesOpt = setBool(Opts::tougesOpt->value());
  bool tougeCarsOpt = setBool(Opts::tougeCarsOpt->value());

  bool circuitOpt = setBool(Opts::circuitsOpt->value());
  bool circuitCarsOpt = setBool(Opts::circuitCarsOpt->value());

  bool ballastOpt = setBool(Opts::ballastOpt->value());

  if (specialOpt && useSpecial()) {
    std::string special = generateSpecial();
    checkEmptyString(special, &generateSpecial);
    return;
  }

  bool isLegal = boolRng(); // whether its touge or circuit
  if (tougesOpt && !isLegal) {
    std::string touge = generateTouge();
    checkEmptyString(touge, generateTouge);
  }
  if (tougeCarsOpt && !isLegal) {
    std::string tougeCar = generateTougeCar();
    checkEmptyString(tougeCar, generateTougeCar);
  }

  if (circuitOpt && isLegal) {
    std::string circuit = generateCircuit();
    checkEmptyString(circuit, generateCircuit);
  }
  if (circuitCarsOpt && isLegal) {
    std::string circuitCar = generateCircuitCar();
    checkEmptyString(circuitCar, generateCircuitCar);
  }

  if (ballastOpt) {
    std::string ballast = std::to_string(ballastRng(Opts::ballastOpt->value()));
    fl_message("%s", ballast.c_str());
  }
};
