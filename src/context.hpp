
#ifndef LMQ_CONTEXT_HPP
#define LMQ_CONTEXT_HPP

#include <map>

#include "channel.hpp"

namespace lmq {

    class context : public context_interface {
        using channel_id_type = channel_id::id_type;
        using container_type = std::map<channel_id_type, channel>;

        std::map<producer_interface * const, std::list<channel * const>> producer_channels;

    public:
        virtual void bind_channel(const channel_id_type& channel_id, producer_interface& producer) {
            auto ch = get_channel(channel_id);
            ch->add_producer(&producer);

            auto ch_list = producer_channels[&producer];
            ch_list.push_back(ch);
        }

        virtual void publish(producer_interface& producer, producer_interface::publish_type value) {
            auto ch_list = producer_channels[&producer];
            for (channel* const ch : ch_list) {
                ch->push(value);
            }
        }

        //virtual void bind_channel(const channel_id_type& channel_id, consumer_interface& c) {
        //    auto ch = get_channel(channel_id);
        //    ch->add_consumer(&c);
        //}

        //container_type::size_type get_channel_count() const {
        //    return _channels.size();
        //}

        //container_type::size_type get_channel_count(const channel_id_type& channel_id) const {
        //    return _channels.count(channel_id);
        //}

    private:
        channel* const get_channel(const channel_id_type& channel_id) {
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
