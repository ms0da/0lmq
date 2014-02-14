
#ifndef LMQ_LOCKED_QUEUE_HPP
#define LMQ_LOCKED_QUEUE_HPP

#include <list>
#include <mutex>

namespace lmq {

    template<typename T>
    struct locked_queue {
        typedef T elem_type;        
    private:
        typedef std::mutex mutex_type;
        typedef std::lock_guard<mutex_type> lock_type;
        typedef std::list<elem_type> list_type;
    public:
        typedef typename list_type::size_type size_type;

        bool empty() const {
            return _list.empty();
        }

        void push_back(const elem_type& e) {
            lock_type lock(_mutex);
            _list.emplace_back(e);
        }

        const elem_type& front() {
            lock_type lock(_mutex);
            return _list.front();
        }

        void pop_front() {
            lock_type lock(_mutex);
            _list.pop_front();
        }

        size_type size() const {
            return _list.size();
        }
        
        void clear() {
            lock_type lock(_mutex);
            _list.clear();
        }

    private:
        list_type _list;
        mutex_type _mutex;
    };
}

#endif
