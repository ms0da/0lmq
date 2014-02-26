
#ifndef LMQ_PRODUCER_HPP
#define LMQ_PRODUCER_HPP

#include "bindable.hpp"

namespace lmq {

    struct producer : public producer_base {
        producer(const_context_type ctx)
        :producer_base(ctx) {
        }

        virtual void bind(const_channel_id_type ch_id) {
            get_context().bind_channel(ch_id, *this);
        }
    };
}

#endif
