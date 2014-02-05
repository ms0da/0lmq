
#include "test.hpp"
#include "../src/channel.hpp"

SCENARIO("channel") {
    using lmq::channel;
    const channel::id_type ch_id = 42;
    channel ch(ch_id);
    
    REQUIRE(ch.get_id() == ch_id);
    auto consumers = ch.get_consumers();
    REQUIRE(0 == consumers.size());
    auto producers = ch.get_producers();
    REQUIRE(0 == producers.size());

    GIVEN("a consumer") {
        using lmq::consumer;
        const consumer co;
        
        WHEN("the consumer is added") {
            ch.add_consumer(co);
            
            THEN("the consumer count is increased, but not the producer count") {
                REQUIRE(1 == ch.get_consumers().size());
                REQUIRE(0 == ch.get_producers().size());
            }
        }
    }
    GIVEN("a producer") {
        using lmq::producer;
        const producer pr;

        WHEN("the producer is added") {
            ch.add_producer(pr);

            THEN("the producer count is increased, but not the consumer count") {
                REQUIRE(0 == ch.get_consumers().size());
                REQUIRE(1 == ch.get_producers().size());
            }
        }
    }
}
