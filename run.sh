#!/bin/bash

export LD_LIBRARY_PATH=./audio_lib:$LD_LIBRARY_PATH

chmod +x cube3D_stablebuild

./cube3D_stablebuild "$@"
