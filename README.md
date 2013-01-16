Maze
====

Fun maze game written in C++ with allegro graphics. Automated level creation among other features.

All content is property of James Loewen and may only be used with express written permission.  Users may pull files for personal use at their own risk.  James Loewen is not liable for any damages or viruses that occur from the use of these files.

Details about files will be presented if requested.  Improved commenting on files upcoming

Game Objective

The main gameplay objective is to navigate through a maze and discover the different paths that create the maze while killing enemies in the process.  The player starts on a red square and navigates to find the green square tha indicates the level exit.

A player earns money for killing enemies which can be used to upgrade or buy new weapons.

Controls

Use the arrow keys to move 
WASD to shoot
Z to switch to the previous weapon
X to switch to the next weapon
C to place bombs if any are purchased
U to pause game and purchase upgrades

Features

A main menu displayed using the console with input being retrieved from the main window with the exception of selecting a game to load.  If your display flashes upon opening Maze.exe, do not worry, it is a known issue with compatibility with the implementation of the graphics library and will cause no harm to the computer or anything else.

A variety of enemies programmed to chase the user once they are within a certain range of the user.  Types of enemies include ones that fly over walls, ones that shoot bullets and ones that will simply chase the user down.

A level creator that will create a challenging but guaranteed exit maze.

Upgrades menu with a variety of upgrade options.

Mini map on right side with capability of zooming in on specific locations or where the users current location is.

Modes include:
Create a level which allows the user to create their own personal level that they then play upon completion.
Generate a level which will make the program create a level using Prim's Algorithm and then allows the user to play the generated level.
Create a Game which will generate a set of 20 levels saved in a folder with the corresponding game number as found in the code found in "Level Creator.h"
Play a Game which will prompt the user to enter a game number into the terminal and will then load the entered game for the user to play.
Survival is a mode that allows the user to play on a small boxlike map where enemies spawn at regular intervals and the user attempts to last as long as possible
Multiplayer allows multiple players to take turns at playing a series of levels until the last one has lost their life.

Install Instructions

To install this program, download all of the items in this repository to a folder on your hard drive and run Maze.exe. On screen instructions will guide you in selecting a mode to play.
