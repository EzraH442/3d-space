#!/bin/bash

file=./src/meson.build

echo "src_sources = [" > $file
find ./src -type f | grep -v "$file" | sed "s/.*/'&',/" >> $file
echo "]" >> $file
