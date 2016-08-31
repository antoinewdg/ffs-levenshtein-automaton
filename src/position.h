//
// Created by antoinewdg on 18/06/16.
//

#ifndef FFS_POSITION_H
#define FFS_POSITION_H

#include <cmath>
#include <iostream>
#include <vector>
#include <limits>
#include <list>
#include <algorithm>

#include "bit_vector.h"


namespace ffs {

    using std::ostream;
    using std::vector;
    using std::list;
    using std::abs;
    using std::numeric_limits;
    using std::cout;
    using std::endl;

    struct Position {
        int i, e;

        Position() {}

        Position(int i, int e) : i(i), e(e) {}

        vector<Position> transition(const BitVector &b, int tolerance) const;

        bool is_subsumed(const Position &p) const {
            return p.subsumes(*this);
        }

        bool subsumes(const Position &p) const {
            return e <= p.e && abs(i - p.i) <= p.e - e;
        }

        static Position max_value() {
            return Position(numeric_limits<int>::max(), numeric_limits<int>::max());
        }

    };

    ostream &operator<<(ostream &out, const Position &p);


    inline bool operator!=(const Position &p, const Position &q) {
        return p.i != q.i || p.e != q.e;
    }

    inline bool operator==(const Position &p, const Position &q) {
        return !(p != q);
    }


    inline bool operator<(const Position &p, const Position &q) {
        return p.e < q.e || (p.e == q.e && p.i < q.i);
    }


}


#endif //FFS_POSITION_H
