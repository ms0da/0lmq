
#ifndef LMQ_CONSUMER_HPP
#define LMQ_CONSUMER_HPP

#include "bindable.hpp"

namespace lmq {

    struct consumer : public bindable {
        consumer(const_context_type ctx)
        :bindable(ctx, true) {
        }
    };
}

#endif
