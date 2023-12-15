#!/bin/bash

FILE=./sfml_chess

rm -rf build
mkdir build && cd build
cmake .. && make
if test -f "$FILE"; then
   echo "The SFML Chess project built successfully."
   echo -e "\n"
   $FILE
   echo -e "\n"
fi
cd ..