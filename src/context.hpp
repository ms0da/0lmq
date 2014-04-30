
#ifndef LMQ_CONTEXT_HPP
#define LMQ_CONTEXT_HPP

#include <map>

#include "channel.hpp"
#include "message_factory.hpp"

namespace lmq {

    class context : public context_interface {
		using channel_id_type = channel_id::id_type ;
		using container_type = std::map<channel_id_type, channel>;

    public:
        virtual void bind_channel(const channel_id_type& channel_id, consumer_interface& c) {
            auto ch = get_channel(channel_id);
            ch->add_consumer(&c);
        }

		virtual void bind_channel(const channel_id_type& channel_id, producer_interface& p) {
            auto ch = get_channel(channel_id);
            ch->add_producer(&p);
        }

        container_type::size_type get_channel_count() const {
            return _channels.size();
        }

        container_type::size_type get_channel_count(const channel_id_type& channel_id) const {
            return _channels.count(channel_id);
        }

        virtual channel* const get_channel(const channel_id_type& channel_id) {
            auto itt = _channels.find(channel_id);
            bool exists = end(_channels) != itt;
            channel* ch_ret = nullptr;
            if(exists) {
                ch_ret = &itt->second;
            } else {
                ch_ret = create_new_channel(channel_id);
            }
            return ch_ret;
        }

        message_factory& get_message_factory() {
            return _msg_factory;
        }

    private:
        channel* const create_new_channel(const channel_id_type& ch_id) {
            _channels.emplace(ch_id, channel(ch_id));
            return &_channels.at(ch_id);
        }

        bool channel_exists(const channel_id_type& channel_id) {
            const auto it = _channels.find(channel_id);
            return _channels.end() != it;
        }

        container_type _channels;
        message_factory _msg_factory;
    };
}

#endif
