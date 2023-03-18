#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <stdio.h>
#include "FilesReading.h"

using namespace std;

void File::loadFile() {

	long int counter = 1;
	string line,word;
	ifstream file;

	file.open(File::inputfile, ios::in);
	if (file.good() == false) {
		cout << "Cannot open a file\n";
	}
	else {
		while (getline(file, line)) {
			stringstream str(line);
			while ((getline(str, word, ','))&&(counter <= stol(elementsss))) {
				loadedData.push_back(stoi(word));
				counter++;
			}
		}
	}
	
	file.close();
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

void File::bubble() {
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
	
	//size_t size = loadedData.size();
	/*
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size - 1; j++) {
			if (loadedData[j] > loadedData[j + 1]) {
				long tmp = loadedData[j];
				loadedData[j] = loadedData[j + 1];
				loadedData[j + 1] = tmp;
			}
		}
	}
	*/
