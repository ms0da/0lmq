
#ifndef LMQ_BINDABLE_HPP
#define LMQ_BINDABLE_HPP

#include <list>

#include "context_interface.hpp"
#include "message.hpp"

namespace lmq {

    struct bindable {
        typedef const channel_id::id_type& const_channel_id_type;
        
        virtual void bind(const_channel_id_type ch_id) = 0;

    protected:
        typedef const context_interface& const_context_type;

        bindable(const_context_type ctx)
        :_ctx(const_cast<context_interface&>(ctx)) {
        }

        context_interface& get_context() const {
            return _ctx;
        }

    private:
        context_interface& _ctx;
    };

    struct consumer_base : public bindable {
        consumer_base(const_context_type ctx)
        :bindable(ctx) {
        };

        virtual void consume(const message& msg) =  0;
    };

    struct producer_base : public bindable {
        producer_base(const_context_type ctx)
        :bindable(ctx) {
        };

        virtual void publish(const message& msg) = 0;
    };
}

#endif
