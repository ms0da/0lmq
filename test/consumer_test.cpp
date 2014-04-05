
#include "../ext/catch/catch.hpp"
#include "../src/consumer.hpp"
#include "../src/context.hpp"
#include "../src/message_factory.hpp"

SCENARIO("consumer") {
    using lmq::context;
    context ctx;
    using lmq::consumer;
    consumer cons(ctx);
    
    consumer::const_channel_id_type ch_id = 42;

    GIVEN("is bound to a channel") {
        cons.bind(ch_id);

        WHEN("the channel has a consumer bound to it") {
            auto channel = ctx.get_channel(ch_id);
            auto ch_consumers = channel->get_consumers();
            REQUIRE(ch_consumers.size() == 1);

            THEN("it is the same consumer") {
                auto first_cons = ch_consumers.front();
                REQUIRE(first_cons == &cons);
            }
        }
        WHEN("no message are consumed") {
            // ...

            THEN("the first message is null") {
                auto msg = cons.get_message();
                bool is_msg_null = msg == nullptr;
                REQUIRE(is_msg_null);

                AND_WHEN("we do not consume... again") {
                    // ...

                    THEN("the first message is null... again") {
                        msg = cons.get_message();
                        is_msg_null = msg == nullptr;
                        REQUIRE(is_msg_null);
                    }
                }
            }
        }
        WHEN("a message is consumed receives message") {
            const int msg_value = 42;
            cons.consume(std::make_shared<lmq::message_factory::message>(lmq::message_factory::message(msg_value)));

            THEN("the consumer receives the message") {
                auto msg = cons.get_message();
                bool is_msg_present = msg != nullptr;
                REQUIRE(is_msg_present);
                REQUIRE(msg->get() == msg_value);

                AND_WHEN("the consumer is ready for another message, but none have been consumed") {
                    cons.next_message();

                    THEN("the next message is null") {
                        msg = cons.get_message();
                        is_msg_present = msg != nullptr;
                        REQUIRE_FALSE(is_msg_present);
                    }
                }
                AND_WHEN("the consumer is ready for another message and it has been consumed") {
                    const int snd_msg_value = msg_value + 1;
                    cons.consume(std::make_shared<lmq::message_factory::message>(lmq::message_factory::message(snd_msg_value)));
                    cons.next_message();

                    THEN("the next message is not null") {
                        msg = cons.get_message();
                        is_msg_present = msg != nullptr;
                        REQUIRE(is_msg_present);
                        REQUIRE(msg->get() == snd_msg_value);
                    }
                }
            }
        }
    }
}
