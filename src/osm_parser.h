#pragma once

#include <unordered_set>

#include "extremities.h"

namespace my {

std::unordered_set<Extremity, ExtremityHasher> osm_to_extremities(std::string osmfile);

}  // namespace my
