cmake_minimum_required(VERSION 3.5)
project(ffs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wreturn-type")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES
        src/bit_vector.cpp src/bit_vector.h
        src/position.h src/position.cpp
        src/parametrized_state.h
        src/universal_automaton.cpp src/universal_automaton.h
        src/state.cpp src/state.h
        src/node_minimal.h src/trie/node.h src/trie.h src/trie/depth_first_iterator.h)

set(TEST_FILES
        test/main.cpp
        test/test_position.cpp
        test/test_bit_vector.cpp
        src/parametrized_state.cpp
        test/test_parametrized_state.cpp
        test/test_state.cpp test/test_trie.cpp)

include_directories(src)
include_directories(lib)

add_executable(ffs ${SOURCE_FILES})
add_executable(run_tests ${SOURCE_FILES} ${TEST_FILES})