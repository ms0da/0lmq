
#ifndef LMQ_MESSAGE_FACTORY_HPP
#define LMQ_MESSAGE_FACTORY_HPP

#include <map>
#include <memory>

#include <iostream>

namespace lmq {

    struct message_factory {

		//template<typename T>
		struct message {
			using value_type = int;

			message(const value_type& value)
				:_value(value) {
			}

			const value_type& get_ref() const {
				return _value;
			}

		private:
			const value_type _value;
		};
    };
}

#endif
