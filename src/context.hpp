
#ifndef LMQ_CONTEXT_HPP
#define LMQ_CONTEXT_HPP

#include <map>

#include "channel.hpp"
#include "message_factory.hpp"

namespace lmq {

    class context : public context_interface {
        typedef channel_id::id_type channel_id_type;
        typedef std::map<channel_id_type, channel> container_type;
    public:

        virtual void bind_channel(const channel_id_type& channel_id, consumer_base& c) {
            auto ch = get_existing_channel(channel_id);
            ch->add_consumer(&c);
        }

        virtual void bind_channel(const channel_id_type& channel_id, producer_base& p) {
            auto ch = get_existing_channel(channel_id);
            ch->add_producer(&p);
        }

        container_type::size_type get_channel_count() const {
            return _channels.size();
        }

        container_type::size_type get_channel_count(const channel_id_type& channel_id) const {
            return _channels.count(channel_id);
        }

        virtual const channel* const get_channel(const channel_id_type& channel_id) const {
            const auto itt = _channels.find(channel_id);
            const bool exists = _channels.end() != itt;
            const channel* ch_ret = nullptr;
            if(exists) {
                ch_ret = &(itt->second);
            }
            return ch_ret;
        }

        message_factory& get_message_factory() {
            return _msg_factory;
        }

    private:
        bool channel_exists(const channel_id_type& channel_id) {
            const auto it = _channels.find(channel_id);
            return _channels.end() != it;
        }

        channel* const get_existing_channel(const channel_id_type& channel_id) {
            bool exists = channel_exists(channel_id);
            if(!exists) {
                _channels.emplace(channel_id, channel(channel_id));
            }
            return &_channels.at(channel_id);
        }

        container_type _channels;
        message_factory _msg_factory;
    };
}

#endif
