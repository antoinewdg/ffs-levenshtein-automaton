//
// Created by antoinewdg on 16/07/16.
//

#ifndef FFS_STATE_H
#define FFS_STATE_H

#include <algorithm>
#include <vector>

#include "position.h"


namespace ffs {
    using std::vector;

    class State {

    public:

        typedef vector<Position>::iterator iterator;
        typedef vector<Position>::const_iterator const_iterator;

        State() {}

        template<class Iterator>
        State(Iterator begin, Iterator end) {
            m_positions = vector<Position>(begin, end);
            std::sort(m_positions.begin(), m_positions.end());
            auto comparator = [](const Position &p, const Position &q) { return p.i < q.i; };
            if (m_positions.empty()) {
                m_minimum_boundary = 0;
            } else {
                auto it = std::min_element(m_positions.begin(), m_positions.end(), comparator);
                m_minimum_boundary = it->i;
            }
        }

        State(const initializer_list<Position> &positions) : State(positions.begin(), positions.end()) {}

        State(const vector<Position> &positions) : State(positions.begin(), positions.end()) {}

        static State reduced_union(const vector<State> &states);

        int get_minimum_boundary() const { return m_minimum_boundary; }

        const_iterator begin() const { return m_positions.begin(); }

        const_iterator end() const { return m_positions.end(); };

        unsigned long size() const { return m_positions.size(); };

        bool operator==(const State &s) const {
            return m_positions == s.m_positions;
        }

        bool operator!=(const State &s) const {
            return !(*this == s);
        }

    private:
        int m_minimum_boundary;
        vector<Position> m_positions;
    };

}

#endif //FFS_STATE_H
