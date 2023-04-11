#include <iostream>
#include <vector>

using namespace std;

class File {
public:
	File(string inputFileName, string savedFileName, string algorithName, string timeFileName, string elements ) {
		this->inputfile = inputFileName;
		this->savedfile = savedFileName;
		this->algorithm = algorithName;
		this->timefile = timeFileName;
		this->elementsss = elements;
	}
	void loadFile(int iterator);
	void saveFile();
	void bubble();
	void bubbleWithoutClear();
	void combsort();
	void combsortWithoutClear();
	void countingsort();
	void countingsortWithoutClear();

public:
	vector<int> loadedData;
	string inputfile, savedfile, algorithm, timefile, elementsss; 
	int counterfile = 0;
};
