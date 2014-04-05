
#include "../ext/catch/catch.hpp"
#include "../src/producer.hpp"
#include "../src/context.hpp"

SCENARIO("producer") {
    using lmq::context;
    context ctx;
    using lmq::producer;
    producer p(ctx);
    REQUIRE(0 == p.get_bound_channel_count());
    const producer::const_channel_id_type ch_id = 42;
    
    GIVEN("binds to a channel") {
        p.bind(ch_id);
        REQUIRE(1 == p.get_bound_channel_count());
		auto ch1 = ctx.get_channel(ch_id);

        WHEN("it binds again to the same channel") {
            p.bind(ch_id);

            THEN("the number of binded channel should not change") {
                REQUIRE(1 == p.get_bound_channel_count());
				auto ch2 = ctx.get_channel(ch_id);
				REQUIRE(ch1 == ch2);
            }
        }
        WHEN("it binds to a different channel") {
			const producer::const_channel_id_type snd_ch_id = ch_id + 1;
            p.bind(snd_ch_id);

            THEN("the bound count should increase") {
                REQUIRE(2 == p.get_bound_channel_count());
				auto ch2 = ctx.get_channel(snd_ch_id);
				REQUIRE_FALSE(ch1 == ch2);
            }
        }
		WHEN("it publishes a message on the binded channel") {
			bool published = p.publish(lmq::message_factory::message(42), ch_id);

			THEN("the message will be published on the channel") {
				REQUIRE(published);
			}
		}
		WHEN("it publishes a message on another channel") {
			bool published = p.publish(lmq::message_factory::message(42), ch_id + 1);

			THEN("the message will not be published") {
				REQUIRE_FALSE(published);
			}
		}
    }
	GIVEN("not bound, but existing channel") {
        REQUIRE(0 == p.get_bound_channel_count());
        ctx.get_channel(ch_id);

        WHEN("it publishes on that channel") {
            bool published = p.publish(lmq::message_factory::message(42), ch_id);

            THEN("the message should not be published") {
                REQUIRE_FALSE(published);
            }
        }
	}
}
