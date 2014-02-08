
#ifndef LMQ_CONTEXT_HPP
#define LMQ_CONTEXT_HPP

#include <map>
#include "channel.hpp"

namespace lmq {

    class context {
        typedef std::map<channel::id_type, channel> container_type;
    public:
        /*static context& getContext() {
            static context ctx;
            return ctx;
        }*/

        void bind_channel(const channel::id_type channel_id, const consumer& c) {
            auto ch = get_existing_channel(channel_id);
            ch->add_consumer(c);
        }

        void bind_channel(const channel::id_type channel_id, const producer& p) {
            auto ch = get_existing_channel(channel_id);
            ch->add_producer(p);
        }

        container_type::size_type get_channel_count() const {
            return _channels.size();
        }

        container_type::size_type get_channel_count(const channel::id_type& channel_id) const {
            return _channels.count(channel_id);
        }

        const channel* const get_channel(const channel::id_type& channel_id) const {
            const auto itt = _channels.find(channel_id);
            const bool exists = _channels.end() != itt;
            const channel* ch_ret = nullptr;
            if(exists) {
                ch_ret = &(itt->second);
            }
            return ch_ret;
        }

    private:
        bool channel_exists(const channel::id_type& channel_id) {
            const auto it = _channels.find(channel_id);
            return _channels.end() != it;
        }

        channel* const get_existing_channel(const channel::id_type channel_id) {
            bool exists = channel_exists(channel_id);
            if(!exists) {
                _channels.emplace(std::make_pair(channel_id, channel(channel_id)));
            }
            return &_channels.at(channel_id);
        }

        container_type _channels;
    };
}

#endif
