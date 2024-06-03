# cub3D Project 🎮

![simplescreenrecorder-2024-06-03_15 22 59-ezgif com-video-to-gif-converter (1)](https://github.com/DjoykeAbyah/42_CUB3D/assets/115019123/c2a5fab4-f2dd-46f9-907f-1916911076af)


In collaboration with [Daoyi Liu](https://github.com/Jelligeth).

## Overview 📝

Welcome to the cub3D project! This project is a part of the 42 curriculum and involves creating a realistic 3D graphical representation of a maze from a first-person perspective using ray-casting principles. This README will guide you through the setup, building, and execution of the project, providing all the necessary details to help you navigate and succeed in this journey.

## Table of Contents

- [Introduction](#introduction)
- [Getting Started](#getting-started)
  - [Clone](#clone)
  - [Compile and Run](#compile-and-run)
- [Arguments](#arguments)
- [Controls](#controls)
- [Map Format](#map-format)
- [Example .cub File](#example-cub-file)
- [Bonus List](#bonus-list)

## Introduction

Imagine yourself as a developer in the 90s, tasked with creating a 3D game engine from scratch. Your goal is to build a program that generates a realistic 3D maze, navigable from a first-person perspective. You will use the ray-casting technique, the same technology that powered early 3D games like Wolfenstein 3D. Welcome to cub3D, where you bring these classic concepts to life using modern tools provided by the MiniLibX library.

## Getting Started

### Clone

Clone the repository including the MiniLibX submodule:

```bash
git clone --recursive https://github.com/mcombeau/cub3D.git

Or:

```bash
git clone <https://github.com/mcombeau/cub3D.git>
git submodule update --init --recursive

```


### Compile and Run

There are two versions of the program, the mandatory part and the bonus part. The bonus part adds wall collision, a minimap, and the ability to rotate the view by moving the mouse.

To compile the mandatory part, cd into the cloned directory and:

```bash
make

```

To compile the bonus part, cd into the cloned directory and:

```bash
make bonus

```

> Note: you may need to make fclean to switch between the mandatory and bonus compilations (working on a fix for this!).
> 

To run the program:

```bash
./cub3d <path/to/map.cub>

```

The program takes a map file as an argument. Maps are available in the `maps` directory. There are good maps which the program should run smoothly with, and bad maps which the program should reject. For example:

```bash
./cub3d maps/good/library.cub

```

should run.

```bash
./cub3d maps/bad/filetype_wrong.buc

```

should print an error and abort.

### Arguments

The program accepts one argument:

- A map file with the `.cub` extension, which describes the layout of the maze.

## Controls

The following controls should be implemented for navigating the maze:

- **W**: Move forward
- **S**: Move backward
- **A**: Move left
- **D**: Move right
- **Left Arrow**: Rotate left
- **Right Arrow**: Rotate right
- **ESC**: Close the window and quit the program
- **Red Cross on Window Frame**: Close the window and quit the program
- **Mouse**: Rotate by moving the mouse (bonus only)

## Map Format

The map file describes the layout of the maze and should contain:

- `0`: Empty space
- `1`: Wall
- `N`, `S`, `E`, `W`: Player’s start position and initial orientation

## Example .cub File 📝

Here’s an example of what a `.cub` file might look like:

```bash
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111

```

## Bonus List ✨

- Wall collisions 🧱: Prevent the player from walking through walls.
- A minimap system 🗺️: Display a minimap of the maze..
- Rotate the point of view with the mouse 🖱️: Allow mouse control for viewing direction.
