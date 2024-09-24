#!/bin/bash

export LD_LIBRARY_PATH=./audio_lib:$LD_LIBRARY_PATH

chmod +x helldivers3D

./helldivers3D "$@"
