#include <iostream>
#include <unordered_map>
#include "catch.hpp"
#include "bit_vector.h"

using std::cout;
using std::endl;
using std::unordered_map;
using std::pair;
using namespace ffs;

TEST_CASE("BitVector iterators") {
    BitVector b = {1, 0, 0};
    auto it = b.begin();

    REQUIRE(*it == 1);
    REQUIRE(*(++it) == 0);
    REQUIRE(*(++it) == 0);
    REQUIRE(++it == b.end());
}

TEST_CASE("BitVector insertion") {
    BitVector b = {1};
    b << 0;
    REQUIRE(b == BitVector({1, 0}));
    b << 1;
    REQUIRE(b == BitVector({1, 0, 1}));
}


TEST_CASE("BitVector generation for max_size=0") {
    vector<BitVector> generated = BitVector::generate_all(0);
    vector<BitVector> expected = {{}};

    REQUIRE(generated == expected);
}

TEST_CASE("BitVector generation for max_size=1") {
    vector<BitVector> generated = BitVector::generate_all(1);
    vector<BitVector> expected = {
            {},
            {0},
            {1}
    };

    REQUIRE(generated == expected);
}


TEST_CASE("BitVector generation for max_size=3") {
    vector<BitVector> generated = BitVector::generate_all(3);
    vector<BitVector> expected = {
            {},
            {0},
            {1},
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1},
            {0, 0, 0},
            {0, 0, 1},
            {0, 1, 0},
            {0, 1, 1},
            {1, 0, 0},
            {1, 0, 1},
            {1, 1, 0},
            {1, 1, 1},

    };

    REQUIRE(generated == expected);
}

TEST_CASE("BitVector hash does not lead to collisions") {
    vector<BitVector> generated = BitVector::generate_all(8);
    unordered_map<size_t, int> counts;


    for (const BitVector &b : generated) {
        auto h = std::hash<BitVector>()(b);
        counts[h]++;
    }

    bool collision_happened = std::any_of(
            counts.begin(), counts.end(),
            [](const pair<size_t, int> &p) {
                return p.second > 1;
            }
    );

    REQUIRE(!collision_happened);

}

TEST_CASE("Sub bit vector") {
    BitVector b({1, 0, 0, 1, 0});

    REQUIRE(b.sub(0, 5) == b);
    REQUIRE(b.sub(2, 5) == BitVector({0, 1, 0}));
    REQUIRE(b.sub(0, 2) == BitVector({1, 0}));
    REQUIRE(b.sub(1, 4) == BitVector({0, 0, 1}));
}