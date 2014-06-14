
#include "../ext/catch/catch.hpp"
#include "../src/producer.hpp"
#include "../src/context.hpp"

using ctx_type = lmq::context;
using prod_type = lmq::producer;
using chid_type = lmq::channel_id::id_type;

SCENARIO("producer") {
    ctx_type ctx;
    chid_type ch_id = 42;

    prod_type prod(ctx);
    GIVEN("binds to a channel") {
        prod.bind(ch_id);

    }

}
