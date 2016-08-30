#include "catch.hpp"

#include "parametrized_state.h"

using namespace ffs;

TEST_CASE("ParametrizedState transition") {
    ParametrizedState state = {Position(0, 1), Position(1, 1)},
            expected = {Position(0, 2), Position(1, 2), Position(2, 2)};
    auto result = state.transition({0, 0, 0});

    REQUIRE(result.first == 0);
    REQUIRE(result.second == expected);

    expected = {Position(2, 1), Position(0, 2)};
    result = state.transition({0, 1, 0});

    REQUIRE(result.first == 0);
    REQUIRE(result.second == expected);

    expected = {Position(0, 1)};
    result = state.transition({1, 0, 0});

    REQUIRE(result.first == 1);
    REQUIRE(result.second == expected);


}

TEST_CASE("Generation of all parametrized states for n=1") {
    vector<ParametrizedState> generated = ParametrizedState::generate_all(1);
    vector<ParametrizedState> expected = {
            {Position(0, 0)},
            {Position(0, 1)},
            {Position(0, 1), Position(1, 1)},
            {Position(0, 1), Position(2, 1)},
            {Position(0, 1), Position(1, 1), Position(2, 1)},
    };

    REQUIRE(generated == expected);

}

TEST_CASE("Generation of all parametrized states for n=2") {
    vector<ParametrizedState> generated = ParametrizedState::generate_all(2);
    vector<ParametrizedState> expected = {
            {Position(0, 0)},
            {Position(0, 1)},
            {Position(0, 2)},
            {Position(0, 1), Position(1, 1)},
            {Position(0, 1), Position(2, 1)},
            {Position(0, 1), Position(2, 2)},
            {Position(0, 1), Position(3, 2)},
            {Position(0, 2), Position(2, 1)},
            {Position(0, 2), Position(3, 1)},
            {Position(0, 2), Position(1, 2)},
            {Position(0, 2), Position(2, 2)},
            {Position(0, 2), Position(3, 2)},
            {Position(0, 2), Position(4, 2)},
            {Position(0, 1), Position(1, 1), Position(2, 1)},
            {Position(0, 1), Position(1, 1), Position(3, 2)},
            {Position(0, 1), Position(2, 2), Position(3, 2)},
            {Position(0, 2), Position(2, 1), Position(3, 1)},
            {Position(0, 2), Position(2, 1), Position(4, 2)},
            {Position(0, 2), Position(3, 1), Position(1, 2)},
            {Position(0, 2), Position(1, 2), Position(2, 2)},
            {Position(0, 2), Position(1, 2), Position(3, 2)},
            {Position(0, 2), Position(1, 2), Position(4, 2)},
            {Position(0, 2), Position(2, 2), Position(3, 2)},
            {Position(0, 2), Position(2, 2), Position(4, 2)},
            {Position(0, 2), Position(3, 2), Position(4, 2)},
            {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)},
            {Position(0, 2), Position(1, 2), Position(2, 2), Position(4, 2)},
            {Position(0, 2), Position(1, 2), Position(3, 2), Position(4, 2)},
            {Position(0, 2), Position(2, 2), Position(3, 2), Position(4, 2)},
            {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2), Position(4, 2)},
    };
    REQUIRE(generated == expected);

}

TEST_CASE("Generation of all parametrized states for n=3") {
    vector<ParametrizedState> generated = ParametrizedState::generate_all(3);
    REQUIRE(generated.size() == 196);
}

TEST_CASE("Generation of all parametrized states for n=4") {
    vector<ParametrizedState> generated = ParametrizedState::generate_all(4);
    REQUIRE(generated.size() == 1353);
}

TEST_CASE("Parametrized state from positions") {
    State state = {Position(1, 1), Position(2, 1)};
    ParametrizedState expected = {Position(0, 1), Position(1, 1)};
    auto result = ParametrizedState::parametrized_from_state(state);

    REQUIRE(result.first == 1);
    REQUIRE(result.second == expected);

}

TEST_CASE("Parametrized state from positions with min boundary not on first element") {
    State state = {Position(1, 1), Position(2, 1), Position(0, 1)};
    ParametrizedState expected = {Position(1, 1), Position(2, 1), Position(0, 1)};
    auto result = ParametrizedState::parametrized_from_state(state);

    REQUIRE(result.first == 0);
    REQUIRE(result.second == expected);

}