#include "metric_impl/cyclomatic_complexity.hpp"

#include <gtest/gtest.h>

#include "check_metric.cpp"

using CyclomaticComplexityMetric = analyzer::metric::metric_impl::CyclomaticComplexityMetric;

static const std::string METRIC_NAME = "Cyclomatic Complexity";

// clang-format off
TEST(CyclomaticComplexityMetric, Comments) {
    check_metric<CyclomaticComplexityMetric, int>("./comments.py", 1, METRIC_NAME);
};

TEST(CyclomaticComplexityMetric, Exceptions) {
    check_metric<CyclomaticComplexityMetric, int>("./exceptions.py", 4, METRIC_NAME);
};

TEST(CyclomaticComplexityMetric, If) { 
    check_metric<CyclomaticComplexityMetric, int>("./if.py", 2, METRIC_NAME); 
};

TEST(CyclomaticComplexityMetric, Loops) { 
    check_metric<CyclomaticComplexityMetric, int>("./loops.py", 4, METRIC_NAME); 
};

TEST(CyclomaticComplexityMetric, Many_lines) {
    check_metric<CyclomaticComplexityMetric, int>("./many_lines.py", 2, METRIC_NAME);
};

TEST(CyclomaticComplexityMetric, Many_parameters) {
    check_metric<CyclomaticComplexityMetric, int>("./many_parameters.py", 2, METRIC_NAME);
};

TEST(CyclomaticComplexityMetric, Match_case) {
    check_metric<CyclomaticComplexityMetric, int>("./match_case.py", 4, METRIC_NAME);
};

TEST(CyclomaticComplexityMetric, Nested_if) {
    check_metric<CyclomaticComplexityMetric, int>("./nested_if.py", 4, METRIC_NAME);
};

TEST(CyclomaticComplexityMetric, Simple) { 
    check_metric<CyclomaticComplexityMetric, int>("./simple.py", 2, METRIC_NAME); 
};

TEST(CyclomaticComplexityMetric, Ternary) {
    check_metric<CyclomaticComplexityMetric, int>("./ternary.py", 3, METRIC_NAME);
};
// clang-format on
