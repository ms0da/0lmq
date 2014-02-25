
#ifndef LMQ_PRODUCER_HPP
#define LMQ_PRODUCER_HPP

#include "bindable.hpp"

namespace lmq {

    struct producer : public bindable {
        producer(const_context_type ctx)
        :bindable(ctx, false) {
        }
    };
}

#endif
