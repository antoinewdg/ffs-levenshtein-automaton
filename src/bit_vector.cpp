#include "bit_vector.h"

namespace ffs {
    vector<BitVector> BitVector::generate_all(int max_size) {
        vector<BitVector> result;
        list<BitVector> *newly_generated = new list<BitVector>({{}});

        for(int size = 0; size <= max_size ; size++){
            result.insert(result.end(), newly_generated->begin(), newly_generated->end());
            auto old = newly_generated;
            newly_generated = new list<BitVector>;

            for (const BitVector &a: *old) {
                BitVector b(a);
                b << 0;
                newly_generated->push_back(b);
                b = BitVector(a);
                b << 1;
                newly_generated->push_back(b);
            }

            delete (old);
        }

        delete (newly_generated);
        return result;
    }
}