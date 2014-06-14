
#include "test.hpp"
#include "../src/channel.hpp"
#include "../src/producer.hpp"
#include "../src/context.hpp"

SCENARIO("producers can be added and removed", "[channel]") {
    using lmq::channel;
    using lmq::channel_id::id_type;
    
    GIVEN("an empty channel") {
        const id_type ch_id = 42;
        channel ch(ch_id);
        
        using lmq::producer;
        using lmq::context;
        context ctx;
        producer prod(ctx);

        REQUIRE(ch_id == ch.get_id());
        REQUIRE(0 == ch.get_producers().size());

        WHEN("a producer is added") {
            ch.add_producer(&prod);

            THEN("the producer count is increased") {
                REQUIRE(1 == ch.get_producers().size());

                WHEN("the same producer is removed") {
                    auto removed = ch.remove(&prod);

                    THEN("the producer count is decreased") {
                        REQUIRE(removed);
                        REQUIRE(0 == ch.get_producers().size());
                    }
                }
                WHEN("a different producer is removed") {
                    producer prod_not_added(ctx);
                    auto removed = ch.remove(&prod_not_added);

                    THEN("the producer count do not change") {
                        REQUIRE(!removed);
                        REQUIRE(1 == ch.get_producers().size());
                    }
                }
            }
        }
        WHEN("a producer is removed") {
            auto removed = ch.remove(&prod);

            THEN("nothing has changed") {
                REQUIRE(!removed);
                REQUIRE(0 == ch.get_producers().size());
            }
        }
    }
}
