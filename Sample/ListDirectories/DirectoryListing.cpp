#include<iostream>
#include<filesystem>
#include<string>
#include<vector>
#include "TimeBasedFileSorting.h"

using namespace std;
namespace fs = filesystem;

size_t getFolderOrFileSize(std::string path)
{
	size_t size = 0;
	fs::path pathObj(path);
	if (fs::exists(pathObj) && fs::is_directory(pathObj))
	{
		for (auto it = fs::recursive_directory_iterator(path); it != fs::recursive_directory_iterator(); it++)
		{
			if (!(it->is_directory()))
			{
				size += it->file_size();
			}
		}
	}
	else if(fs::exists(pathObj) && fs::is_regular_file(pathObj))
	{
		size = fs::file_size(pathObj);
	}
	return size;
}

int main( int argc, char* argv[])
{
	int returnCode = 0;
	if (argc < 2 || argc > 4)  
	{
		cout << "****************** USAGE ********************" << endl;
		cout << "DirectoryList.exe <path> <option1> <option2>" << endl;
		cout << "option1 = IncludeAll , DirectoriesOnly" << endl;
		cout << "option2 = Ascending , Descending" << endl;
		cout << "*********************************************" << endl;
	}
	else
	{ 
		string path = argv[1];
		string contentSelection = "IncludeAll";
		string sortOrder = "Ascending";

		if (argc > 2)
		{
			contentSelection = argv[2];
		}
		if (argc > 3)
		{
			sortOrder = argv[3];
		}

		bool directoriesOnly = false;
		bool sortAscenting = false;
		directoriesOnly = !contentSelection.compare("DirectoriesOnly");
		sortAscenting = sortOrder.compare("Ascending");

		TimeBasedFileSorting fileSort(path, directoriesOnly, sortAscenting);
		vector<std::string> contentList = fileSort.getSortedContentList();
		for (auto path = contentList.begin(); path != contentList.end(); path++)
		{
			cout << *path << "\t size = " << getFolderOrFileSize(*path) / (1024 * 1024) << " MB" << endl;
		}
		returnCode = 1;
	}

	return 1;
}