
#ifndef LMQ_CONSUMER_HPP
#define LMQ_CONSUMER_HPP

#include <list>

#include "bindable.hpp"

namespace lmq {

    struct consumer : public consumer_base {
        consumer(const_context_type ctx)
        :consumer_base(ctx) {
        }

        virtual void bind(const_channel_id_type ch_id) {
            get_context().bind_channel(ch_id, *this);
        }

        virtual void consume(const message_factory::message* const msg) {
            _msgs.push_back(msg);
        }

        const message_factory::message* const get_message() const {
            return _msgs.empty() ? nullptr : _msgs.front();
        }

        void next_message() {
            _msgs.pop_front();
        }

    private:
        typedef std::list<const message_factory::message* const> container_type;

        container_type _msgs;
    };
}

#endif
