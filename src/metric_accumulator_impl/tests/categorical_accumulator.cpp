

#include "metric_accumulator_impl/categorical_accumulator.hpp"
#include "metric.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

using CategoricalAccumulator = analyzer::metric_accumulator::metric_accumulator_impl::CategoricalAccumulator;
using MetricResult = analyzer::metric::MetricResult;
using ResMap = std::unordered_map<std::string, int>;

TEST(CategoricalAccumulator, ValidUsage) {
    CategoricalAccumulator acc;

    // category 1
    acc.Accumulate({.metric_name = "test1", .value = "category_1"});
    acc.Accumulate({.metric_name = "test2", .value = "category_1"});
    acc.Accumulate({.metric_name = "test3", .value = "category_1"});

    // category 2
    acc.Accumulate({.metric_name = "test4", .value = "category_2"});
    acc.Accumulate({.metric_name = "test5", .value = "category_2"});

    // category 3
    acc.Accumulate({.metric_name = "test6", .value = "category_3"});
    acc.Accumulate({.metric_name = "test7", .value = "category_3"});

    acc.Finalize();

    ResMap res1 = acc.Get();

    EXPECT_EQ(res1.size(), 3);
    EXPECT_EQ(res1["category_1"], 3);
    EXPECT_EQ(res1["category_2"], 2);
    EXPECT_EQ(res1["category_3"], 2);

    acc.Reset();
    acc.Finalize();

    ResMap res2 = acc.Get();

    EXPECT_EQ(res2.size(), 0);

    acc.Reset();

    // category 4
    acc.Accumulate({.metric_name = "test8", .value = "category_4"});
    acc.Accumulate({.metric_name = "test9", .value = "category_4"});
    acc.Accumulate({.metric_name = "test10", .value = "category_4"});

    // category 5
    acc.Accumulate({.metric_name = "test11", .value = "category_5"});
    acc.Accumulate({.metric_name = "test12", .value = "category_5"});

    // category 6
    acc.Accumulate({.metric_name = "test13", .value = "category_6"});

    acc.Finalize();

    ResMap res3 = acc.Get();

    EXPECT_EQ(res3.size(), 3);
    EXPECT_EQ(res3["category_4"], 3);
    EXPECT_EQ(res3["category_5"], 2);
    EXPECT_EQ(res3["category_6"], 1);
}

TEST(CategoricalAccumulator, EmptyAcc) {
    CategoricalAccumulator acc;

    acc.Finalize();

    ResMap res = acc.Get();

    EXPECT_EQ(res.size(), 0);
}

TEST(CategoricalAccumulator, NotFinalize) {
    CategoricalAccumulator acc;

    EXPECT_THROW(acc.Get(), std::runtime_error);
}
