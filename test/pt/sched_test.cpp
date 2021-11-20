//
// Created by netcan on 2021/11/20.
//

#include <catch2/catch_test_macros.hpp>
#include <nanobench.h>
#include <asyncio/task.h>
#include <asyncio/runner.h>

using asyncio::Task;

SCENARIO("sched perf test") {
    auto completes_synchronously = []() -> Task<int> {
        co_return 1;
    };

    auto main = [&]() -> Task<int> {
        int sum = 0;
        for (int i = 0; i < 1'000'000; ++i) {
            sum += co_await completes_synchronously();
        }
        REQUIRE(sum == 1'000'000);
    };

    ankerl::nanobench::Bench().run("lots of synchronous completions ", [&] {
        asyncio::run(main());
    });
}