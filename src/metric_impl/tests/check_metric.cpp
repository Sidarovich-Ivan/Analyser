#pragma once

#include "file.hpp"
#include "function.hpp"
#include "metric.hpp"

#include <gtest/gtest.h>
#include <string>
#include <vector>

using FnList = std::vector<analyzer::function::Function>;
using File = analyzer::file::File;
using FnExtr = analyzer::function::FunctionExtractor;
using MetricResult = analyzer::metric::MetricResult;

template <typename MetricT, typename ReturnT>
void check_metric(const std::string &filename, ReturnT expected_res, const std::string &expected_name) {

    MetricT metric;
    File file(filename);
    FnExtr extractor;

    FnList fn_list = extractor.Get(file);

    ASSERT_EQ(fn_list.size(), 1);

    MetricResult mr = metric.Calculate(fn_list[0]);

    ASSERT_EQ(mr.metric_name, expected_name);
    ASSERT_TRUE(std::holds_alternative<ReturnT>(mr.value));
    EXPECT_EQ(std::get<ReturnT>(mr.value), expected_res);
}