
#include "test.hpp"
#include "../src/channel.hpp"
#include "../src/context.hpp"

#include "../src/consumer.hpp"
#include "../src/producer.hpp"

SCENARIO("channel") {
    using lmq::channel;
    const channel::id_type ch_id = 42;
    channel ch(ch_id);
    
    REQUIRE(ch.get_id() == ch_id);
    auto consumers = ch.get_consumers();
    REQUIRE(0 == consumers.size());
    auto producers = ch.get_producers();
    REQUIRE(0 == producers.size());

    using lmq::context;
    context ctx;

    GIVEN("a consumer") {
        using lmq::consumer;
        consumer co(ctx);
        
        WHEN("the consumer is added") {
            ch.add_consumer(&co);
            
            THEN("the consumer count is increased, but not the producer count") {
                REQUIRE(1 == ch.get_consumers().size());
                REQUIRE(0 == ch.get_producers().size());
            }
        }
    }
    GIVEN("a producer") {
        using lmq::producer;
        producer pr(ctx);

        WHEN("the producer is added") {
            ch.add_producer(&pr);

            THEN("the producer count is increased, but not the consumer count") {
                REQUIRE(0 == ch.get_consumers().size());
                REQUIRE(1 == ch.get_producers().size());
            }
        }
    }
    GIVEN("a producer and 2 consumers") {
        using lmq::producer;
        producer pr(ctx);
        pr.bind(ch_id);
        const channel::id_type new_channel_id = ch_id + 1;
        pr.bind(new_channel_id);

        using lmq::consumer;
        consumer co_ch1(ctx);
        co_ch1.bind(new_channel_id);
        consumer co_ch2(ctx);
        co_ch2.bind(ch_id);

        WHEN("the producer publish only to a channel") {
            const lmq::message_factory::message msg;
            pr.publish(&msg, ch_id);

            THEN("a single consumer got the message") {
                auto msg_ch1 = co_ch1.get_message();
                bool is_null = nullptr == msg_ch1;
                REQUIRE(is_null);
                auto msg_ch2 = co_ch2.get_message();
                is_null = nullptr == msg_ch2;
                REQUIRE_FALSE(is_null);
            }
        }
    }
    GIVEN("a new message") {

        // TODO
        REQUIRE(false);
        auto msg_factory = ctx.get_message_factory();
        //auto msg = msg_factory.get_new_message();
        //REQUIRE(nullptr != msg);

        WHEN("a message is pushed") {
            //ch.push(msg);


        }
    }
}
