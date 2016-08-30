//
// Created by antoinewdg on 30/08/16.
//

#ifndef FFS_TRIE_H
#define FFS_TRIE_H

#include <vector>
#include <list>

#include "trie/node.h"
#include "trie/depth_first_iterator.h"

namespace ffs {
    template<class Symbol, class Word=std::vector<Symbol>>
    class Trie {
    public:
        typedef Trie<Symbol, Word> self_type;
        typedef TrieNode<Symbol, Word> node_type;
        typedef typename node_type::ptr_type node_ptr_type;
        typedef ConstDepthFirstTrieIterator<Symbol, Word> const_iterator;

        template<class InputIterator>
        Trie(InputIterator begin, InputIterator end) : m_size(0) {
            for (auto it = begin; it != end; it++) {
                _add_word_to_node(m_root, it->begin(), it->end());
            }
        }

        Trie(const std::initializer_list<Word> &l) : Trie(l.begin(), l.end()) {}

        Trie() : Trie({}) {}

        std::list<Word> get_words() {
            std::list<Word> words;
            if (m_root != nullptr) {
                _fill_list_of_words(m_root, words, std::list<Symbol>());
            }
            return words;
        }

        size_t size() const {
            return m_size;
        }

        node_ptr_type get_root() const {
            return m_root;
        }

        const_iterator begin() const {
            return const_iterator(m_root);
        }

        const_iterator end() const {
            return const_iterator();
        };


    private:

        template<class InputIterator>
        void _add_word_to_node(node_ptr_type &node, InputIterator begin, InputIterator end) {
            if (node == nullptr) {
                node = std::make_shared<node_type>();
            }
            if (begin == end) {
                m_size += !node->m_final;
                node->m_final = true;
                return;
            }
            _add_word_to_node(node->m_children[*begin], begin + 1, end);
        }

        void _fill_list_of_words(node_ptr_type node, std::list<Word> &words, const std::list<Symbol> &current_word) {
            if (node->m_final) {
                words.emplace_back(current_word.begin(), current_word.end());
            }
            for (auto it = node->begin_children(); it != node->end_children(); it++) {
                std::list<Symbol> new_word(current_word);
                new_word.push_back(it->first);
                _fill_list_of_words(it->second, words, new_word);
            }
        }

        node_ptr_type m_root;
        size_t m_size;

    };
}

#endif //FFS_TRIE_H
