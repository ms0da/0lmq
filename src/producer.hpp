
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
			if(0 == _channels.count(ch_id)) {
				context_interface& ctx = get_context();
				ctx.bind_channel(ch_id, *this);
				auto ch = ctx.get_channel(ch_id);
				_channels.emplace(std::make_pair(ch_id, ch));
			}
        }

        virtual bool publish(const_msg_ref_type msg, const_channel_id_type ch_dest) {
            auto elem = _channels.find(ch_dest);
			const bool channel_exists = end(_channels) != elem;
            // if a channel exists
            if(channel_exists) {
                elem->second->push(msg);
            }
			return channel_exists;
        }

        size_type get_bound_channel_count() {
            return _channels.size();
        }

	private:
		container_type _channels;
    };
}

#endif
