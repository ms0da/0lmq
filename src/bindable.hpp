
#ifndef LMQ_BINDABLE_HPP
#define LMQ_BINDABLE_HPP

//#include "locked_queue.hpp"
#include "context.hpp"

namespace lmq {

    class bindable {
        context& _ctx;
        const bool _is_consumer;

    protected:
        typedef const context& const_context_type;
        typedef const channel_id::id_type& const_channel_id_type;

        bindable(const_context_type ctx, const bool is_consumer)
        :_ctx(const_cast<context&>(ctx)), _is_consumer(is_consumer) {
        }

    public:
        void bind(const_channel_id_type channel_id) {
            _ctx.bind_channel(channel_id, this, _is_consumer);
        }
    };
}

#endif
