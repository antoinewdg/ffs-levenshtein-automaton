#include "position.h"

namespace ffs {

    vector<Position> Position::transition(const BitVector &b, int tolerance) const {
        auto it = b.begin();
        auto filter_tolerated = [tolerance](const vector<Position> &v) {
            vector<Position> result(v.size());
            auto nend = std::copy_if(v.begin(), v.end(), result.begin(), [tolerance](const Position &p) {
                return p.e <= tolerance;
            });
            result.resize(size_t(std::distance(result.begin(), nend)));
            return result;
        };

        if (it == b.end()) {
            return filter_tolerated({Position(i, e + 1)});
        }

        if (*it == 1) {
            return filter_tolerated({Position(i + 1, e)});
        }

        vector<Position> result = {Position(i, e + 1), Position(i + 1, e + 1)};

        for (; it != b.end(); it++) {
            if (*it == 1) {
                int d = int(std::distance(b.begin(), it));
                result.push_back(Position(i + d + 1, e + d));
                break;
            }
        }

        return filter_tolerated(result);
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