#include "Board.h"

struct Magic {
    BitBoard mask;
    std::uint64_t magic;
    std::uint8_t index_bits;
};
