#!/bin/bash

export LD_LIBRARY_PATH=./audio_lib:$LD_LIBRARY_PATH

chmod +x helldivers3D

# Run the program with Valgrind for memory leak checking
# valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./helldivers3D "$@"
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=definite,indirect,possible --errors-for-leak-kinds=definite,indirect,possible ./helldivers3D "$@"
