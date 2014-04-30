
#ifndef LMQ_CONTEXT_INTERFACE_HPP
#define LMQ_CONTEXT_INTERFACE_HPP

#include "channel_id.hpp"

namespace lmq {

    struct consumer_interface;
    struct producer_interface;
    struct channel;

    struct context_interface {
		virtual void bind_channel(const channel_id::id_type& ch_id, consumer_interface& base) = 0;
		virtual void bind_channel(const channel_id::id_type& ch_id, producer_interface& base) = 0;

        virtual channel* const get_channel(const channel_id::id_type& ch_id) = 0;
    };
}

#endif
