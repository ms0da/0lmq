
#ifndef LMQ_CONTEXT_INTERFACE_HPP
#define LMQ_CONTEXT_INTERFACE_HPP

#include "channel_id.hpp"

namespace lmq {

    struct channel;
    struct producer_interface;
    //struct consumer_interface;

    struct context_interface {
        using channel_id = const channel_id::id_type&;

        virtual void bind_channel(channel_id ch_id, producer_interface& producer) = 0;
        virtual bool unbind_channel(channel_id ch_id, producer_interface& producer) = 0;

        //virtual void publish(producer_interface& producer, producer_interface::publish_type value) = 0;
		//virtual void bind_channel(const channel_id::id_type& ch_id, consumer_interface& base) = 0;

        //virtual channel* const get_channel(const channel_id::id_type& ch_id) = 0;
    };
}

#endif
