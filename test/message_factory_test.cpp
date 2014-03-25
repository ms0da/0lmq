
#include "../ext/catch/catch.hpp"

#include "../src/message_factory.hpp"

SCENARIO("message_factory") {
    using lmq::message_factory;
    message_factory msg_factory;

    //auto msg = msg_factory.get_new_message();
    REQUIRE(false);
}
