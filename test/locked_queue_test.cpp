
#include <random>

#include "../src/locked_queue.hpp"
#include "../ext/catch/catch.hpp"

void random_populate_queue(lmq::locked_queue<int> &q, const int min, const int max) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dis(min, max);

    auto count = dis(generator);
    for(int i = 0; i < count; ++i) {
        auto elem = dis(generator);
        q.push_back(elem);
    }
}

SCENARIO("lockeq queue") {
    using lmq::locked_queue;
    typedef locked_queue<int> queue_type;
    queue_type q;
    queue_type::elem_type element_added = 1;
    const queue_type::size_type min_count = 2;
    const queue_type::size_type max_count = 100;

    GIVEN("an empty queue") {
        REQUIRE(true == q.empty());
        REQUIRE(0 == q.size());

        WHEN("an element is added") {
            q.push_back(element_added);

            THEN("the size is larger") {
                REQUIRE(true != q.empty());
                REQUIRE(q.size() > 0);
            }
        }
    }
    GIVEN("a queue with 1 element") {
        q.push_back(element_added);
        REQUIRE(false == q.empty());
        REQUIRE(1 == q.size());

        WHEN("an element is removed") {
            auto element_removed = q.front();
            q.pop_front();

            THEN("the size is zero") {
                REQUIRE(true == q.empty());
                REQUIRE(0 == q.size());
                REQUIRE(element_added == element_removed);
            }
        }
    }
    GIVEN("a queue with more than 2 elements and less than 100 elements") {
        random_populate_queue(q, min_count, max_count);
        const auto queue_size = q.size();

        WHEN("an element is removed") {
            q.pop_front();

            THEN("the size is smaller") {
                const auto new_size = queue_size - 1;
                REQUIRE(new_size == q.size());
            }
        }
        WHEN("an element is added") {
            q.push_back(0);

            THEN("the size is larger") {
                const auto new_size = queue_size + 1;
                REQUIRE(new_size == q.size());
            }
        }
        WHEN("the queue is cleared") {
            q.clear();

            THEN("the size is zero") {
                REQUIRE(true == q.empty());
                REQUIRE(0 == q.size());
            }
        }
    }
}
