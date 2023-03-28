#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <stdio.h>
#include "FilesReading.h"

using namespace std;

void File::loadFile(int iterator) {

	long int counter = 0;
	string line,word;
	ifstream file;

	stringstream ss(elementsss);
	vector<int> nums;
	    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ',');
        nums.push_back(std::stoi(substr));
    }
	file.open(File::inputfile, ios::in);
	if (file.good() == false) {
		cout << "Cannot open a file\n";
	}
	else {
		while (getline(file, line)) {
			stringstream str(line);
			while ((getline(str, word, ','))&&(counter < (nums.at(iterator)))) {
				loadedData.push_back(stoi(word));
				counter++;
			}
		}
	}
	
	file.close();
}

void File::bubble() {

	stringstream ss(elementsss);
	vector<int> nums;
	while (ss.good()) {
        std::string substr;
        getline(ss, substr, ',');
        nums.push_back(std::stoi(substr));
    }

	size_t size = loadedData.size();
	for (size_t i = 0; i < size; i++) {


		for (size_t j = 0; j < size - 1; j++) {
			if (loadedData[j] > loadedData[j + 1]) {
					long tmp = loadedData[j];
					loadedData[j] = loadedData[j + 1];
					loadedData[j + 1] = tmp;
			}
		}
		loadedData.clear();
	}
}

void File::bubbleWithoutClear() {
	size_t size = loadedData.size();
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size - 1; j++) {
			if (loadedData[j] > loadedData[j + 1]) {
					long tmp = loadedData[j];
					loadedData[j] = loadedData[j + 1];
					loadedData[j + 1] = tmp;
			}
		}
			

	}
}

void File::combsort(){
	bool swapper;
    int gap = loadedData.size();
    double shrink = 1.25;
    int temp;
    do {
        gap = (int)gap / shrink;
        if (gap < 1)
            gap = 1;

        swapper = false;
        for (int i = 0; (i + gap) < loadedData.size(); i++) {
            if (loadedData[i] > loadedData[i + gap]) {
                swap(loadedData[i], loadedData[i + gap]);
                swapper = true;
            }
        }
    } while ((gap > 1) || (swapper == true));
}

void File::saveFile() {
	ofstream file(File::savedfile);

	// Send data to the stream
	for (int i = 0; i < loadedData.size(); ++i)
	{
		if (i == loadedData.size() - 1) {
			file << loadedData.at(i);
		}
		else
			file << loadedData.at(i) << ",";
	}

	// Close the file
	file.close();
}

