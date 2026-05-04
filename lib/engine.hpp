#pragma

#include <cstddef>
#include <cstdlib>
#include <random>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#ifndef ENGINE_HPP
#define ENGINE_HPP

auto vectorRng(std::vector<std::string> v) -> std::string;
auto ballastRng(int max) -> int;

auto boolRng() -> bool;
auto useSpecial() -> bool;

#endif
