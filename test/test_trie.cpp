#include <iostream>
#include <set>
#include "catch.hpp"
#include "trie.h"
#include "node_minimal.h"
#include <boost/version.hpp>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::set;
using namespace ffs;

TEST_CASE("Trie construction and destruction work") {
    std::initializer_list<string> init = {"abc", "abcd"};
    Trie<char, std::string> trie(init);

    vector<string> words = init;
    Trie<char> trie2(words.begin(), words.end());
}

TEST_CASE("Trie size") {
    Trie<char, std::string> a{},
            b{"cat", "dog", "mouse"},
            c{"cat", "dog", "mouse", "caterpillar"},
            d{"cat", "dog", "mouse", "cat"};

    REQUIRE(a.size() == 0);
    REQUIRE(b.size() == 3);
    REQUIRE(c.size() == 4);
    REQUIRE(d.size() == 3);
}

TEST_CASE("Trie lists words as expected") {
    set<string> words = {"cat", "dog", "caterpillar", "dogmatic", "chaos", "cream"};
    Trie<char, string> trie(words.begin(), words.end());
    std::list<string> result = trie.get_words();


    set<string> actual(result.begin(), result.end());

    REQUIRE(words == actual);
}

TEST_CASE("Trie iteration") {
    set<string> words = {"cat", "dog", "caterpillar", "dogmatic", "chaos", "cream"};
    Trie<char, string> trie(words.begin(), words.end());
    std::set<string> iteration(trie.begin(), trie.end());

    REQUIRE(iteration == words);
}

TEST_CASE("Trie empty iteration") {
    set<string> words = {};
    Trie<char, string> trie(words.begin(), words.end());
    std::set<string> iteration(trie.begin(), trie.end());

    REQUIRE(iteration == words);
}

TEST_CASE("Trie node iteration") {
    Trie<char, string> trie{"cat", "car", "dog", "cd"};
    typedef typename Trie<char, string>::node_ptr_type Node;
    Node root = trie.get_root();
    auto op = [](std::pair<char, Node> p) {
        return p.first;
    };
    auto get_children_key_set = [op](Node n) {
        vector<char> v(n->get_children().size());
        std::transform(n->begin_children(), n->end_children(), v.begin(), op);
        return set<char>(v.begin(), v.end());
    };

    REQUIRE(get_children_key_set(root) == set<char>({'c', 'd'}));
    Node a = root->get_children().at('c');
    REQUIRE(get_children_key_set(a) == set<char>({'a', 'd'}));
    Node b = a->get_children().at('a');
    REQUIRE(get_children_key_set(b) == set<char>({'t', 'r'}));
    Node c = b->get_children().at('t');
    REQUIRE(get_children_key_set(c) == set<char>());
    Node d = b->get_children().at('r');
    REQUIRE(get_children_key_set(d) == set<char>());
    Node e = a->get_children().at('d');
    REQUIRE(get_children_key_set(e) == set<char>());

    Node f = root->get_children().at('d');
    REQUIRE(get_children_key_set(f) == set<char>({'o'}));
    Node g = f->get_children().at('o');
    REQUIRE(get_children_key_set(g) == set<char>({'g'}));
    Node h = g->get_children().at('g');
    REQUIRE(get_children_key_set(h) == set<char>());

}
