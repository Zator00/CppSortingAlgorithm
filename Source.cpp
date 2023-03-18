#include <string.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <locale>
#include <codecvt>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include <stdio.h>
#include <chrono>
#include "FilesReading.h"



using namespace std;




int main() {
	string path = "D:\\VisualStudio\\moje_projekty\\C-Sorting-algorithm\\SDiZO_Console\\SDiZO_Console\\config.ini";
	
	string inFile, savFile, alg, fileTime, element;

	const string& section = "MAIN_SEC";
	const string& inputValue = "inputFile";
	const string& saveValue = "savedFile";
	const string& algValue = "algorithm";
	const string& timeValue = "times";
	const string& elValue = "elements";
	const string& def = " ";

	char infile[256] = {};
	char savfile[256] = {};
	char algorithm[256] = {};
	char time[256] = {};
	char elements[256] = {};


	GetPrivateProfileString(section.c_str(), inputValue.c_str(), def.c_str(), infile , 255, path.c_str());
	GetPrivateProfileString(section.c_str(), saveValue.c_str(), def.c_str(), savfile, 255, path.c_str());
	GetPrivateProfileString(section.c_str(), algValue.c_str(), def.c_str(), algorithm, 255, path.c_str());
	GetPrivateProfileString(section.c_str(), timeValue.c_str(), def.c_str(), time, 255, path.c_str());
	GetPrivateProfileString(section.c_str(), elValue.c_str(), def.c_str(), elements, 255, path.c_str());

	string Fileinput = (string)infile;
	string Filesave = (string)savfile;
	string Filealg = (string)algorithm;
	string Filetime = (string)time;
	string Fileelements = (string)elements;
	


	File fileToMod(Fileinput, Filesave, Filealg, Filetime, Fileelements);
	cout << fileToMod.inputfile << endl;
	cout << fileToMod.savedfile << endl;
	cout << fileToMod.algorithm << endl;

	fileToMod.loadFile();

	if (fileToMod.algorithm == "bubble") {
		auto begin = std::chrono::high_resolution_clock::now();
		fileToMod.bubble();
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
		ofstream file(Filetime);
			file << "Bubble: " << elapsed.count() * 1e-9 << "s";
		file.close();
	}

	fileToMod.saveFile();


	return 0;
}