
#ifndef LMQ_MESSAGE_FACTORY_HPP
#define LMQ_MESSAGE_FACTORY_HPP

#include <map>
#include <memory>

#include <iostream>

namespace lmq {

    struct message_factory {

        struct message {
        };

        

        //typedef std::map<const factory_message* const, std::shared_ptr<factory_message>> container_type;
        //container_type _msgs;

        /*message get_new_message() {
            message msg;
            return std::move(msg);
        }*/

    };
}

#endif
