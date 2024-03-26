# **Cub3D**
<img alt="Cub3D" src="https://img.shields.io/static/v1?label=Cub3D&message=120+/+125&color=gree&style=plastic"/>


# Project
Cub3D is one of the three project in the 42 program fifth circle. This is a group project of the 42 common core program. In this project the students need to create a raycaster to display custom maps.

# Involved Language(s)
* <img alt="C_Logo" src="https://upload.wikimedia.org/wikipedia/commons/thumb/archive/3/35/20220802133510%21The_C_Programming_Language_logo.svg/120px-The_C_Programming_Language_logo.svg.png" style="height : 50px;"/>

# Constraints
According to the subject there only three constraint for this project:
* The whole files of the projects need to follow 42 norm ([Link](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf))
* The project must be realized using the minilibx ([Link](https://github.com/codam-coding-college/MLX42))

# External Functions Allowed

This project don't allow any external library.
* open
* close
* read
* write
* printf
* malloc
* free
* perror
* strerror
* exit
* All functions of the math library (*-lm man man 3 math*)

# Project breakdown
For this project we didn't splited the workload in distinct parts, both of us worked on everything.
* Co-Worker : [ParesseuxRose](https://github.com/ParesseuxRose)

# Group choices

We've taken a small liberty with the subject:
* We have chosen to have "square" by "square" movement in our labyrinth, inspired by the *[Legend of Grimrock](https://store.steampowered.com/app/207170/Legend_of_Grimrock/)* movement system rather than a more classic movement system.

# Mandatory Features
Following a non-exhaustive list of the commands and features requested by the subject:

|  Name   |                                                  Descripion                                                  |       Status       |
|:-------:|:------------------------------------------------------------------------------------------------------------:|:------------------:|
| **Windows**  |The management of the window must remain smooth: changing to another window, minimizing, etc.| :white_check_mark: |
| **Textures** |Display different wall textures (the choice is yours) that vary depending on which side the wall is facing (North, South, East, West).| :white_check_mark: |
|  **Colors**   |The program must be able to set the floor and ceiling colors to two different ones.| :white_check_mark: |
||**Controls**|
| **Rotation** |The left and right arrow keys of the keyboard must allow the player to look left and right in the maze.| :white_check_mark: |
| **Movement** |The **W**, **A**, **S**, and **D** keys must allow the player to move the point of view through the maze.| :white_check_mark: |
| **Close** |  The **ESC** key and the cross on the window's frame must close the window and quit the program cleanly.| :white_check_mark:|
||**Parsing**|
| **Characters** |The map must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and N,S,E or W for the player’s start position and spawning orientation.| :white_check_mark: |
| **Border** |The map must be closed/surrounded by walls, if not the program must return an error.| :white_check_mark: |
| **Order** |Except for the map content which always has to be the last, each type of element can be set in any order in the file.| :white_check_mark: |


# Exemple Map file

```bash
NO ./path_to_the_north_texture.png
SO ./path_to_the_south_texture.png
WE ./path_to_the_west_texture.png
EA ./path_to_the_east_texture.png


F 220,100,0 # Floor color in rgb format
C 225,30,0 # Ceiling color in rgb format

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
# Bonus Features

Following a list of the bonus features requested by the subject:

|  Name   |                                                  Descripion                                                  |       status       |
|:-------:|:------------------------------------------------------------------------------------------------------------:|:------------------:|
| **Wall collisions**  |Not specified in the mandatory part, the player need to collide with the walls. | :white_check_mark: |
| **Minimap**  |A minimap of the maze must be visible on the player screen.| :white_check_mark: |
| **Doors**  | A System of door must be implemented (opening and closing) | :white_check_mark: |
| **Animation**  | An animation must be visible somewhere.| :white_check_mark: |
| **Alternative rotation** | Rotate the point of view with the mouse. | :x: |


# Input
The project executable have 2 required input:
1. **Map**: The .ber map file path

# Usage

``make`` to compile.

``clean`` to clean all compiled file without the library file.

``fclean`` to clean all compiled file with the library file.

``re`` to fclean then make.

# Controls

``W A S D`` for moving character the player.

``Right Arrow Left Arrow`` for rotation the player.

``Space`` For opening and closing doors.

# Warning 
Be sure to keep at last one 0.png in the ./Assets/Textures/Animation/ folder.
Animation loop can be changed by adding more png in the folder named with the previous number + 1. (0.png 1.png 2.png) 

# Screenshots

<img width="720" alt="Screenshot" src="https://github.com/m-juin/Cub3D/blob/master/Assets/Screens/Cub3D001.png">
<img width="720" alt="Screenshot" src="https://github.com/m-juin/Cub3D/blob/master/Assets/Screens/Cub3D002.png">
<img width="720" alt="Screenshot" src="https://github.com/m-juin/Cub3D/blob/master/Assets/Screens/Cub3D003.png">

BrickWall.png Designed by Dotstudio / Freepik
