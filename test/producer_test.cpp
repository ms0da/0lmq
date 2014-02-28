
#include "../ext/catch/catch.hpp"
#include "../src/producer.hpp"
#include "../src/context.hpp"

SCENARIO("producer") {
    using lmq::context;
    context ctx;
    using lmq::producer;
    producer p(ctx);
    REQUIRE(0 == p.get_bound_channel_count());

    producer::const_channel_id_type ch_id = 42;
    
    GIVEN("is bound") {
        p.bind(ch_id);
        REQUIRE(1 == p.get_bound_channel_count());

        WHEN("you bind again to the same channel") {
            p.bind(ch_id);

            THEN("the bound count should not change") {
                REQUIRE(1 == p.get_bound_channel_count());
            }
        }
        WHEN("you bind to a different channel") {
            p.bind(ch_id + 1);

            THEN("the bound count should increase") {
                REQUIRE(2 == p.get_bound_channel_count());
            }
        }
    }
}
