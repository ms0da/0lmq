
#ifndef LMQ_PRODUCER_HPP
#define LMQ_PRODUCER_HPP

#include <map>

#include "producer_interface.hpp"
#include "channel.hpp"

namespace lmq {

    class producer : public producer_interface {
		using container_type = std::map<const channel_id::id_type, channel* const>;

	public:
        using size_type = container_type::size_type;

        producer(const_context_type ctx)
        :producer_interface(ctx) {
        }

        virtual void bind(const_channel_id_type ch_id) {
			context_interface& ctx = get_context();
			ctx.bind_channel(ch_id, *this);
        }

        virtual void publish(publish_type value) {
            context_interface& ctx = get_context();
            ctx.publish(*this, value);
        }
    };
}

#endif
