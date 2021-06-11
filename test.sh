#!/bin/bash

set -o errexit
set -o nounset
set -o pipefail

root_dir="$(realpath "$(dirname "$0")" )"

set -o xtrace
"${root_dir}/_build/bin/converter" "${root_dir}/data/data.osm.pbf"
