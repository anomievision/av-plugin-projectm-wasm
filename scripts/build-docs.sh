#!/bin/bash

# Install Doxygen
# sudo apt install doxygen

# Install Moxygen (convert .xml to .md)
# npm install -g moxygen

rm -rf doxygen
rm -rf docs

mkdir docs

doxygen doxygen.conf

moxygen --anchors --output=docs/index.md ./doxygen/xml

rm -rf doxygen