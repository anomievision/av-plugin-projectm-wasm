#!/bin/bash
set -e

# Global variables
ROOT=$(pwd)
SRC="${ROOT}/src"
BUILD="${ROOT}/build"
BUILD_TYPE="DEBUG"
EMSDK_TOOLCHAIN_FILE="$HOME/.install/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"
CMAKE_INSTALL_PREFIX=$LIBPROJECTM_INSTALL_PREFIX;$POCO_INSTALL_PREFIX


LIBPROJECTM_DIR="$HOME/.install/projectm/lib/cmake/libprojectM"
LIBPROJECTM_INSTALL_PREFIX="$HOME/.install/projectm"

# Clean generated project files
cleanProject() {
    rm -rf ${BUILD}
}

# Build
buildProject() {
    emcmake cmake \
    -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
    -G "Unix Makefiles" \
    -DCMAKE_TOOLCHAIN_FILE=${EMSDK_TOOLCHAIN_FILE} \
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} \
    -DlibprojectM_DIR=${LIBPROJECTM_DIR} \
    -B ${BUILD} \
    -S .

    cd $BUILD
    emmake make
}

cleanProject
buildProject