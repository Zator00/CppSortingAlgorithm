// compile 3 files: g++ Source.cpp FilesReadings.h FilesReadings.cpp -o all
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
#include <filesystem>
#include "FilesReading.h"

#define REPEATS 10

using namespace std;
namespace fs = std::filesystem;



int main() {
	string path = fs::current_path().generic_string().append("\\config.ini") ;
	
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

	cout << "Zczytywanie z pliku: " << Fileinput << endl;
	cout << "Zapis do pliku: " << Filesave<< endl;
	cout << "Zapis srednich czasow do pliku: " << Filetime << endl;
	

	File fileToMod(Fileinput, Filesave, Filealg, Filetime, Fileelements);

	vector<double> sortTimes;
	vector<double> allTimes;

	stringstream ss(Fileelements);
	vector<int> numsFile;
	while (ss.good()) {
    	std::string substr;
    	getline(ss, substr, ',');
    	numsFile.push_back(std::stoi(substr));
    }
	vector<double> avgTimes;
	if(fileToMod.algorithm == "bubble"){
		for(int z=0; z<numsFile.size();z++ ){

			if(z == 0){cout<<"Zmierzone i posortowane instancje: " << 0 << "/" << numsFile.size()<<endl;}
			for(int i = 0; i<REPEATS;i++){
				fileToMod.loadFile(z);

				if (fileToMod.algorithm == "bubble") {

					if (z == numsFile.size()-1 && i==REPEATS-1){
						auto begin = std::chrono::high_resolution_clock::now();
						fileToMod.bubbleWithoutClear();
						auto end = std::chrono::high_resolution_clock::now();
						auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
						sortTimes.push_back(elapsed.count() * 1e-9);
					}else{
						auto begin = std::chrono::high_resolution_clock::now();
						fileToMod.bubble();
						auto end = std::chrono::high_resolution_clock::now();
						auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
						sortTimes.push_back(elapsed.count() * 1e-9);
					}
					
					
				}				
			}
		
			double sumTime =0;
			
			for (int i = 0; i < sortTimes.size();i++){
				
				sumTime += sortTimes.at(i);
				allTimes.push_back(sortTimes.at(i));
			}
			
			avgTimes.push_back(sumTime/ (double)sortTimes.size());
			sumTime = 0;
			sortTimes.clear();
			cout<<"Zmierzone i posortowane instancje: " << z+1 << "/" << numsFile.size()<<endl;
		}
		int iterator = 0;
		int holder = 0;
		ofstream file(Filetime);
		for(int i = 0; i<allTimes.size();i++){
			
			if(holder == REPEATS)
			{
				iterator++;
				holder = 0;
			}
			file << "Bubble for "<< numsFile.at(iterator) << " elements - time: " << allTimes.at(i) << "s" << endl;
			holder++;
		}
		for(int i = 0; i < avgTimes.size();i++){
			file << "Bubble for "<< numsFile.at(i) << " elements - avg time: " << avgTimes.at(i) << "s" << endl;
		}
		file.close();
		allTimes.clear();
		
	}
	if(fileToMod.algorithm == "combsort"){
			for(int z=0; z<numsFile.size();z++ ){

			if(z == 0){cout<<"Zmierzone i posortowane instancje: " << 0 << "/" << numsFile.size()<<endl;}
			for(int i = 0; i<REPEATS;i++){
				fileToMod.loadFile(z);

				if (fileToMod.algorithm == "combsort") {

					if (z == numsFile.size()-1 && i==REPEATS-1){
						auto begin = std::chrono::high_resolution_clock::now();
						fileToMod.combsortWithoutClear();
						auto end = std::chrono::high_resolution_clock::now();
						auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
						sortTimes.push_back(elapsed.count() * 1e-9);
					}else{
						auto begin = std::chrono::high_resolution_clock::now();
						fileToMod.combsort();
						auto end = std::chrono::high_resolution_clock::now();
						auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
						sortTimes.push_back(elapsed.count() * 1e-9);
					}
					
					
				}				
			}
			double sumTime =0;
			
			for (int i = 0; i < sortTimes.size();i++){
				sumTime += sortTimes.at(i);
				allTimes.push_back(sortTimes.at(i));
			}
			
			avgTimes.push_back(sumTime/ (double)sortTimes.size());
			sumTime = 0;			
			sortTimes.clear();
			cout<<"Zmierzone i posortowane instancje: " << z+1 << "/" << numsFile.size()<<endl;
		}

		int iterator = 0;
		int holder = 0;
		ofstream file(Filetime);
		for(int i = 0; i<allTimes.size();i++){
			
			if(holder == REPEATS)
			{
				iterator++;
				holder = 0;
			}
			file << "Combsort for "<< numsFile.at(iterator) << " elements - time: " << allTimes.at(i) << "s" << endl;
			holder++;
		}
		for(int i = 0; i < avgTimes.size();i++){
			file << "Combsort for "<< numsFile.at(i) << " elements - avg time: " << avgTimes.at(i) << "s" << endl;
		}
		file.close();
		allTimes.clear();

	}
	if(fileToMod.algorithm == "counting"){
			for(int z=0; z<numsFile.size();z++ ){

			if(z == 0){cout<<"Zmierzone i posortowane instancje: " << 0 << "/" << numsFile.size()<<endl;}
			for(int i = 0; i<REPEATS;i++){
				fileToMod.loadFile(z);

				if (fileToMod.algorithm == "counting") {

					if (z == numsFile.size()-1 && i==REPEATS-1){
						auto begin = std::chrono::high_resolution_clock::now();
						fileToMod.countingsortWithoutClear();
						auto end = std::chrono::high_resolution_clock::now();
						auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
						sortTimes.push_back(elapsed.count() * 1e-9);
					}else{
						auto begin = std::chrono::high_resolution_clock::now();
						fileToMod.countingsort();
						auto end = std::chrono::high_resolution_clock::now();
						auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
						sortTimes.push_back(elapsed.count() * 1e-9);
					}
					
					
				}				
			}
		
			double sumTime =0;
			
			for (int i = 0; i < sortTimes.size();i++){
				sumTime += sortTimes.at(i);
				allTimes.push_back(sortTimes.at(i));
			}
			
			avgTimes.push_back(sumTime/ (double)sortTimes.size());
			sumTime = 0;
			sortTimes.clear();
			cout<<"Zmierzone i posortowane instancje: " << z+1 << "/" << numsFile.size()<<endl;
		}

		int iterator = 0;
		int holder = 0;
		ofstream file(Filetime);
		for(int i = 0; i<allTimes.size();i++){
			
			if(holder == REPEATS)
			{
				iterator++;
				holder = 0;
			}
			file << "Countingsort for "<< numsFile.at(iterator) << " elements - time: " << allTimes.at(i) << "s" << endl;
			holder++;
		}
		for(int i = 0; i < avgTimes.size();i++){
			file << "Countingsort for "<< numsFile.at(i) << " elements - avg time: " << avgTimes.at(i) << "s" << endl;
		}
		file.close();
		allTimes.clear();
	}

	fileToMod.saveFile();
	char choice;
	cout << "Czy wyswietlic posortowane liczby? (Ostatnia instancja) t/n \n";
	cin >> choice;
	switch(choice){
		case 't':{
			fileToMod.showSortedData();
			break;
		}
		default:{
			break;
		}
	}

	return 0;
}