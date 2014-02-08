
#ifndef LMQ_CHANNEL_H
#define LMQ_CHANNEL_H

#include <list>
#include "bindable.hpp"

namespace lmq {

    struct channel {
        typedef int id_type;
        typedef std::list<bindable> bindable_list;

        channel(const id_type& id)
        :_channel_id(id) {
        }

        void add_consumer(const consumer& consumer) {
            _consumers.push_back(consumer);
        }

        void add_producer(const producer& producer) {
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
