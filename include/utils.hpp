#pragma once

#include <charconv>
#include <stdexcept>
#include <string>
#include <string_view>

#include <iostream>

inline int ToInt(std::string_view value) { return std::stoi(value.data()); }
