//
// Created by antoinewdg on 16/07/16.
//

#ifndef FFS_STATE_H
#define FFS_STATE_H

#include <algorithm>
#include <vector>

#include "position.h"

using std::vector;

namespace ffs {
    class State {

    public:

        typedef vector<Position>::iterator iterator;
        typedef vector<Position>::const_iterator const_iterator;

        State() { }

        template<class Iterator>
        State(Iterator begin, Iterator end) {
            _positions = vector<Position>(begin, end);
            std::sort(_positions.begin(), _positions.end());
            auto comparator = [](const Position &p, const Position &q) { return p.i < q.i; };
            auto it = std::min_element(_positions.begin(), _positions.end(), comparator);
            _minimum_boundary = it->i;
        }

        State(const initializer_list<Position> &positions) : State(positions.begin(), positions.end()) { }

        State(const vector<Position> &positions) : State(positions.begin(), positions.end()) { }

        static State reduced_union(const vector<State> &states);

        int get_minimum_boundary() const { return _minimum_boundary; }

        const_iterator begin() const { return _positions.begin(); }

        const_iterator end() const { return _positions.end(); };

        unsigned long size() const { return _positions.size(); };

    private:
        int _minimum_boundary;
        vector<Position> _positions;
    };

    inline bool operator==(const State &s, const State &t) {
        return std::equal(s.begin(), s.end(), t.begin());
    }

    inline bool operator!=(const State &s, const State &t) {
        return !(s == t);
    }

}

#endif //FFS_STATE_H
