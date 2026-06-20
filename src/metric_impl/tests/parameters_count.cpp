#include "metric_impl/parameters_count.hpp"

#include <gtest/gtest.h>

#include "check_metric.cpp"

using CountParametersMetric = analyzer::metric::metric_impl::CountParametersMetric;

static const std::string METRIC_NAME = "Parameters count";

// clang-format off
TEST(CountParametersMetric, Comments) {
    check_metric<CountParametersMetric, int>("./comments.py", 3, METRIC_NAME);
};

TEST(CountParametersMetric, Exceptions) {
    check_metric<CountParametersMetric, int>("./exceptions.py", 0, METRIC_NAME);
};

TEST(CountParametersMetric, If) { 
    check_metric<CountParametersMetric, int>("./if.py", 1, METRIC_NAME); 
};

TEST(CountParametersMetric, Loops) { 
    check_metric<CountParametersMetric, int>("./loops.py", 1, METRIC_NAME); 
};

TEST(CountParametersMetric, Many_lines) {
    check_metric<CountParametersMetric, int>("./many_lines.py", 0, METRIC_NAME);
};

TEST(CountParametersMetric, Many_parameters) {
    check_metric<CountParametersMetric, int>("./many_parameters.py", 5, METRIC_NAME);
};

TEST(CountParametersMetric, Match_case) {
    check_metric<CountParametersMetric, int>("./match_case.py", 1, METRIC_NAME);
};

TEST(CountParametersMetric, Nested_if) {
    check_metric<CountParametersMetric, int>("./nested_if.py", 2, METRIC_NAME);
};

TEST(CountParametersMetric, Simple) { 
    check_metric<CountParametersMetric, int>("./simple.py", 0, METRIC_NAME); 
};

TEST(CountParametersMetric, Ternary) {
    check_metric<CountParametersMetric, int>("./ternary.py", 1, METRIC_NAME);
};
// clang-format on
