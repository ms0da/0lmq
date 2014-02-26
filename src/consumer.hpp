
#ifndef LMQ_CONSUMER_HPP
#define LMQ_CONSUMER_HPP

#include "bindable.hpp"

namespace lmq {

    struct consumer : public consumer_base {
        consumer(const_context_type ctx)
        :consumer_base(ctx) {
        }

        virtual void bind(const_channel_id_type ch_id) {
            get_context().bind_channel(ch_id, *this);
        }
    };
}

#endif
