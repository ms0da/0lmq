
#ifndef LMQ_PRODUCER_HPP
#define LMQ_PRODUCER_HPP

#include <map>

#include "bindable.hpp"
#include "channel.hpp"

namespace lmq {

    class producer : public producer_base {
        typedef std::map<const channel_id::id_type, channel* const> container_type;
        container_type _channels;

    public:
        typedef container_type::size_type size_type;

        producer(const_context_type ctx)
        :producer_base(ctx) {
        }

        virtual void bind(const_channel_id_type ch_id) {
            context_interface& ctx = get_context();
            ctx.bind_channel(ch_id, *this);
            auto ch = ctx.get_channel(ch_id);
            _channels.emplace(std::make_pair(ch_id, ch));
        }

        virtual void publish(const_msg_ref_type msg, const_channel_id_type ch_dest) {
            auto elem = _channels.find(ch_dest);
            // if channel exists
            if(end(_channels) != elem) {
                elem->second->push(msg);
            }
        }

        size_type get_bound_channel_count() {
            return _channels.size();
        }
    };
}

#endif
