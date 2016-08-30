#include "parametrized_state.h"

namespace ffs {
    list<Position> get_next_candidates(int tolerance, const vector<Position> &current) {
        const Position &base = current[0], &back = current.back();
        list<Position> result;
        int i0 = base.i + base.e;

        int e0 = 0;

        if (back != base) {
            e0 = back.e + 1;
            for (int j = back.i + 1; j <= i0 + back.e; j++) {
                result.push_back(Position(j, back.e));
            }
        }


        for (int f = e0; f <= tolerance; f++) {
            for (int j = i0 - f; j <= i0 + f; j++) {
                result.push_back(Position(j, f));
            }
        }

        return result;
    }

    vector<ParametrizedState> ParametrizedState::generate_all(int tolerance) {
        list<vector<Position>> generated,
                *newly_generated = new list<vector<Position>>;
        for (int e = 0; e <= tolerance; e++) {
            newly_generated->push_back({Position(0, e)});
        }

        while (!newly_generated->empty()) {
            generated.insert(generated.end(), newly_generated->begin(), newly_generated->end());
            auto old = newly_generated;
            newly_generated = new list<vector<Position>>;

            for (vector<Position> positions : *old) {


                list<Position> candidates = get_next_candidates(tolerance, positions);


                for (auto candidate : candidates) {
                    auto op = [&candidate](Position &p) {
                        return p.subsumes(candidate) || p.is_subsumed(candidate) || p == candidate;
                    };
                    bool is_valid = none_of(positions.begin(), positions.end(), op);

                    if (is_valid) {
                        vector<Position> new_positions(positions);
                        new_positions.push_back(candidate);
                        newly_generated->push_back(new_positions);
                    }
                }

            }

            delete (old);
        }

        delete (newly_generated);

        vector<ParametrizedState> result;
        for (vector<Position> v : generated) {
            result.push_back(ParametrizedState(v));
        }
        return result;

    }

    pair<int, ParametrizedState> ParametrizedState::parametrized_from_state(State state) {

        int parameter = state.get_minimum_boundary();

        vector<Position> result(state.size());
        auto op = [parameter](const Position &p) { return Position(p.i - parameter, p.e); };
        std::transform(state.begin(), state.end(), result.begin(), op);

        return pair<int, ParametrizedState>(parameter, ParametrizedState(result));
    };

    pair<int, ParametrizedState> ParametrizedState::transition(const BitVector &b) const {

        // Compute the transitions of all positions
        vector<State> transitions(positions.size());
        auto transitioner = [b](const Position &p) {
            return State(p.transition(b.sub(p.i)));
        };
        std::transform(positions.begin(), positions.end(), transitions.begin(), transitioner);

        State reduced = State::reduced_union(transitions);

        return parametrized_from_state(reduced);
    };
}