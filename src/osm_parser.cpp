#include <iostream>
#include <osmium/osm/way.hpp>
#include <osmium/handler.hpp>
#include <osmium/io/any_input.hpp>
#include <osmium/visitor.hpp>
#include <osmium/index/map/sparse_mmap_array.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>

#include "osm_parser.h"

using namespace std;

namespace my {

bool _is_way_interesting(const osmium::Way& way) {
    // as a rule of thumb, if a way has the 'highway' tag, it can be used for routing :
    // FIXME : we would probably like to filter out non-pedestrian ways.
    if (way.tags()["highway"] == nullptr)
        return false;

    // some ways aren't a road, but delimits an area. We aren't interesting in them :
    if (way.tags()["area"] != nullptr && strcmp(way.tags()["area"], "yes") == 0)
        return false;

    // way is too short :
    if (way.nodes().size() < 2)
        return false;

    return true;
}

// simple libosmium Handler that get extremities of ways, and associates them to the parent way id :
struct ExtremitiesHandler : public osmium::handler::Handler {
    unordered_set<Extremity, ExtremityHasher> extremities;
    void way(const osmium::Way& way) noexcept {
        // useful docs :
        //      https://docs.osmcode.org/libosmium/latest/classosmium_1_1Way.html
        //      https://docs.osmcode.org/libosmium/latest/classosmium_1_1WayNodeList.html
        //      https://docs.osmcode.org/libosmium/latest/classosmium_1_1NodeRef.html
        //      https://docs.osmcode.org/libosmium/latest/classosmium_1_1Location.html
        if (!_is_way_interesting(way))
            return;
        auto& front_node = way.nodes().front();
        auto& back_node = way.nodes().back();
        extremities.insert({way.id(), front_node.lon(), front_node.lat()});
        extremities.insert({way.id(), back_node.lon(), back_node.lat()});
    }
};

unordered_set<Extremity, ExtremityHasher> osm_to_extremities(string osmfile) {
    // osmium warmup :
    auto interesting_types = osmium::osm_entity_bits::node | osmium::osm_entity_bits::way;
    using Index = osmium::index::map::SparseMmapArray<osmium::unsigned_object_id_type, osmium::Location>;
    Index index;
    osmium::handler::NodeLocationsForWays<Index> location_handler{index};

    osmium::io::Reader reader{osmfile, interesting_types};

    // parse osmfile + fill-in data structures :
    ExtremitiesHandler handler;
    osmium::apply(reader, location_handler, handler);
    reader.close();

    return handler.extremities;
}

}  // namespace my
