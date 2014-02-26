
#ifndef LMQ_BINDABLE_HPP
#define LMQ_BINDABLE_HPP

#include "context_interface.hpp"

namespace lmq {

    class bindable {
        context_interface& _ctx;

    protected:
        typedef const context_interface& const_context_type;
        typedef const channel_id::id_type& const_channel_id_type;

        bindable(const_context_type ctx)
        :_ctx(const_cast<context_interface&>(ctx)) {
        }

        context_interface& get_context() {
            return _ctx;
        }

    public:
        virtual void bind(const_channel_id_type ch_id) = 0;
    };

    struct consumer_base : public bindable {
        consumer_base(const_context_type ctx)
        :bindable(ctx) {
        };
    };

    struct producer_base : public bindable {
        producer_base(const_context_type ctx)
        :bindable(ctx) {
        };
    };
}

#endif
