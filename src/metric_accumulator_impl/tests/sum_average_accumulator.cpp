#include "metric_accumulator_impl/sum_average_accumulator.hpp"
#include "metric.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

using SumAverageAccumulator = analyzer::metric_accumulator::metric_accumulator_impl::SumAverageAccumulator;
using MetricResult = analyzer::metric::MetricResult;
using SumAverage = SumAverageAccumulator::SumAverage;

TEST(SumAverageAccumulator, ValidUsage) {
    SumAverageAccumulator acc;

    acc.Accumulate({.metric_name = "test1", .value = 1});
    acc.Accumulate({.metric_name = "test2", .value = 2});
    acc.Accumulate({.metric_name = "test3", .value = 3});
    acc.Accumulate({.metric_name = "test4", .value = 4});
    acc.Accumulate({.metric_name = "test5", .value = 5});

    acc.Finalize();

    SumAverage res1 = acc.Get();

    EXPECT_DOUBLE_EQ(res1.average, (1.0 + 2 + 3 + 4 + 5) / 5);
    EXPECT_EQ(res1.sum, 1 + 2 + 3 + 4 + 5);

    acc.Reset();
    acc.Finalize();

    SumAverage res2 = acc.Get();

    EXPECT_DOUBLE_EQ(res2.average, 0.0);
    EXPECT_EQ(res2.sum, 0);

    acc.Reset();

    acc.Accumulate({.metric_name = "test6", .value = 6});
    acc.Accumulate({.metric_name = "test7", .value = 7});
    acc.Accumulate({.metric_name = "test8", .value = 8});
    acc.Accumulate({.metric_name = "test9", .value = 9});
    acc.Accumulate({.metric_name = "test10", .value = 10});

    acc.Finalize();

    SumAverage res3 = acc.Get();

    EXPECT_DOUBLE_EQ(res3.average, (6.0 + 7 + 8 + 9 + 10) / 5);
    EXPECT_EQ(res3.sum, 6 + 7 + 8 + 9 + 10);
}

TEST(SumAverageAccumulator, EmptyAcc) {
    SumAverageAccumulator acc;

    acc.Finalize();

    SumAverage res = acc.Get();

    EXPECT_DOUBLE_EQ(res.average, 0.0);
    EXPECT_EQ(res.sum, 0);
}

TEST(SumAverageAccumulator, NotFinalize) {
    SumAverageAccumulator acc;

    EXPECT_THROW(acc.Get(), std::runtime_error);
}
