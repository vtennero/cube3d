# cube3d

## Run
to run (including on 42 computers):
bash run.sh maps/[mapname].cub

helldivers3D exe is required as well as audio_lib directory. See Build Commands below.

## Build Commands

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


