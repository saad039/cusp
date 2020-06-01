# cusp

_A simple and easy to use command line build tool for C++ based on premake_


## Prerequisites

  

1. Download and add [ Premake 5.0 ](https://premake.github.io/) to your system's path variable.

2. ```make``` for linux only.
3. ```C++17```.
4. ```g++``` or ```clang``` for linux only.
5. For Windows, ```Visual Studio 2017``` or ```Visual Studio 2019``` .

  

## How To Build ?

  

Clone the repository to a local destination and make sure to fetch all dependencies.

> ```git clone https://github.com/saad039/cusp```

  

## For Linux

  

1.  On your console, enter ``` premake5 gmake```

2. Then ``` make config=release```

3. From ```/bin/cusp/Release/``` directory, copy cusp binary to a location inside your system's path variable.

  

## For Windows

  

1. Open command prompt and enter ```premake5 vs2017``` for Visual Studio 2017 or ```premake5 vs2019``` for Visual Studio 2019

2. Build the solution in release mode.

3. From ```/bin/cusp/Release/```, copy cusp binary to a location inside your system's path variable.


## Cusp Commands

| Commands | Actions |
|---|---|
| cusp init | Creates a new solution in the present working directory. |
| cusp add ```projectName``` header ```head.h or head.hpp``` | Adds head.h/hpp header file into the project projectName under your solution directory. |
| cusp add ```projectName``` src ```src.cc or src.cpp``` | Adds src.cc/cpp source file into the project projectName under your solution directory. |
| cusp add ```projectName``` class ```className``` | Adds className.h and className.cpp header and source files into the project projectName under your solution directory. |
|cusp update | Regenerates premake5.lua for all projects and solutions. This should be used if changes were made to ```cusp.json``` manually. Note that any changes made to ```premake5.lua``` files manually will be lost. |
|cusp make | Generates makefiles for all projects and solution. |
|cusp vs2015|Generates visual studio 2015 solution files. |
|cusp vs2017|Generates visual studio 2017 solution files. |
|cusp vs2019|Generates visual studio 2019 solution files. |
|cusp vscode|Generates tasks.json file for vscode. Press Ctrl+Shift+p inside vscode to select default build configuration. |
|cusp xcode|Generates xcode solution files for all projects and solution. |
|cusp build debug |Generates debug binaries from both makefiles and sln files. Note that cusp will use MSBuild to build the project if you are using Microsoft C++ Compiler|
|cusp build release |Generates release binaries from both makefiles and sln files. Note that cusp will use MSBuild to build the project if you are using Microsoft C++ Compiler|


> This is a hobby project of mine. If you find any bug  or want to contribute, please open a pull request.

You can email me at msaadahmed039@gmail.com

