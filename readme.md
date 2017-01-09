# CMake Lists Generator
#
 CMake Lists Generator is a simple CMakeLists.txt file generator.
  - Drag and Drop, drop your `Code` folder onto the exe to generate your CMakeLists file, or 
  - Place next to your project file and double click
  - Uses a template file that you can edit called `CMakeListTemplate.txt` in the project folder
    - Note that you can either let cmakegen create it automatically the first time you run it or edit the provided file supplied in this package

###### CMakeGen does not generate or parse uber file structures.
# 
### Using CMakeGen.exe
Simply drop the exe anywhere you like, then drag and drop your `Code` folder onto `CMakeGen.exe`.
Alternatively, you can place `CMakeGen.exe` in your project folder (above the `Code` folder) and run it. 
CmakeGen will traverse your Code folder directory structure and add any `.cpp` or `.h` files to sourcegroups for you. This will basically setup your Visual studio solution filters to match your file system directory structure.

This program is intended for small and/or early project development and testing and may not be suitable for larger or more serious projects.

### Building from source
Project target is set to vc140, the build uses the `filesystem TS` library (C++17) so you will need an up to date compiler.

### More information
For help or more information please look for the associated thread, or pm me (name `Uni Bliss`) on the Cry Engine &reg; forums.