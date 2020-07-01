# CPPND: Capstone Snake Game 

_Please check the last section of this README for commentary on the changes made to the starter repository and the points of the rubric addressed._

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Make a build directory in the top level directory: `mkdir build && cd build`
2. Compile: `cmake .. && make`
3. Run it: `./SnakeGame`.

## Additional Functionality

My Modifications in short is divided into three parts :

The first part consists of storing the player score and player name in a .txt file. Which is updated every time a new player play the game, and in the instance where a player with the same name as an existing player name is added, the new player score replaces the old one, and when the second game mode is chosen the player name is saved as CPU.

The Second Part is the addition of a couple of powerups for the snake to help ease the game and that consists of three types 1.PowerSpeed(purple block), 2.PowerSlow(green block), 3.ExtraLife(black block), i think number one is more of a powerdown as it increases the speed of the snake and makes the game harder. number two decreases the speed of the snake to make it easier to control the snake and the final one adds the concept of lives to the game where the snake has a number of lives that decreases by one each time the snake's head touches it's body and when the snake does so with the condition of the lives equals the player loses.

The Third part is where i added an automated game mode that plays the game on its own with the goal of collecting the food out there while also having a maximum of 20 lives, which means you will find the snake going for the yellow and black blocks whenever it has the chance, and it will stop looking for black blocks when the lives counter is 20 and it does all this while maintaning a speed of 0.41 which means that whenever the speed exceeds this number the snake stops looking for all the blocks except the green one to decrease its speed and when it does so it gets back to looking for either yellow and black blocks.

1. `main.cpp` now gives the user the choice of three game modes and the instance of the first game mode is chosen, the player inputs the player name.
2. The `Player` is initialized on the heap if the game mode is set to automated, The game constructor receives the game mode. If the user is playing, the `unique_ptr` remains uninitialized. If the CPU is playing, the constructor initializes the `unique_ptr` and the instance of player.
3. In `Autoplayer.h` and `Autoplayer.cpp`. The `Player` class is initialized with pointer addresses to the food and snake objects. Since the instance is allocated on the heap, calls to the class constructor and destructor are signaled to the console. The method `void play()` runs a simple search for the food and generate a key press event to set the direction of the snake. Also, the Rule of Five is applied to this class.
4. In `PlayerHistory.h` and `PlayerHistory.cpp`. the `PlayerHistory` class handles the addition of player names and scores to the `Game_History.txt` with different methods that stores, reads and displays the content of the file. these methods are  `WritesThisGame`, `ReadGameHistory` and `DisplayPlayers`

## Rubric Points Addressed

### Loops, Functions, I/O
|Criteria| Addressed(Yes/No)|
|--------|------------|
The project demonstrates an understanding of C++ functions and control structures. == Yes, this is demonstrated in probably all the files inside the src directory where functions are appropriately defined and used correctly as well
The project reads data from a file and process the data, or the program writes data to a file. == Yes, this is demonstrated using the `PlayerHistory.h` and `PlayerHistory.cpp` files where the class handles the reading and writing in the `Game_History.txt` file.
The project accepts user input and processes the input. == Yes, this is demonstrated in the main.cpp where the player chooses from the main menu one of three options and when the first option is chosen(which allows the player to play the game) another input is taken from the player which is the player name.

### Object Oriented Programming
|Criteria| Addressed(Yes/No)|
|--------|------------|
The project uses Object Oriented Programming techniques. == Yes, and this is demonstrated in different files where classes are defined in a `.h` file and then using in a `.cpp` file.
Classes use appropriate access specifiers for class members. == Yes, this is demonstrated in different files as well but for example in the `PlayerHistory.h` the `GetPlayerName()` method acceses the player name of the class `PlayerHistory` 
Class constructors utilize member initialization lists. == Yes, this is also demonstrated in a couple of files but one example is the intialization of the `AutoPlayer` class which uses a constructor to get intialized
Classes abstract implementation details from their interfaces.== Yes, and this is represented in different files in the src.
Classes encapsulate behavior. == Yes, and this is represented by having all the functions belongong for a certain class to be defined in that class's `.h` file.


### Memory Management
|Criteria| Addressed(Yes/No)|
|--------|------------|
Classes abstract implementation details from their interfaces. == Yes, this is represesnted in different files in the src
The project uses destructors appropriately. == Yes, and this represented for the example in the `AutoPlayer` class.
The project follows the Rule of 5. == Yes, and this is represented in the `AutoPlayer` Class
The project uses smart pointers instead of raw pointers. == Yes, this is described in the `game.h` file in the intialization of an Autoplayer object where a `unique pointer` is used

