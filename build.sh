#!/bin/bash

usage() {
    echo "Usage: $0 [-d | -r]"
    echo "  -d  Build in Debug mode"
    echo "  -r  Build in Release mode"
    exit 1
}

while getopts "dr" opt; do
    case ${opt} in
    d)
        BUILD_TYPE="Debug"
        ;;
    r)
        BUILD_TYPE="Release"
        ;;
    *)
        usage
        ;;
    esac
done

if [ -z "${BUILD_TYPE}" ]; then
    usage
fi

BUILD_DIR="build/${BUILD_TYPE}"
mkdir -p "${BUILD_DIR}"

cd "${BUILD_DIR}"

echo "Configuring project for ${BUILD_TYPE} build..."
cmake -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" ../..

echo "Building project..."
cmake --build . -- VERBOSE=1

echo "Build completed successfully."
