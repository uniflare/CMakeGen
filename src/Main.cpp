#include "StdAfx.h"
#include <Windows.h>
#include <iostream>

#include "CMakeGen.h"


int main(int argc, char ** argv) {

	std::string CurrentDirectory = UTIL::ExePath();
	std::string DefaultSourceDirectory{ CurrentDirectory + "\\Code" };
	std::string TargetSourceDirectory;

	// Error
	if (argc > 2)
	{
		std::cout << "Incorrect usage.\n"
			<< "Usage: CMakeListsGen.exe (\"Path/To/Source/Directory\")\n"
			<< "Press enter to quit.";

		std::getchar();

		return 0;
	}

	// Use default source code path if none provided
	if (argc == 1)
		TargetSourceDirectory = DefaultSourceDirectory;
	else
		TargetSourceDirectory = std::string(argv[1]);

	// check source folder exists
	if (!UTIL::CheckFolderExists(TargetSourceDirectory))
	{
		std::cout << "Could not determine source folder (tried \"" << TargetSourceDirectory << "\").\n"
			<< "Usage: CMakeListsGen.exe (\"Path/To/Source/Directory\")\n"
			<< "Press enter to quit.";

		std::getchar();

		return 0;
	}
	else
	{
		CMakeGen::GenerateCMakeList(TargetSourceDirectory);
	}


	return 0;
}

