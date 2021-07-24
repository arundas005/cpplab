#include "TimeBasedFileSorting.h"


using namespace std;

TimeBasedFileSorting::TimeBasedFileSorting(std::string fullpath,
	bool directoriesOnly, bool sortAscending) : _fullPath(fullpath),
																_directoriesOnly(directoriesOnly),
																_sortAscending(sortAscending)
{
}


vector<std::string> TimeBasedFileSorting::getSortedContentList()
{
	_contentList.clear();

	for (const auto& entry : fs::directory_iterator(_fullPath))
	{
		if (_directoriesOnly)
		{
			if (entry.is_directory())
			{
				_contentList.push_back(entry);
			}
		}
		else
		{
			_contentList.push_back(entry);
		}
	}

	sortContent();

	vector<string> contentListAsString;
	convertPathtoString(contentListAsString);

	return contentListAsString;
}

void TimeBasedFileSorting::sortContent()
{
	if (_sortAscending)
	{
		sort(_contentList.begin(), _contentList.end(), [](fs::directory_entry& p1, fs::directory_entry& p2) {
			return (p1.last_write_time() > p2.last_write_time());
			});
	}
	else
	{
		sort(_contentList.begin(), _contentList.end(), [](fs::directory_entry& p1, fs::directory_entry& p2) {
			return (p1.last_write_time() < p2.last_write_time());
			});
	}
}


void TimeBasedFileSorting::convertPathtoString(std::vector<std::string>& content)
{
	for (const auto& entry : _contentList)
	{
		content.push_back(entry.path().string());
	}
}
