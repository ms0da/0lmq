
#ifndef LMQ_CHANNEL_HPP
#define LMQ_CHANNEL_HPP

#include <list>

#include "bindable.hpp"
#include "message_factory.hpp"
#include "context_interface.hpp"

namespace lmq {

    // USE POINTER FOR CONTENT OF LISTS
    // UNIQUE PTR? AUTO PTR?
    struct channel {
        typedef channel_id::id_type id_type;

        typedef consumer_base* const consumer_const_ptr_type;
        typedef std::list<consumer_const_ptr_type> consumer_list;

        typedef producer_base* const producer_const_ptr_type;
        typedef std::list<producer_const_ptr_type> producer_list;

        typedef const message_factory::message const_msg_type;

        channel(const id_type& id)
        :_channel_id(id) {
        }

        const id_type get_id() const {
            return _channel_id;
        }

        void add_consumer(consumer_const_ptr_type consumer) {
            _consumers.push_back(consumer);
        }

        void add_producer(producer_const_ptr_type producer) {
            _producers.push_back(producer);
        }

        const consumer_list& get_consumers() const {
            return _consumers;
        }

        const producer_list& get_producers() const {
            return _producers;
        }

        void push(producer_base::const_msg_ref_type msg) {
            auto shared_ptr_msg = std::make_shared<const_msg_type>(msg);
            for(auto cons : _consumers) {
                cons->consume(shared_ptr_msg);
            }            
        }

    private:
        id_type _channel_id;
        producer_list _producers;
        consumer_list _consumers;
    };
}

#endif
