
#ifndef LMQ_CONSUMER_INTERFACE_HPP
#define LMQ_CONSUMER_INTERFACE_HPP

#include "bindable.hpp"

namespace lmq {

	struct consumer_interface : public bindable {
		consumer_interface(ctx_type ctx)
			:bindable(ctx) {
		};

		using const_msg_type = const message_factory::message;
        template<typename T>
		void consume(T value) = 0;
	};

}

#endif
