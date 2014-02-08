
#include <algorithm>

#include "../ext/catch/catch.hpp"
#include "../src/context.hpp"

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
            consumer c;
            ctx.bind_channel(c_id, c);

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
            producer p;
            ctx.bind_channel(c_id, p);

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

//SCENARIO("binding channels", "context") {
//    using lmq::context;
//    context ctx;
//
//    auto channel_count = ctx.get_channel_count();
//    REQUIRE(0 == channel_count);
//   
//    const lmq::channel::id_type channel_id = 1;
//
//    SECTION("bind consumer") {
//        ctx.bind_consumer(channel_id, lmq::bindable());
//        channel_count = ctx.get_channel_count();
//        REQUIRE(1 == channel_count);
//        const auto first_channel = ctx.get_channel_count(channel_id);
//        REQUIRE(1 == channel_count);
//    }
//
//}
