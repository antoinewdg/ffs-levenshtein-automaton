//
// Created by antoinewdg on 16/07/16.
//

#include "state.h"

namespace ffs {
    State State::reduced_union(const vector<State> &states) {
        vector<const_iterator> its(states.size());
        vector<Position> result;

        for (int i = 0; i < states.size(); i++) {
            its[i] = states[i].begin();
        }

        auto get_minimum_index = [&its, &states]() -> int {
            Position minimum_pos = Position::max_value();
            int min_i = -1;
            for (int i = 0; i < its.size(); i++) {
                if (its[i] != states[i].end() && *(its[i]) < minimum_pos) {
                    min_i = i;
                    minimum_pos = *(its[i]);
                }
            }

            return min_i;
        };

        auto can_candidate_be_added = [&result](const Position &candidate) -> bool {
            for (const Position &p : result) {
                if (candidate.is_subsumed(p)) { return false; }
            }
            return true;
        };

        while (true) {
            int i = get_minimum_index();

            // Return if all iterators are invalid
            if (i < 0) { break; }

            const Position &candidate(*(its[i]));
            if (can_candidate_be_added(candidate)) {
                result.push_back(candidate);
            }
            its[i]++;
        }

        State state;
        state._positions = result;

        auto comp = [](const State &s, const State &t) { return s._minimum_boundary < t._minimum_boundary; };
        auto it = std::min_element(states.begin(), states.end(), comp);
        state._minimum_boundary = it->_minimum_boundary;

        return state;
    }
}