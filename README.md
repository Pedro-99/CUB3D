# CUB3D
This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.


1. Clone the Project
Instruction: Clone your project repository to their machine.
``
git clone git@github.com:Pedro-99/CUB3D.git cub3d_project
cd cub3d_project
``
2. Install System Dependencies
MLX42 requires a C compiler, CMake (for building MLX42), GLFW (a dependency for window management), and other libraries. Run:
``
sudo apt-get update
sudo apt-get install gcc cmake libglfw3 libglfw3-dev libx11-dev libxext-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
``
Explanation:
gcc: Compiler for building the project.
cmake: Builds MLX42 from source.
libglfw3 and libglfw3-dev: GLFW library for window and input handling (replaces some X11 functionality in MLX42).
X11-related libraries (libx11-dev, etc.): Needed for Linux compatibility.
Verify GLFW Installation:
``
pkg-config --modversion glfw3
``
Should return a version (e.g., 3.3). If not, the installation failed.
3. Verify Project Structure
Ensure the cloned project has this structure:

cub3d_project/
├── Makefile          (your provided Makefile)
├── MLX42/           (MLX42 source folder)
├── src/             (main.c, raycasting.c, etc.)
│   ├── libft/       (libft source files)
│   └── get-next-line/ (GNL source files)
├── includes/        (cub3d.h)
└── obj/             (created during build)
Note: If MLX42/ isn’t in the repo, they’ll need to download it (see step 4). Confirm with you whether it’s included!
4. Download MLX42 (If Not Included)
If MLX42/ isn’t part of your repository:

Instruction: Download MLX42 from its official GitHub and place it in the project root.
``
git clone https://github.com/codam-coding-college/MLX42.git MLX42
Note: Your Makefile expects MLX42/ as MLX_DIR, so the folder name must match.
``
5. Build MLX42
Your Makefile includes a rule to build MLX42:
``
$(MLX_LIB):
	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4
``
Instruction: Run make to build MLX42 and the project.
``
make
``
What Happens:
``
cd MLX42 && cmake -B build: Configures MLX42, creating a build/ folder inside MLX42/.
cmake --build build -j4: Compiles libmlx42.a using 4 parallel jobs (adjust -j4 based on CPU cores).
``
Output: MLX42/build/libmlx42.a (referenced as $(MLX_LIB)).
Troubleshooting:
If it fails, check for missing GLFW (sudo apt-get install libglfw3-dev) or CMake (sudo apt-get install cmake).
Ensure they’re in the project root when running make.
6. Build the Project
The all target in your Makefile builds everything:
makefile
``
all: $(NAME)
$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
``
Instruction: If make hasn’t been run yet, run it:
``
make
``
What Happens:
Compiles source files from src/, src/libft/, and src/get-next-line/ into obj/.
Links objects with libmlx42.a and libraries (-ldl -lglfw -pthread -lm).
Creates the cub3d executable.
Verify: Check for ./cub3d in the root.
