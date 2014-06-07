
#ifndef LMQ_CONSUMER_HPP
#define LMQ_CONSUMER_HPP

#include <list>

#include "consumer_interface.hpp"

namespace lmq {

	struct consumer : public consumer_interface {
        consumer(const_context_type ctx)
		:consumer_interface(ctx) {
        }

        virtual void bind(const_channel_id_type ch_id) {
            get_context().bind_channel(ch_id, *this);
        }

        template<typename T>
        virtual void consume(std::shared_ptr<T> msg) {
            _msgs.push_back(msg);
        }

        const message_factory::message* const get_message() const {
            return _msgs.empty() ? nullptr : _msgs.front().get();
        }

        void next_message() {
            if(!_msgs.empty()) {
                _msgs.pop_front();
            }
        }

    private:
		using container_type = std::list<std::shared_ptr<const_msg_type>>;
        container_type _msgs;
    };
}

#endif
