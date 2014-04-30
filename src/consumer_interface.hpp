
#ifndef LMQ_CONSUMER_INTERFACE_HPP
#define LMQ_CONSUMER_INTERFACE_HPP

#include "bindable.hpp"

namespace lmq {

	struct consumer_interface : public bindable {
		consumer_interface(const_context_type ctx)
			:bindable(ctx) {
		};

		using const_msg_type = const message_factory::message;
		virtual void consume(std::shared_ptr<const_msg_type> msg) = 0;
	};

}

#endif
