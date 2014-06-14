
//#include <algorithm>

#include "../ext/catch/catch.hpp"
#include "../src/context.hpp"

#include "../src/consumer.hpp"
#include "../src/producer.hpp"

using lmq::context;
using lmq::channel_id::id_type;

SCENARIO("context") {

    context ctx;
    const id_type ch_id = 42;

    ctx.bind_channel(ch_id, nullptr);

}
