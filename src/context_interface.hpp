
#ifndef LMQ_CONTEXT_INTERFACE_HPP
#define LMQ_CONTEXT_INTERFACE_HPP

#include "channel_id.hpp"

namespace lmq {

    struct consumer_base;
    struct producer_base;
    struct channel;

    struct context_interface {
        virtual void bind_channel(const channel_id::id_type& ch_id, consumer_base& base) = 0;
        virtual void bind_channel(const channel_id::id_type& ch_id, producer_base& base) = 0;

        virtual const channel* const get_channel(const channel_id::id_type& ch_id) const = 0;
    };
}

#endif
