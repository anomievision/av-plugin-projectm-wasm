#!/bin/bash
set -e

# Global variables
ROOT=$(pwd)
SRC="${ROOT}/src"
BUILD="${ROOT}/build"
DIST="${ROOT}/dist"
EMSDK_TOOLCHAIN_FILE="$HOME/.install/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"
CMAKE_INSTALL_PREFIX=$LIBPROJECTM_INSTALL_PREFIX;$POCO_INSTALL_PREFIX


LIBPROJECTM_DIR="$HOME/.install/projectm/lib/cmake/libprojectM"
LIBPROJECTM_INSTALL_PREFIX="$HOME/.install/projectm"

# Clean generated project files
cleanProject() {
    rm -rf ${DIST}/avPluginProjectMWASM.*
    rm -rf ${BUILD}
}

# Build
buildProject() {
    emcmake cmake \
    -DCMAKE_BUILD_TYPE=RELEASE \
    -G "Unix Makefiles" \
    -DCMAKE_TOOLCHAIN_FILE=${EMSDK_TOOLCHAIN_FILE} \
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} \
    -DlibprojectM_DIR=${LIBPROJECTM_DIR} \
    -B ${BUILD} \
    -S .

    cd $BUILD
    emmake make

    cd $ROOT
    mkdir -p ${DIST}
    cp ${BUILD}/avPluginProjectMWASM.* ${DIST}

    rm -rf ${BUILD}
}

cleanProject
buildProject
