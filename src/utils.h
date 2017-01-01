#pragma once
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>

struct UTIL {

	bool fileExists(const std::string& file) {
		struct stat buf;
		return (stat(file.c_str(), &buf) == 0);
	}

	static std::string ExePath() {
		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		return std::string(buffer).substr(0, pos);
	}

	static bool CheckFolderExists(const std::string path) {

		struct stat info;

		if (stat(path.c_str(), &info) != 0)
			return false;
		else if (info.st_mode & S_IFDIR)
			return true;
		else
			return false;
	}

	static bool CheckFileExists(const std::string path) {

		struct stat info;

		if (stat(path.c_str(), &info) != 0)
			return false;
		else if (info.st_mode & S_IFDIR)
			return false;
		else
			return true;
	}

	static std::string GetTextResourceA(HMODULE hModule, int ResourceId)
	{
		HRSRC hResource = FindResourceA(hModule, MAKEINTRESOURCEA(ResourceId), "TEXT");

		if (hResource)
		{
			HGLOBAL hLoadedResource = LoadResource(hModule, hResource);

			if (hLoadedResource)
			{
				LPVOID pLockedResource = LockResource(hLoadedResource);

				if (pLockedResource)
				{
					DWORD dwResourceSize = SizeofResource(hModule, hResource);

					if (0 != dwResourceSize)
					{
						return std::string(static_cast<char*>(pLockedResource), dwResourceSize);
					}
				}
			}
		}

		return "";
	}


	static std::string ReadWholeFile(std::string path)
	{
		std::stringstream buffer;

		std::ifstream t(path);
		buffer << t.rdbuf();
		return buffer.str();
	}
};