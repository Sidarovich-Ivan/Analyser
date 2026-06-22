#pragma once

#include <charconv>
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>

#include <iostream>

inline int ToInt(std::string_view value) {
    try {
        return std::stoi(value.data());
    } catch (...) {
        throw std::runtime_error(std::format("Error in converting {} to int", value));
    }
}
