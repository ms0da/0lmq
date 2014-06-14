
#ifndef LMQ_BINDABLE_HPP
#define LMQ_BINDABLE_HPP

#include <list>

#include "context_interface.hpp"
#include "message_factory.hpp"

namespace lmq {

    struct bindable {
        using const_channel_id_type = const channel_id::id_type&;
        virtual void bind(const_channel_id_type ch_id) = 0;
        virtual bool unbind(const_channel_id_type ch_id) = 0;

    protected:
        using ctx_type = context_interface&;
        bindable(ctx_type ctx)
        :_ctx(ctx) {
        }

        ctx_type& get_context() const {
            return _ctx;
        }

    private:
        ctx_type& _ctx;
    };
}

#endif
