#include "metric_impl/code_lines_count.hpp"

#include <unistd.h>

#include "utils.hpp"
#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

namespace analyzer::metric::metric_impl {
std::string CodeLinesCountMetric::Name() const { return kName; }

MetricResult::ValueType CodeLinesCountMetric::CalculateImpl(const function::Function &f) const {
    auto &function_ast = f.ast;

    auto line_number = [&](int start_pos) {
        size_t line_pos = function_ast.find("[", start_pos);
        size_t comma_pos = function_ast.find(",", line_pos);
        return ToInt(function_ast.substr(line_pos + 1, comma_pos - line_pos - 1));
    };

    const int start_line = line_number(0);
    const int end_line = line_number(function_ast.find("] -"));

    auto is_code_line = [&](int line) {
        std::string line_marker = "[" + std::to_string(line) + ",";
        size_t line_pos = function_ast.find(line_marker);

        if (line_pos == std::string::npos)
            return false;

        size_t node_start = function_ast.rfind('(', line_pos);
        if (node_start == std::string::npos)
            return false;

        std::string_view node_type =
            std::string_view(function_ast)
                .substr(node_start + 1, function_ast.find_first_of(" \n[", node_start + 1) - node_start - 1);

        return node_type != "comment";
    };

    return static_cast<int>(std::ranges::count_if(std::views::iota(start_line + 1, end_line + 1), is_code_line));
}

}  // namespace analyzer::metric::metric_impl
