#pragma once
#include <string>
#include <vector>
#include <map>

#define DO_BACKUP 0

struct CMakeGen
{
	static std::vector<std::string> sourcegroups;
	static std::map<std::string, std::vector<std::string>> sources;
	static std::map<std::string, std::string> VSFilterGroups;

	static void GenerateCMakeList(std::string source_dir);

private:
	CMakeGen();
};
