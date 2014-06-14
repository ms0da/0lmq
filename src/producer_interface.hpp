
#ifndef LMQ_PRODUCER_INTERFACE_HPP
#define LMQ_PRODUCER_INTERFACE_HPP

#include "bindable.hpp"

namespace lmq {

	struct producer_interface : public bindable {
		producer_interface(ctx_type ctx)
		:bindable(ctx) {
		};

		using publish_type = const int&; 
		virtual void publish(publish_type value) = 0;
	};

}

#endif
