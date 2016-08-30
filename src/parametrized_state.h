//
// Created by antoinewdg on 18/06/16.
//

#ifndef FFS_PARAMETRIZED_STATE_H
#define FFS_PARAMETRIZED_STATE_H


#include <vector>
#include <iostream>
#include <algorithm>

#include "bit_vector.h"
#include "position.h"
#include "state.h"

using std::vector;
using std::ostream;
using std::string;
using std::initializer_list;
using std::none_of;
using std::pair;

namespace ffs {


    struct ParametrizedState {

        ParametrizedState(const vector<Position> &positions) : positions(positions) { }

        ParametrizedState(const initializer_list<Position> &positions) : positions(positions) { }

        static vector<ParametrizedState> generate_all(int tolerance);

        static pair<int, ParametrizedState> parametrized_from_state(State state);

        pair<int, ParametrizedState> transition(const BitVector &b) const;

        State positions;
    };


    inline ostream &operator<<(ostream &out, const ParametrizedState &s) {
        out << '(';
        for (auto it = s.positions.begin(); it != s.positions.end(); it++) {
            if (it != s.positions.begin()) { out << ", "; }
            out << *it;
        }
        out << ')';

        return out;
    }

    inline bool operator==(const ParametrizedState &s, const ParametrizedState &t) {
        return s.positions == t.positions;
    }

    inline bool operator!=(const ParametrizedState &s, const ParametrizedState &t) {
        return s.positions != t.positions;
    }
}


namespace std {
    template<>
    struct hash<ffs::ParametrizedState> {
        size_t operator()(const ffs::ParametrizedState &state) const {
            size_t seed = state.positions.size();
            for (const ffs::Position &p : state.positions) {
                seed ^= p.i + 78 * p.e + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}
#endif //FFS_PARAMETRIZED_STATE_H
