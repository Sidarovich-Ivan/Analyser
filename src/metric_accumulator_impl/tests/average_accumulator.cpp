#include "metric_accumulator_impl/average_accumulator.hpp"
#include "metric.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

using AverageAccumulator = analyzer::metric_accumulator::metric_accumulator_impl::AverageAccumulator;
using MetricResult = analyzer::metric::MetricResult;

TEST(AverageAccumulator, ValidUsage) {
    AverageAccumulator acc;

    acc.Accumulate({.metric_name = "test1", .value = 1});
    acc.Accumulate({.metric_name = "test2", .value = 2});
    acc.Accumulate({.metric_name = "test3", .value = 3});
    acc.Accumulate({.metric_name = "test4", .value = 4});
    acc.Accumulate({.metric_name = "test5", .value = 5});

    acc.Finalize();

    EXPECT_DOUBLE_EQ(acc.Get(), (1.0 + 2 + 3 + 4 + 5) / 5);

    acc.Reset();
    acc.Finalize();

    EXPECT_DOUBLE_EQ(acc.Get(), 0.0);

    acc.Reset();

    acc.Accumulate({.metric_name = "test6", .value = 6});
    acc.Accumulate({.metric_name = "test7", .value = 7});
    acc.Accumulate({.metric_name = "test8", .value = 8});
    acc.Accumulate({.metric_name = "test9", .value = 9});
    acc.Accumulate({.metric_name = "test10", .value = 10});

    acc.Finalize();

    EXPECT_DOUBLE_EQ(acc.Get(), (6.0 + 7 + 8 + 9 + 10) / 5);
}

TEST(AverageAccumulator, EmptyAcc) {
    AverageAccumulator acc;

    acc.Finalize();

    EXPECT_DOUBLE_EQ(acc.Get(), 0.0);
}

TEST(AverageAccumulator, NotFinalize) {
    AverageAccumulator acc;

    EXPECT_THROW(acc.Get(), std::runtime_error);
}
