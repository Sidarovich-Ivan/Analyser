#include "metric_impl/code_lines_count.hpp"

#include <gtest/gtest.h>

#include "check_metric.cpp"

using CodeLinesCountMetric = analyzer::metric::metric_impl::CodeLinesCountMetric;

static const std::string METRIC_NAME = "Code lines count";

// clang-format off

TEST(CodeLinesCountMetric, Comments) {
    check_metric<CodeLinesCountMetric, int>("./comments.py", 3, METRIC_NAME);
};

TEST(CodeLinesCountMetric, Exceptions) {
    check_metric<CodeLinesCountMetric, int>("./exceptions.py", 7, METRIC_NAME);
};

TEST(CodeLinesCountMetric, If) { 
    check_metric<CodeLinesCountMetric, int>("./if.py", 3, METRIC_NAME); 
};

TEST(CodeLinesCountMetric, Loops) { 
    check_metric<CodeLinesCountMetric, int>("./loops.py", 6, METRIC_NAME); 
};

TEST(CodeLinesCountMetric, Many_lines) {
    check_metric<CodeLinesCountMetric, int>("./many_lines.py", 11, METRIC_NAME);
};

TEST(CodeLinesCountMetric, Many_parameters) {
    check_metric<CodeLinesCountMetric, int>("./many_parameters.py", 1, METRIC_NAME);
};

TEST(CodeLinesCountMetric, Match_case) {
    check_metric<CodeLinesCountMetric, int>("./match_case.py", 7, METRIC_NAME);
};

TEST(CodeLinesCountMetric, Nested_if) {
    check_metric<CodeLinesCountMetric, int>("./nested_if.py", 8, METRIC_NAME);
};

TEST(CodeLinesCountMetric, Simple) { 
    check_metric<CodeLinesCountMetric, int>("./simple.py", 5, METRIC_NAME);
};

TEST(CodeLinesCountMetric, Ternary) { 
    check_metric<CodeLinesCountMetric, int>("./ternary.py", 1, METRIC_NAME); 
};
// clang-format on
