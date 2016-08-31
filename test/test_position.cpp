//
// Created by antoinewdg on 18/06/16.
//
#include <iostream>
#include "catch.hpp"
#include "position.h"

using std::cout;
using std::endl;
using std::vector;
using namespace ffs;

TEST_CASE("Position equality operators") {
    REQUIRE(Position(0, 0) == Position(0, 0));
    REQUIRE(Position(0, 0) != Position(-1, 0));
    REQUIRE(Position(0, 0) != Position(0, 1));
    REQUIRE(Position(0, 0) != Position(1, -1));
}

TEST_CASE("Position transition works as expected", "[Position]") {
    Position p(0, 0);
    vector<Position> expected;

    expected = {Position(1, 0)};
    REQUIRE(p.transition({1, 0}, 3) == expected);
    REQUIRE(p.transition({1, 1, 1, 0, 1}, 3) == expected);
    REQUIRE(p.transition({1, 0, 0, 0, 0}, 3) == expected);

    expected = {Position(0, 1), Position(1, 1)};
    REQUIRE(p.transition({0}, 3) == expected);
    REQUIRE(p.transition({0, 0, 0}, 3) == expected);

    expected = {Position(0, 1), Position(1, 1), Position(2, 1)};
    REQUIRE(p.transition({0, 1, 0}, 3) == expected);
    REQUIRE(p.transition({0, 1, 1}, 3) == expected);

    expected = {Position(0, 1), Position(1, 1), Position(4, 3)};
    REQUIRE(p.transition({0, 0, 0, 1}, 3) == expected);
    REQUIRE(p.transition({0, 0, 0, 1, 1, 1}, 3) == expected);
    REQUIRE(p.transition({0, 0, 0, 1, 0, 0}, 3) == expected);

    expected = {Position(0, 1)};
    REQUIRE(p.transition({}, 3) == expected);
}

TEST_CASE("Position transition removes non tolerated results") {
    Position p(0, 1);

    REQUIRE(p.transition({1, 0}, 1) == vector<Position>{Position(1, 1)});
    REQUIRE(p.transition({0, 0}, 1) == vector<Position>{});
    REQUIRE(p.transition({}, 1) == vector<Position>{});
}

TEST_CASE("0#0 subsumes 0#1, 1#1, -1#1 and 2#2 but not 3#2 nor 1#0") {
    Position p(0, 0);

    REQUIRE(p.subsumes(Position(0, 1)));
    REQUIRE(p.subsumes(Position(1, 1)));
    REQUIRE(p.subsumes(Position(-1, 1)));
    REQUIRE(p.subsumes(Position(2, 2)));

    REQUIRE(!p.subsumes(Position(3, 2)));
    REQUIRE(!p.subsumes(Position(1, 0)));
}

TEST_CASE("0#1 is subsumed by itself, 0#0, 1#0 and -1#0, but not by 2#0 nor -1#1") {
    Position p(0, 1);

    REQUIRE(p.is_subsumed(p));
    REQUIRE(p.is_subsumed(Position(0, 0)));
    REQUIRE(p.is_subsumed(Position(1, 0)));
    REQUIRE(p.is_subsumed(Position(-1, 0)));

    REQUIRE(!p.is_subsumed(Position(2, 0)));
    REQUIRE(!p.is_subsumed(Position(-1, 1)));
}

TEST_CASE("0#1 < 1#1, 0#1 < 0#2, 0#1 < -4#2 and 0#0 < 0#1") {
    REQUIRE(Position(0, 1) < Position(1, 1));
    REQUIRE(Position(0, 1) < Position(0, 2));
    REQUIRE(Position(0, 1) < Position(-4, 2));
    REQUIRE(Position(0, 0) < Position(0, 1));
}


