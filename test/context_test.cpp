
#include <algorithm>

#include "../ext/catch/catch.hpp"
#include "../src/context.hpp"

#include "../src/consumer.hpp"
#include "../src/producer.hpp"

SCENARIO("context") {
    using lmq::context;
    context ctx;
    auto channel_count = ctx.get_channel_count();
    REQUIRE(0 == channel_count);

    GIVEN("a consumer") {
        using lmq::consumer;
        using lmq::producer;
        lmq::channel::id_type c_id = 1;
        const lmq::channel* ch;

        WHEN("no channel bound") {
            auto ch_count = ctx.get_channel_count();
            REQUIRE(ch_count == 0);

            THEN("no channel exists") {
                ch = ctx.get_channel(c_id);
                const bool not_exist_channel = nullptr == ch;
                REQUIRE(not_exist_channel);
            }
        }
        WHEN("a consumer binds") {
            consumer c(ctx);
            c.bind(c_id);

            THEN("the channel count and number of consumer are increased") {
                REQUIRE(1 == ctx.get_channel_count());
                REQUIRE(1 == ctx.get_channel_count(c_id));

                ch = ctx.get_channel(c_id);
                const bool exist_channel = nullptr != ch;
                REQUIRE(exist_channel);
                auto consumers = ch->get_consumers();
                REQUIRE(1 == consumers.size());
            }
        }
        WHEN("a producer binds") {
            producer p(ctx);
            p.bind(c_id);

            THEN("the channel count and number of producer are increased") {
                REQUIRE(1 == ctx.get_channel_count());
                REQUIRE(1 == ctx.get_channel_count(c_id));

                ch = ctx.get_channel(c_id);
                const bool exist_channel = nullptr != ch;
                REQUIRE(exist_channel);
                auto producers = ch->get_producers();
                REQUIRE(1 == producers.size());
            }
        }
    }

}
