#!/bin/bash
set -e

# Global variables
ROOT="$(pwd)"
SRC_DIR="${ROOT}/presets/packs"
OUTPUT_DIR="${ROOT}/presets/data"
JS="${ROOT}/js"
TEXTURE_PACK="${SRC_DIR}/textures"

cleanBuild() {
    rm -rf ${OUTPUT_DIR}
    mkdir -p ${OUTPUT_DIR}
    rm -rf ${SRC_DIR}
    rm -rf ${ROOT}/dist/*.data
}

cleanJs() {
    rm ${OUTPUT_DIR}/*.js
}

unzipPack() {
    mkdir -p ${SRC_DIR}
    unzip -q ./presets/PresetPacks.zip -d ${SRC_DIR}
}

buildDataPack() {
    cd ${OUTPUT_DIR}

    ~/install/emsdk/upstream/emscripten/tools/file_packager "presets-${PACK_NAME}.data" \
    --preload "${SRC_DIR}/${PACK_NAME}@presets" \
    --preload "${TEXTURE_PACK}@textures" \
    --js-output="${OUTPUT_DIR}/presets-${PACK_NAME}.js" \
    --lz4

    cd ${ROOT}
}

modifyJsFiles() {
    sed -i '1,9d' ${OUTPUT_DIR}/presets-${PACK_NAME}.js
    sed -i "1i Module['${PACK_NAME}'] = async function () {" ${OUTPUT_DIR}/presets-${PACK_NAME}.js
    sed -i '$d' ${OUTPUT_DIR}/presets-${PACK_NAME}.js
    sed -i -e '$a}' ${OUTPUT_DIR}/presets-${PACK_NAME}.js
}

generatePreJs() {
    rm ${JS}/pre-js.js
    cat "${JS}/presets/pre.js" >> "${JS}/pre-js.js" 
    find ${OUTPUT_DIR} -type f -name '*.js' -exec cat {} + >> "${JS}/pre-js.js"
    cat "${JS}/presets/post.js" >> "${JS}/pre-js.js" 
}

copyDataToDist(){
    mkdir -p ${ROOT}/dist
    cp ${OUTPUT_DIR}/*.data ${ROOT}/dist
}

main() {
    cleanBuild
    unzipPack

    for PACK in ${SRC_DIR}/*; do
        if [ -d "${PACK}" ]; then
            PACKNAME="$(basename ${PACK})"
            PACK_NAME="${PACKNAME,,}"

            if [ $PACK_NAME != "textures" ]; then
                echo "Pack Name: ${PACK_NAME}"
                echo
                buildDataPack
                modifyJsFiles
                
            fi
        fi
    done

    generatePreJs
    cleanJs
    copyDataToDist
}

main