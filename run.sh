#!/bin/bash

# Set the library path
export LD_LIBRARY_PATH=./audio_lib:$LD_LIBRARY_PATH

chmod +x cube3d_stable_build

# Run the program
./cube3d_stable_build "$@"

# Optionally, you can add command line arguments like this:
# ./cube3dwaudio "$@"