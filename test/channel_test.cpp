
#include "test.hpp"
#include "../src/channel.hpp"
#include "../src/context.hpp"

#include "../src/consumer.hpp"
#include "../src/producer.hpp"

SCENARIO("channel") {
    using lmq::context;
    context ctx;

    using lmq::channel;
    const channel::id_type ch_id = 42;
    channel* ch = ctx.get_channel(ch_id);

    REQUIRE(ch->get_id() == ch_id);
    auto consumers = ch->get_consumers();
    REQUIRE(0 == consumers.size());
    auto producers = ch->get_producers();
    REQUIRE(0 == producers.size());

    GIVEN("a consumer") {
        using lmq::consumer;
        consumer co(ctx);
        
        WHEN("the consumer is added") {
            ch->add_consumer(&co);
            
            THEN("the consumer count is increased, but not the producer count") {
                auto consumers = ch->get_consumers();
                REQUIRE(1 == consumers.size());
                auto cons_first = consumers.front();
                auto cons_ptr_eq = cons_first == &co;
                REQUIRE(cons_ptr_eq);
                REQUIRE(0 == ch->get_producers().size());
            }
            WHEN("a message is pushed") {
                const int msg_value = 55;
                ch->push(std::move(lmq::message_factory::message(msg_value)));

                THEN("the consumer receive the message") {
                    auto msg = co.get_message();
                    auto msg_ptr_null = nullptr == msg;
                    REQUIRE_FALSE(msg_ptr_null);
                    REQUIRE(msg->get() == msg_value);
                }
            }
        }
    }
    GIVEN("a producer") {
        using lmq::producer;
        producer pr(ctx);

        WHEN("the producer is added") {
            ch->add_producer(&pr);

            THEN("the producer count is increased, but not the consumer count") {
                REQUIRE(0 == ch->get_consumers().size());
                auto producers = ch->get_producers();
                REQUIRE(1 == producers.size());
                auto prod_first = producers.front();
                auto prod_ptr_eq = prod_first == &pr;
                REQUIRE(prod_ptr_eq);
            }
        }
    }
}
