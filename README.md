# cub3D Project 🎮

![simplescreenrecorder-2024-06-03_15 22 59-ezgif com-video-to-gif-converter (1)](https://github.com/DjoykeAbyah/42_CUB3D/assets/115019123/c2a5fab4-f2dd-46f9-907f-1916911076af)


In collaboration with [Daoyi Liu](https://github.com/Jelligeth).

## Overview 📝
The cub3D project is a ray-casting game engine that provides a realistic 3D graphical representation of the inside of a maze from a first-person perspective. The project is developed using the MiniLibX library and is a part of the Codam curriculum. This README provides a comprehensive guide on setting up, building, and running the project.

## Table of Contents 📚
- [Mandatory Part](#mandatory-part)
  - [Program Name](#program-name)
  - [Turn In Files](#turn-in-files)
  - [Makefile](#makefile)
  - [Arguments](#arguments)
  - [External Functions](#external-functions)
  - [Libft](#libft)
  - [Description](#description)
  - [Constraints](#constraints)
  - [Controls](#controls)
  - [Map Format](#map-format)
  - [Error Handling](#error-handling)
  - [Example .cub File](#example-cub-file)
- [Bonus Part](#bonus-part)
  - [Bonus List](#bonus-list)

## Mandatory Part ⚙️

### Program Name 🖥️
`cub3D`

### Turn In Files 📁
All your files

### Makefile 🛠️
The `Makefile` must handle the following rules:
- `all`: Compile the program
- `clean`: Remove object files
- `fclean`: Remove object files and the executable
- `re`: Recompile the program
- `bonus`: Compile the bonus part (if applicable)

### Arguments 🎯
The program takes a single argument:
- A map file in the format `*.cub`

### External Functions 🔧
You are allowed to use the following external functions:
- `open`, `close`, `read`, `write`
- `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`
- All functions of the math library (`-lm`)
- All functions of the MiniLibX

### Libft 📚
The use of `libft` is authorized.

### Description 🏞️
You must create a realistic 3D graphical representation of the inside of a maze from a first-person perspective using ray-casting principles.

### Constraints 🚧
- Use the MiniLibX library.
- Ensure smooth window management (changing windows, minimizing, etc.).
- Display different wall textures based on wall orientation (North, South, East, West).
- Set distinct colors for the floor and ceiling.
- The program should respond to keyboard controls for navigation and viewing.

### Controls 🎮
- Arrow keys (left/right): Look left/right in the maze.
- W, A, S, D: Move the point of view through the maze.
- ESC: Close the window and quit the program.
- Red cross on the window frame: Close the window and quit the program.

### Map Format 🗺️
- The map must be composed of the characters `0` (empty space), `1` (wall), and `N`, `S`, `E`, `W` (player’s start position and orientation).
- The map must be enclosed by walls.
- Elements can be separated by empty lines.
- Elements can be in any order, except the map, which must be last.
- Spaces in the map are valid and must be handled.


