//
// Created by antoinewdg on 30/08/16.
//

#ifndef FFS_TRIE_NODE_H
#define FFS_TRIE_NODE_H

#include <memory>
#include <unordered_map>

namespace ffs {
    template<class Symbol, class Word>
    class Trie;

    template<class Symbol, class Word>
    class TrieNode {
    public:
        friend class Trie<Symbol, Word>;

        typedef TrieNode<Symbol, Word> self_type;
        typedef std::shared_ptr<self_type> ptr_type;
        typedef std::unordered_map<Symbol, ptr_type> map_type;
        typedef typename map_type::const_iterator const_iterator;


        TrieNode() : m_final(false) {}

        const_iterator begin_children() const {
            return m_children.begin();
        }

        const_iterator end_children() const {
            return m_children.end();
        }

        bool is_final() const {
            return m_final;
        }

        const map_type &get_children() const {
            return m_children;
        }


    private:

        map_type m_children;
        bool m_final;
    };
}


#endif //FFS_NODE_H
