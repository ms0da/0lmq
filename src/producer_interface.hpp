
#ifndef LMQ_PRODUCER_INTERFACE_HPP
#define LMQ_PRODUCER_INTERFACE_HPP

#include "bindable.hpp"

namespace lmq {

	struct producer_interface : public bindable {
		producer_interface(const_context_type ctx)
			:bindable(ctx) {
		};

		using const_msg_ref_type = const message_factory::message&;
		virtual bool publish(const_msg_ref_type, const_channel_id_type ch_dest) = 0;
	};

}

#endif
