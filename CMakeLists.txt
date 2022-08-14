cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project(avPluginProjectMWASM
        VERSION 1.0.0)

find_package(libprojectM REQUIRED CONFIG)

# Setting the suffix to .html also creates an HTML file in addition to the .js and .wasm outputs.
set(CMAKE_EXECUTABLE_SUFFIX ".js")

add_executable(avPluginProjectMWASM
        src/Main.cpp
        src/FPSLimiter.cpp
        src/FPSLimiter.h
        src/Settings.cpp
        src/Settings.h         
        )
            
target_include_directories(avPluginProjectMWASM
        PUBLIC
        include
        )

target_link_libraries(avPluginProjectMWASM
        PRIVATE
        libprojectM::static
        )

target_compile_options(avPluginProjectMWASM
        PRIVATE
        "SHELL:-s USE_SDL=2"
        )


target_link_options(avPluginProjectMWASM
        PRIVATE
        "SHELL:--bind"
        "SHELL:-s USE_SDL=2"
        "SHELL:-s MIN_WEBGL_VERSION=2"
        "SHELL:-s MAX_WEBGL_VERSION=2"
        "SHELL:-s FULL_ES2=1"
        "SHELL:-s ALLOW_MEMORY_GROWTH=1"
        "SHELL:-s MODULARIZE=1"
        "SHELL:-s EXPORT_NAME=avPluginProjectMWASM"
        "SHELL:-s EXPORT_ES6=1"
        "SHELL:-s EXIT_RUNTIME=1"
        "SHELL:-s FORCE_FILESYSTEM"
        "SHELL:-s NO_DISABLE_EXCEPTION_CATCHING"
        "SHELL:-s EXPORTED_RUNTIME_METHODS=['UTF8ToString','lengthBytesUTF8','stringToUTF8','FS']"
        "SHELL:--shell-file ${CMAKE_SOURCE_DIR}/templates/shell_minimal.html"
        "SHELL:--pre-js ${CMAKE_SOURCE_DIR}/js/pre-js.js"
        # "SHELL:-s INCOMING_MODULE_JS_API=[]"
        # "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/presets@/presets"
        )

message(STATUS "")
message(STATUS "-----------------------------------------------")
message(STATUS "  AnomieVision | Plugin | ProjectM | Library")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "-----------------------------------------------")
message(STATUS "")
message(STATUS "  CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "")
message(STATUS "-----------------------------------------------")
message(STATUS "")
