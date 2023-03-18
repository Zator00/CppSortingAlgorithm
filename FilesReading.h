#include <iostream>
#include <vector>

using namespace std;

class File {
public:
	File(string inputFileName, string savedFileName, string algorithName, string timeFileName, string elements) {
		this->inputfile = inputFileName;
		this->savedfile = savedFileName;
		this->algorithm = algorithName;
		this->timefile = timeFileName;
		this->elementsss = elements;
	}
	void loadFile();
	void saveFile();
	void bubble();

public:
	vector<int> loadedData;
	string inputfile, savedfile, algorithm, timefile, elementsss;
};
