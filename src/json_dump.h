#pragma once

#include <unordered_set>
#include <ostream>

#include "extremities.h"

namespace my {

void dump_extremities(std::ostream& out, std::unordered_set<Extremity, ExtremityHasher> const& extremities);

}  // namespace my
