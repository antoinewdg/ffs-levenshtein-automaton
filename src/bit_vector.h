//
// Created by antoinewdg on 18/06/16.
//

#ifndef FFS_BIT_VECTOR_H
#define FFS_BIT_VECTOR_H

#include <iostream>
#include <vector>
#include <list>

using std::ostream;
using std::vector;
using std::initializer_list;
using std::list;

namespace ffs {
    struct BitVector {
        typedef vector<bool>::const_iterator const_iterator;

        vector<bool> data;

        BitVector(const vector<bool> &data) : data(data) { }

        BitVector(const initializer_list<bool> &data) : data(data) { }

        BitVector sub(int start, int end) const {
            vector<bool> new_data((unsigned long) (end - start));
            std::copy(data.begin() + start, data.begin() + end, new_data.begin());
            return BitVector(new_data);
        }

        BitVector sub(int start) const {
            return sub(start, size());
        }

        static vector<BitVector> generate_all(int max_size);

        void operator<<(bool back) {
            data.push_back(back);
        }

        const_iterator begin() const {
            return data.begin();
        }

        const_iterator end() const {
            return data.end();
        }

        unsigned long size() const {
            return data.size();
        }
    };

    inline ostream &operator<<(ostream &os, const BitVector &b) {
        for (bool bit: b.data) {
            os << bit;
        }
        return os;
    }

    inline bool operator!=(const BitVector &a, const BitVector &b) {
        return a.data != b.data;
    }

    inline bool operator==(const BitVector &a, const BitVector &b) {
        return !(a != b);
    }
}

namespace std {
    template<>
    struct hash<ffs::BitVector> {
        size_t operator()(const ffs::BitVector &b) const {
            size_t seed = b.data.size();
            for (bool i : b) {
                seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

//
//}

#endif //FFS_BIT_VECTOR_H
