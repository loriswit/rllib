# RLLib
The Rayman Legends Library is a small library that allows you to manipulate assets from the game [Rayman Legends](https://www.ubisoft.com/en-us/game/rayman-legends/). This project is still only in its early stages and will hopefully incorporate more features in the future.

Current features include:
- Extracting and importing assets files.
- Opening a scene and manipulating its entities.
- Running a scene in the game engine.

## Installation

You will need a C++ compiler supporting the C++17 standard, as well as [CMake](https://cmake.org/) and [Conan](https://conan.io/). Open a terminal in the folder where you want the library to be built and run the following commands:

```bash
cmake path/to/source
cmake --build . --target rl
```

Once done, the compiled library can be found in the *lib* subfolder.

## Documentation

You can find tutorials and information about how the library works on the project [wiki](https://github.com/olybri/rllib/wiki). You can also check the [documentation](https://olybri.github.io/rllib/annotated.html) of classes and functions.

