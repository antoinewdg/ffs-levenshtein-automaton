#include "position.h"

namespace ffs {

    vector<Position> Position::transition(const BitVector &b) const {
        auto it = b.begin();

        if (it == b.end()) {
            return {Position(i, e + 1)};
        }

        if (it != b.end() && *it == 1) {
            return {Position(i + 1, e)};
        }

        vector<Position> result = {Position(i, e + 1), Position(i + 1, e + 1)};

        for (; it != b.end(); it++) {
            if (*it == 1) {
                int d = int(std::distance(b.begin(), it));
                result.push_back(Position(i + d + 1, e + d));
                break;
            }
        }

        return result;
    }


    ostream &operator<<(ostream &out, const Position &p) {
        out << 'i';
        if (p.i > 0) {
            out << '+' << p.i;
        } else if (p.i < 0) {
            out << p.i;
        }
        out << '#' << p.e;
        return out;
    }
}