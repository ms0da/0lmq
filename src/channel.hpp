
#ifndef LMQ_CHANNEL_HPP
#define LMQ_CHANNEL_HPP

#include <list>
#include "channel_id.hpp"
//#include "bindable.hpp"

namespace lmq {

    class bindable;

    struct channel {
        typedef channel_id::id_type id_type;
        typedef std::list<bindable> bindable_list;

        channel(const id_type& id)
        :_channel_id(id) {
        }

        void add_consumer(const bindable& consumer) {
            _consumers.push_back(consumer);
        }

        void add_producer(const bindable& producer) {
            _producers.push_back(producer);
        }

        const id_type get_id() const {
            return _channel_id;
        }

        const bindable_list& get_producers() const {
            return _producers;
        }

        const bindable_list& get_consumers() const {
            return _consumers;
        }

    private:
        id_type _channel_id;
        bindable_list _producers;
        bindable_list _consumers;
    };
}

#endif
