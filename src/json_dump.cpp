#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/ostreamwrapper.h>

#include "json_dump.h"

using namespace std;

namespace my {

void dump_extremities(ostream& out, unordered_set<Extremity, ExtremityHasher> const& extremities) {
    rapidjson::Document doc(rapidjson::kObjectType);
    rapidjson::Document::AllocatorType& a = doc.GetAllocator();

    rapidjson::Value extremities_json(rapidjson::kArrayType);

    for (auto& extremity : extremities) {
        rapidjson::Document extremity_json(rapidjson::kObjectType);
        extremity_json.AddMember("id", extremity.osmid, a);
        extremity_json.AddMember("longitude", extremity.lon, a);
        extremity_json.AddMember("latitude", extremity.lat, a);
        extremities_json.PushBack(extremity_json, a);
    }

    doc.AddMember("extremities", extremities_json, a);

    // dumping :
    rapidjson::OStreamWrapper out_wrapper(out);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(out_wrapper);
    doc.Accept(writer);
}

}  // namespace my
