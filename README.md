# 7 days project

This project was part of a challenge where I would select one programming language that I would like to learn and just use it to create a piece of software that is usable within 7 days with the final date and time being Sunday 11:59 PM Indian Standar time

The Language of choice this time C++

With this language in mind I decided to make a discord bot that integrated with a local ollama model running on the same server that hosts the bot.

The 3rd party libraries used in this program were:-
- cpp-httplib: https://github.com/yhirose/cpp-httplib
- JSON for Modern C++: https://github.com/nlohmann/json
- C++ Discord API Bot Library (D++): https://github.com/brainboxdotcc/DPP

This was my first time make a real world application with C++ and also my first time using CMake.

Steps to install:-
-
- Clone the github repo
```shell
git clone https://github.com/Heckrexter/Discord-LLama-Cpp
```

- Navigate into the repository
```shell
cd /path/to/Discord-LLama-Cpp
```
- Create a file in the include/ directory named token.h and write the following code in it and save
```cpp
// file to store bot token
#include <iostream>

const std::string stored_BOT_TOKEN = "DISCORD_BOT_TOKEN";
```
- Make a folder named build and navigate into it
```shell
mkdir build
cd build
```
- Configure the build with the following command
```shell
cmake ..
```
- Compile the file with the follwing command
```shell
make
```


notes:-
-
- Due to the time crunch on this project long length responses over 2000 characters in discord havent been verified.
- You will have to change the Libdpp folder location to point to your local installation of that library in the CMakeLists.txt