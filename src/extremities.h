#pragma once

#include <cstdint>
#include <functional>

namespace my {

struct Extremity {
    inline Extremity(int64_t osmid_, double lon_, double lat_) : osmid{osmid_}, lon{lon_}, lat{lat_} {}

    inline bool operator==(Extremity const& other) const {
        return this->osmid == other.osmid && this->lon == other.lon && this->lat == other.lat;
    }

    int64_t osmid;
    double lon;
    double lat;
};

struct ExtremityHasher {
    std::size_t operator()(Extremity const& e) const {
        return std::hash<int64_t>{}(e.osmid) + std::hash<double>{}(e.lon) + std::hash<double>{}(e.lat);
    }
};

}  // namespace my
