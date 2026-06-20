#include "metric_impl/naming_style.hpp"

#include <gtest/gtest.h>
#include <string>

#include "check_metric.cpp"

using NamingStyleMetric = analyzer::metric::metric_impl::NamingStyleMetric;

static const std::string METRIC_NAME = "Naming style";

// clang-format off
TEST(NamingStyleMetric, Comments) {
    check_metric<NamingStyleMetric, std::string>("./comments.py", "Unknown", METRIC_NAME);
};

TEST(NamingStyleMetric, Exceptions) {
    check_metric<NamingStyleMetric, std::string>("./exceptions.py", "Unknown", METRIC_NAME);
};

TEST(NamingStyleMetric, If) { 
    check_metric<NamingStyleMetric, std::string>("./if.py", "Camel Case", METRIC_NAME); 
};

TEST(NamingStyleMetric, Loops) { 
    check_metric<NamingStyleMetric, std::string>("./loops.py", "Pascal Case", METRIC_NAME); 
};

TEST(NamingStyleMetric, Many_lines) {
    check_metric<NamingStyleMetric, std::string>("./many_lines.py", "Lower Case", METRIC_NAME);
};

TEST(NamingStyleMetric, Many_parameters) {
    check_metric<NamingStyleMetric, std::string>("./many_parameters.py", "Snake Case", METRIC_NAME);
};

TEST(NamingStyleMetric, Match_case) {
    check_metric<NamingStyleMetric, std::string>("./match_case.py", "Unknown", METRIC_NAME);
};

TEST(NamingStyleMetric, Nested_if) {
    check_metric<NamingStyleMetric, std::string>("./nested_if.py", "Pascal Case", METRIC_NAME);
};

TEST(NamingStyleMetric, Simple) { 
    check_metric<NamingStyleMetric, std::string>("./simple.py", "Snake Case", METRIC_NAME); 
};

TEST(NamingStyleMetric, Ternary) {
    check_metric<NamingStyleMetric, std::string>("./ternary.py", "Unknown", METRIC_NAME);
};
// clang-format on
