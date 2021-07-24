#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class TimeBasedFileSorting
{
	std::string _fullPath;
	bool _directoriesOnly;
	bool _sortAscending;
	std::vector<fs::directory_entry> _contentList;
	void sortContent();
	void convertPathtoString(std::vector<std::string>&);
public:
	explicit TimeBasedFileSorting(std::string fullpath,
								  bool directoriesOnly = false,
								  bool sortAscending = false);
	std::vector<std::string> getSortedContentList();
};

