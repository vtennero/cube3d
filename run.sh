#!/bin/bash

# Set the library path
export LD_LIBRARY_PATH=./audio_lib:$LD_LIBRARY_PATH

# Run the program
./cube3dwaudio2

# Optionally, you can add command line arguments like this:
# ./cube3dwaudio "$@"