#include "StdAfx.h"
#include "CMakeGen.h"

#include <iomanip>
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>

// C++17 "Filesystem TS"
#include <filesystem>
using std::experimental::filesystem::recursive_directory_iterator;

std::map<std::string, std::vector<std::string>> CMakeGen::sources{};
std::map<std::string, std::string> CMakeGen::VSFilterGroups{};

void CMakeGen::GenerateCMakeList(std::string source_dir)
{
	// recurse source_dir for source files
	for (auto& dirEntry : recursive_directory_iterator(source_dir))
	{
		// Only source files
		if (dirEntry.path().filename().extension() == ".h"
			|| dirEntry.path().filename().extension() == ".cpp")
		{
			// Get just the path, no filename
			auto path = dirEntry.path();
			path.remove_filename();
			auto fullPath = path.string();

			// Get the information we need
			std::string fileName = dirEntry.path().filename().string();
			std::string relativePath = (fullPath == source_dir) ? "" : fullPath.substr(source_dir.length() + 1, fullPath.length() - source_dir.length());
			std::string VSFilter = (relativePath.empty())? "Main" : relativePath;
			std::string SourceGroupName((relativePath != "")? relativePath : "Main");
			SourceGroupName.erase(std::remove(SourceGroupName.begin(), SourceGroupName.end(), '\\'), SourceGroupName.end());

			// Set the Visual Studio Explorer Filter
			std::replace(VSFilter.begin(), VSFilter.end(), '\\', '/');
			if (VSFilterGroups.count(SourceGroupName) == 0)
				VSFilterGroups[SourceGroupName] = VSFilter;

			// Add this source file to the source group array
			std::replace(relativePath.begin(), relativePath.end(), '\\', '/');
			sources[SourceGroupName].emplace_back(relativePath + ((relativePath.length() > 0) ? "/" : "") + fileName);
		}
	}

	// Now we can traverse our array and build our sources more easily

	// Get our template file data first
	std::string CMakeContent{};

	if (!UTIL::CheckFileExists(source_dir + "/../CMakeListTemplate.txt"))
	{
		std::cout << "[Warning] Missing CMakeList Template! Generating a default template (Cryengine 5.3 basic)!";

		// Get default
		CMakeContent = UTIL::GetTextResourceA(GetModuleHandleA(NULL), IDR_CMAKETEMPLATE);

		// Save externally for user customization
		std::ofstream CMakeFile(source_dir + "/../CMakeListTemplate.txt");
		CMakeFile << CMakeContent;
		CMakeFile.close();
	}
	else
	{
		CMakeContent = UTIL::ReadWholeFile(source_dir + "/../CMakeListTemplate.txt");
	}

	// Generate source strings for each group
	std::string CMakeSourceData{};
	
	for (auto &g : VSFilterGroups)
	{
		CMakeSourceData.append("set (SourceGroup_" + g.first + "\r\n");
		for (auto &s : sources.at(g.first))
		{
			CMakeSourceData.append("\t\"" + s + "\"\r\n");
		}
		CMakeSourceData.append(std::string(")\r\n") 
			+ "source_group(\"" + g.second + "\" FILES ${" + "SourceGroup_" + g.first + "})\r\n\r\n"
		);
	}

	// Generate sources list
	CMakeSourceData.append("set (SOURCE\r\n");
	for (auto &g : VSFilterGroups)
	{
		CMakeSourceData.append("\t${SourceGroup_" + g.first + "}\r\n");
	}
	CMakeSourceData.append(")\r\n");

	// replace token in template
	auto pos = CMakeContent.find("%%CMakeGen_SOURCES%%");
	if (pos == std::string::npos)
	{
		std::cout << "[Error] Could not find replacement token in cmake template file (refresh the template?)!";
		return;
	}

	CMakeContent.replace(pos, 20, CMakeSourceData);

	// Normalize line endings...
	CMakeContent.erase(std::remove(CMakeContent.begin(), CMakeContent.end(), '\r'), CMakeContent.end());

	if (DO_BACKUP)
	{
		// backup old file
		if (UTIL::CheckFileExists(source_dir + "/CMakeLists.txt"))
		{
			// Get a good suffix to make this backup unique
			auto time = std::time(nullptr);
			struct tm timel;
			localtime_s(&timel, &time);
			std::ostringstream timest;
			timest << std::put_time(&timel, "%y%m%d_%H%M%S");
			auto prefix = timest.str();

			// Write the backup file
			std::ofstream CMakeFile(source_dir + "/" + prefix + "_CMakeLists.txt");
			CMakeFile << UTIL::ReadWholeFile(source_dir + "/CMakeLists.txt");
			CMakeFile.close();

			std::cout << "backup saved to " + source_dir + "/" + prefix + "_CMakeLists.txt";
		}
	}

	// write new file
	std::ofstream CMakeFile(source_dir + "/CMakeLists.txt");
	CMakeFile << CMakeContent;
	CMakeFile.close();

	std::cout << "Finished";
}
