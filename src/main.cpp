#include <iostream>
#include <fstream>
#include <string>

#include "osm_parser.h"
#include "json_dump.h"

int main(int argc, char** argv) {
    const std::string output_file = "output.json";
    if (argc < 2) {
        std::cout << "Converts the extremities of the ways from an input PBF file to a json file : '" << output_file
                  << "'" << std::endl;
        std::cout << "Usage:  " << argv[0] << "   <osm-file>" << std::endl;
        std::exit(0);
    }

    const std::string osm_file = argv[1];

    std::cout << "INPUT OSMFILE      = " << osm_file << std::endl;
    std::cout << std::endl;

    auto extremities = my::osm_to_extremities(osm_file);

    std::ofstream out(output_file);
    my::dump_extremities(out, extremities);

    std::cout << "Dumped " << extremities.size() << " extremities in : " << output_file << std::endl;

    return 0;
}
