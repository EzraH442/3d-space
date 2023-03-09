#!/bin/bash

find ./src -type f > ./_1.txt
sed "s/.*/'&',/" ./_1.txt > ./_2.txt
sed '$ d' ./_2.txt > ./_3.txt