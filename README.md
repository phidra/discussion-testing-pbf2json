# discussion-testing-pbf2json

The only purpose of this repo is to support discussions about how to test a conversion program.

# How to get data

The required format is [osm.pbf](https://wiki.openstreetmap.org/wiki/PBF_Format).

You can download it directly as `.osm.pbf`, for instance from geofabrifk ([example](https://download.geofabrik.de/europe/france.html)).

Alternatively, you can download it as [osm XML](https://wiki.openstreetmap.org/wiki/OSM_XML), then convert it to `.osm.pbf`, for instance using [osmium-tool](https://osmcode.org/osmium-tool/) :

```
wget -O data.osm "https://api.openstreetmap.org/api/0.6/map?bbox=2.19165,48.59169,2.19259,48.59210"
osmium cat data.osm -o data.osm.pbf
```

A very small sample data file is included in the repo in the `data` folder.

# How to build / run

The repo uses conan to get rapidjson dependency, and assumes libosmium to be installed system-wide.

```
./build.sh
./test.sh  # will run on the data included in the repo
```
