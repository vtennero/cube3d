# cube3d

## Demo

[Full Gameplay Demo](https://youtu.be/kX3IMoM1J2w)

## Run
to run (including on 42 computers):
bash run.sh maps/[mapname].cub

helldivers3D exe is required as well as audio_lib directory. See Build Commands below.

if the mouse is too sensitive (for example if you run it on WSL): try these parameters in cube3d.h
```
# define MOUSE_ROT_SPEED 0.0005
# define MOUSE_PITCH_SPEED 0.0001
```

## Build Commands

### Prerequisites
clone https://github.com/42Paris/minilibx-linux inside the repo and rename it to 'mlx'

### make
Compiles the core 42 cub3D project, meeting all mandatory requirements.

### make bonus
Builds the full game without audio functionality. This version is compatible with 42 school computers and includes all bonus features except audio.

### make helldivers3d
Compiles the complete game with full audio support. This version requires additional libraries:
- [xyz]

## Features

### 3D Raycasting Engine
- Wall Rendering
- Randomized Floor Texture Rendering
- Sky dynamic rendering
- 2D Objects: Animated Enemies, Collectibles, Mission Objects, Explosions, Fire
- Player Movement & Collision
- Mouse Pitch
- Screen shake

### Gameplay
- Scripts/Game Events: Death, Burning, Respawn, Health, Shooting, Objectives, Localized Player Airstrikes
- Enemies with pathfinding and randomized location respawn
- Mission Logic: Collect the Sample, Call Extraction, Survive, Extract


