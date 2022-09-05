#pragma once

#include "../../../set.hpp"
#include "../../../vector.hpp"
#include <set>
#include <vector>

#include "prelude.hpp"

// I assume here that each node of set<int> will be < 128 bytes which I think is fair
// enough for:
// - int (4 bytes)
// - 3 ptrs (24 bytes)
// - int(enum) or bool for the color (4 or 1)
// - +some alignment
// --------------------------
// ~32 bytes
#define MAXSIZE ((std::size_t)MAXRAM / 128)
