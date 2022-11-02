#include <catch.hpp>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>


int random_int() {
    return rand() % 100;
}

TEST_CASE("Iterator fun", "[It]") {
    std::vector<int> v;
    for (int i = 0; i < GENERATE(1, 10, 100, 1000); ++i) {
        v.push_back(random_int());
    }

    int n_threads = (int)std::thread::hardware_concurrency();
    int n_values = v.size();
    if (n_values < n_threads)
        n_threads = 1;

    int block_size = n_values / n_threads;
    int remaining_size = n_values;

    int sum = 0;
    std::vector<int> v2(n_values);
    for (auto begin = v.begin(), end = v.end(); begin != end;) {
        int current_block_size = std::min(block_size, remaining_size);
        std::vector<int> lv;
        std::for_each(begin, begin + current_block_size, [&lv](int i) {
            lv.push_back(i);
        });

        v2.insert(v2.end(), lv.begin(), lv.end());
        remaining_size -= current_block_size;
        begin += current_block_size;
    }

    REQUIRE(std::accumulate(v2.begin(), v2.end(), 0) == std::accumulate(v.begin(), v.end(), 0));
}

TEST_CASE("Multiple threads populating one vector", "[NThreadsOneVec]") {
    std::vector<int> values;
    for (int i = 0; i < GENERATE(1, 10, 100, 1000); ++i) {
        values.push_back(random_int());
    }

    std::mutex mutex;
    std::vector<std::thread> threads;

    int n_threads = (int)std::thread::hardware_concurrency();
    int n_values = values.size();
    if (n_values < n_threads)
        n_threads = 1;

    int block_size = n_values / n_threads;
    int remaining_size = n_values;

    std::vector<int> final_values(n_values);
    for (auto begin = values.begin(), end = values.end(); begin!=end;) {
        int current_block_size = std::min(block_size, remaining_size);

        threads.emplace_back(
            [begin, end, current_block_size, &final_values, &mutex]() {
                std::vector<int> thread_values(current_block_size);
                std::for_each(begin, begin+current_block_size, [&thread_values](int value) {
                    thread_values.push_back(value*2);
                });

                std::lock_guard lock(mutex);
                final_values.insert(final_values.end(), thread_values.begin(), thread_values.end());
        });
        remaining_size -= current_block_size;
        begin += current_block_size;
    }

    for (auto& t : threads) {
        t.join();
    }

    int total_threads = std::accumulate(final_values.begin(), final_values.end(), 0);
    int total_initial = std::accumulate(values.begin(), values.end(), 0) * 2;
    REQUIRE(total_threads == total_initial);
}