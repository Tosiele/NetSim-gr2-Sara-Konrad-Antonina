#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "storage_types.hpp"

template<class Node>
class NodeCollection {

    public:
        using container_t = typename std::list<Node>;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

    private:

};

class Factory{
    public:


    private:
        template<class Node>
        void remove_receiver(NodeCollection<Node>& collection, ElementID id);



}

#endif //FACTORY_HPP