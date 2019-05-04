#ifndef _INFRA_QUEUES_H_
#define _INFRA_QUEUES_H_

#include <queue>
#include <deque>
#include "../global.h"

namespace ai {

/**
 * deque is a Class that defines the solver of the problem.
 * It inherits the class std::deque.
 *
 * @author      Eduardo Culau
 * @version     1.8
 * @since       1.8
 */
template<
    class T,
    class Allocator = std::allocator<T>
>
class deque : public std::deque<T, Allocator>
{
public:

    /**
     * Find a state inside the deque
     *
     * @param  state the state
     * @return bool  true if the state is inside the deque
     */
    bool contains(const State &state) {
        auto nodeIt = this->begin();
        auto nodeLast = this->end();
        //Find the state inside the deque.
        for( ; nodeIt != nodeLast; ++nodeIt ){
            if( (*nodeIt)->getState() == state ){
                return true;
            }
        }
        return false;
    }    
};

/**
 * priority_queue is a Class that defines the solver of the problem.
 * It inherits the class std::priority_queue.
 *
 * @author      Eduardo Culau
 * @version     1.8
 * @since       1.8
 */
template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
>
class priority_queue : public std::priority_queue<T, Container, Compare>
{
public:
    typedef typename
        std::priority_queue<
        T,
        Container,
        Compare>::container_type::const_iterator const_iterator;

    /**
     * Find a something inside the priority_queue
     *
     * @param  val             thing
     * @return const_iterator  result (&thing) if inside else c.end().
     */
    const_iterator find(const T&val) const
    {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first!=last) {
            if (*first==val) return first;
            ++first;
        }
        return last;
    }

    /**
     * Find a state inside the priority_queue
     *
     * @param  state the state
     * @return bool  true if the state is inside the priority_queue
     */
    bool contains(const State &state) {
        auto nodeIt = this->c.begin();
        auto nodeLast = this->c.end();
        //Find the state inside the priority_queue.
        for( ; nodeIt != nodeLast; ++nodeIt ){
            if( (*nodeIt)->getState() == state ){
                return true;
            }
        }
        return false;
    }

    /**
     * Operator <<. So it's possible to print the Problem just put it on the std::cout method.
     *
     * @param  out           existing std::ostream
     * @param  problem       problem to be printed
     * @return std::ostream& std::ostream whith the State data
     * @see    std::ostream
     */  
    friend std::ostream& operator<< (std::ostream &out, const priority_queue& pq){
        auto nodeIt = pq.c.begin();
        auto nodeLast = pq.c.end();
        for( ; nodeIt != nodeLast; ++nodeIt ){
            out << (*nodeIt)->toStringFCost() << std::endl;
        }    
        return out;
    }
};



}

#endif

