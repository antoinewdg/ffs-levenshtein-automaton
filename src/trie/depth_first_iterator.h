//
// Created by antoinewdg on 30/08/16.
//

#ifndef FFS_TRIE_DEPTH_FIRST_ITERATOR_H
#define FFS_TRIE_DEPTH_FIRST_ITERATOR_H

#include <boost/iterator/iterator_facade.hpp>
#include <list>

#include "node.h"

namespace ffs {
    template<class Symbol, class Word>
    class ConstDepthFirstTrieIterator
            : public boost::iterator_facade<
                    ConstDepthFirstTrieIterator<Symbol, Word>, const Word, boost::forward_traversal_tag
            > {
    public:
        typedef ConstDepthFirstTrieIterator<Symbol, Word> self_type;
        typedef TrieNode <Symbol, Word> node_type;
        typedef typename node_type::ptr_type node_ptr_type;
        typedef std::pair<node_ptr_type, std::list<Symbol>> pair_type;

        ConstDepthFirstTrieIterator() : m_node(nullptr) {};

        ConstDepthFirstTrieIterator(node_ptr_type root) : ConstDepthFirstTrieIterator() {
            if (root != nullptr) {
                m_stack.emplace_back(root, std::list<Symbol>());
                increment();
            }
        }

    private:
        friend class boost::iterator_core_access;

        void increment() {
            while (!m_stack.empty()) {
                pair_type p = m_stack.back();
                m_stack.pop_back();
                for (auto it = p.first->begin_children(); it != p.first->end_children(); it++) {
                    std::list<Symbol> new_word(p.second);
                    new_word.push_back(it->first);
                    m_stack.emplace_back(it->second, new_word);
                }
                if (p.first->is_final()) {
                    m_word = Word(p.second.begin(), p.second.end());
                    m_node = p.first;
                    return;
                }
            }
            m_node = nullptr;

        }


        bool equal(self_type const &other) const {
            return this->m_node == other.m_node;
        }

        Word const &dereference() const { return m_word; }

        node_ptr_type m_node;
        Word m_word;
        std::list<pair_type> m_stack;

    };
}

#endif //FFS_TRIE_DEPTH_FIRST_ITERATOR_H
