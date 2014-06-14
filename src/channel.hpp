
#ifndef LMQ_CHANNEL_HPP
#define LMQ_CHANNEL_HPP

#include <list>
#include <algorithm>


#include "consumer_interface.hpp"
#include "producer_interface.hpp"
#include "message_factory.hpp"
#include "context_interface.hpp"

namespace lmq {

    //struct channel_interface {
    //    using id_type = channel_id::id_type;
    //private:
    //    id_type _channel_id;
    //};

    // USE POINTER FOR CONTENT OF LISTS
    // UNIQUE PTR? AUTO PTR?
    struct channel {
		using id_type = channel_id::id_type;

		using consumer_const_ptr_type = consumer_interface* const;
		using consumer_list = std::list<consumer_const_ptr_type>;

		using producer_const_ptr_type = producer_interface* const;
        using producer_list = std::list<producer_const_ptr_type>;

		using const_msg_type = message_factory::message;

        channel(const id_type& id)
        :_channel_id(id) {
        }

        const id_type get_id() const {
            return _channel_id;
        }

        //void add_consumer(consumer_const_ptr_type consumer) {
        //    _consumers.push_back(consumer);
        //}

        void add_producer(producer_const_ptr_type producer) {
            m_producers.push_back(producer);
        }

        bool remove(producer_const_ptr_type producer) {
            const auto itt_end = std::end(m_producers);
            const auto itt = std::find_if(
                std::begin(m_producers),
                itt_end,
                [&] (const lmq::producer_interface* p) {
                    return producer == p;
                });
            const bool found = itt_end != itt;
            if (found) {
                m_producers.erase(itt);
            }
            return found;
        }

        //const consumer_list& get_consumers() const {
        //    return _consumers;
        //}

        const producer_list& get_producers() const {
            return m_producers;
        }

        //template<typename T>
        //void push(T value) {
        //    auto shared_ptr_msg = std::make_shared<const_msg_type>(value);
        //    for(auto cons : _consumers) {
        //        cons->consume(value);
        //    }            
        //}

    private:
        id_type _channel_id;
        producer_list m_producers;
        consumer_list _consumers;
    };
}

#endif
