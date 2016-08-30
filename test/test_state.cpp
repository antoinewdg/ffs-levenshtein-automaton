#include <iostream>
#include "catch.hpp"
#include "state.h"

using std::cout;
using std::endl;
using std::vector;
using namespace ffs;

TEST_CASE("State construction sorts and finds minimum boundary") {
    State state({Position(1, 1), Position(0, 3), Position(2, 0)});
    vector<Position> expected_order = {Position(2, 0), Position(1, 1), Position(0, 3)};

    REQUIRE(std::equal(state.begin(), state.end(), expected_order.begin()));
    REQUIRE(state.get_minimum_boundary() == 0);
}

TEST_CASE("Reduced union keeps positions sorted") {
    State a = {Position(0, 0), Position(3, 1)},
            b = {Position(1, 0)},
            expected = {Position(0, 0), Position(1, 0), Position(3, 1)};

    REQUIRE(State::reduced_union({a, b}) == expected);
}

TEST_CASE("Reduced union eliminates subsumed position") {
    State a = {Position(0, 0), Position(3, 1)},
            b = {Position(1, 0)},
            c = {Position(1, 1)},
            expected = {Position(0, 0), Position(1, 0), Position(3, 1)};

    REQUIRE(State::reduced_union({a, b, c}) == expected);


    a = {Position(0, 3), Position(2, 3)},
    b = {Position(1, 3)},
    c = {Position(3, 1)},
    expected = {Position(3, 1), Position(0, 3)};

    REQUIRE(State::reduced_union({a, b, c}) == expected);
}

TEST_CASE("Reduced union eliminates duplicates") {
    State a = {Position(0, 1), Position(1, 1)},
            b = {Position(1, 1), Position(2, 1)},
            expected = {Position(0, 1), Position(1, 1), Position(2, 1)};

    REQUIRE(State::reduced_union({a, b}) == expected);
}
