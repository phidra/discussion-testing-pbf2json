#!/bin/bash

set -o errexit
set -o nounset
set -o pipefail

root_dir="$(realpath "$(dirname "$0")" )"

# === Preparing build
BUILD_DIR="${root_dir}/_build"
CMAKE_ROOT_DIR="${root_dir}/src"
echo "BUILD_DIR=$BUILD_DIR"
echo "CMAKE_ROOT_DIR=$CMAKE_ROOT_DIR"

echo "To build from scratch :  rm -rf '$BUILD_DIR'"
# rm -rf "$BUILD_DIR"


# === Building :
mkdir -p "$BUILD_DIR"
conan install --install-folder="$BUILD_DIR" "$CMAKE_ROOT_DIR"
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo  -B"$BUILD_DIR" -H"$CMAKE_ROOT_DIR"
make -j -C "$BUILD_DIR"
