
#ifndef LMQ_BINDABLE_HPP
#define LMQ_BINDABLE_HPP

namespace lmq {

    class bindable {};
    class consumer : public bindable {};
    class producer : public bindable {};

    /*struct bindable {
        bindable(const context& ctx, const bool is_producer)
        :_ctx(ctx), _is_producer(is_producer) {
        }
        
        void bind(const channel::id_type channel_id) {
            _ctx.bind_channel(channel_id,  _is_producer, *this);
        }

    private:
        const context& _ctx;
        const bool _is_producer;
    };*/


}

#endif
