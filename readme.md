CMakeGen is a simple CMakeLists.txt file generator.

You can either supply it with the path to your source directory on the command line or run it directly,
If you run it directly CMakeGen will assume your source folder is in the relative (to exe) directory "Code".

NOTE*
Upon first use CMakeGen will generate a default CMakeLists.txt template file name (appropriately) CMakeLists_Template.txt.
Use this file to change the layout of and customize the generated CMakeLists.txt file.

The CMakeLists.txt file will be written (or overwritten) to the source directory supplied (or assumed).