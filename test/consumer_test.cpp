
#include "../ext/catch/catch.hpp"
#include "../src/consumer.hpp"
#include "../src/context.hpp"

SCENARIO("consumer") {
    using lmq::context;
    context ctx;
    using lmq::consumer;
    consumer c(ctx);
    
    consumer::const_channel_id_type ch_id = 42;

    WHEN("is bound") {
        c.bind(ch_id);



    }
}
