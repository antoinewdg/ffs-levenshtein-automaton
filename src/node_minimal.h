//
// Created by antoinewdg on 24/07/16.
//

#ifndef FFS_NODE_MINIMAL_H
#define FFS_NODE_MINIMAL_H

#include <unordered_map>
#include <memory>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>


//class Node {
//public:
//    typedef std::unique_ptr<Node> ptr_type;
//    typedef std::unordered_map<char, ptr_type> map_type;
//
//    class const_iterator : public boost::iterator_facade<
//            const_iterator,
//            pair<char, const Node &>,
//            boost::forward_traversal_tag> {
//    public:
//        const_iterator() {}
//
//        const_iterator(map_type::const_iterator base) : base(base) {}
//
//    private:
//        friend class boost::iterator_core_access;
//
//        void increment() { base++; }
//
//        bool equal(const_iterator const &other) const {
//            return this->base == other.base;
//        }
//
//        pair<char, const Node &> const &dereference() const {
//            return pair<char, const Node &>(base->first, *(base->second));
//        }
//
//
//        map_type::const_iterator base;
//    };
//
//
//    const_iterator begin() const {
//        return const_iterator(_children.begin());
//    }
//
//    const_iterator end() const {
//        return const_iterator(_children.end());
//    }
//
//private:
//    map_type _children;
//};

#endif //FFS_NODE_MINIMAL_H
