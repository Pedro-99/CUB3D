#!/bin/bash
sudo apt-get update
sudo apt-get install -y gcc cmake libglfw3 libglfw3-dev libx11-dev libxext-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
git clone git@github.com:Pedro-99/CUB3D.git cub3d_project
cd cub3d_project
# Uncomment next line if MLX42 isn’t in repo
# git clone https://github.com/codam-coding-college/MLX42.git MLX42
make
echo "Setup complete! Run './cub3d path/to/map.cub' to start."
