#include<iostream>
#include<filesystem>
#include<string>
#include<vector>

using namespace std;
namespace fs = filesystem;

int main( int argc, char* argv[])
{
	if (argc < 2)  
	{
		cout << "*******USAGE*******" << endl;
		cout << "DirectoryList.exe <path>" << endl;
		cout << "*******************" << endl;
		return 1;
	}
	string path = argv[1];
	vector<fs::directory_entry> files;
	for (const auto& entry : fs::directory_iterator(path))
	{
		files.push_back(entry);
	}
	
	sort(files.begin(), files.end(), [](fs::directory_entry& p1, fs::directory_entry& p2) {
		return (p1.last_write_time() < p2.last_write_time());
		});

	for (auto entry = files.begin(); entry != files.end(); entry++)
	{
		if (entry->is_directory()) {
			cout << entry->path().filename().string() << endl;
		}
	}
	return 1;
}