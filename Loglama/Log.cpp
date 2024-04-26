#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <thread>
#include <chrono>

using namespace std;
using namespace nlohmann;


class Logger {

	public:
	string logType;
	string logFilesLocation;
	int creationRate;
	int	maxFiles;
	int numberOfFiles;
	ofstream logFile;
	vector<string> fileList;
	string jsonFileLocation;
	bool run;
	
	
	public:
	Logger(const string& jsonAddress , const string& logsAdress) : jsonFileLocation(jsonAddress) , logFilesLocation(logsAdress) {
		
		numberOfFiles = 0;
		jsonFileLocation = jsonAddress;
		logFilesLocation = logsAdress;
		run = true;

		ifstream configFile(jsonAddress);	//Dosya a��ld�.
		
		if (configFile.is_open()) {
			
			json jsonConfig;	//JSON dosyasn� kullanmak i�in de�i�ken.
			configFile >> jsonConfig;	//Dosya i�eri�i JSON nesnesine aktar�ld�.

			maxFiles = jsonConfig["max_files"];		
			creationRate = jsonConfig["creation_rate"];
			logType = jsonConfig["log_type"];
			
			configFile.close();
		}

		else {
			cout << "JSON dosyasi acilamadi.";
			exit(1);
		}

		}	
	

	public:
	void log(string logMessage) {

		while (run) {
			
			string logFileName = "C:/Dosyalar/Logs/" + dateNow() + ".log";

			logFile.open(logFileName, ios::app);	//Log dosyas� olu�turuldu.
			logFile << dateNow() + " : " + logMessage;	//Dosyan�n i�ine mesaj yaz�ld�.
			logFile.close();

			numberOfFiles++;

			fileList.push_back(dateNow()+".log");	//Eklenen dosyan�n ad� listeye yaz�ld�.
			cout << "Logged." <<endl;
			cout << fileList.back()<<endl;
			
			if(logType == "second") std::this_thread::sleep_for(std::chrono::seconds(creationRate));
			else if(logType == "minute") std::this_thread::sleep_for(std::chrono::minutes(creationRate));
			else if (logType == "hour") std::this_thread::sleep_for(std::chrono::hours(creationRate));
			else if (logType == "day") std::this_thread::sleep_for(std::chrono::hours(creationRate*24));

			manageLogFiles();

		}
	}


	public:
	string dateNow() {
		
		time_t dateNow = time(NULL);	//Zaman saniye olarak de�i�kene atand�.
		struct tm* dateNowInfo = localtime(&dateNow);	//Zaman struct tm yap�s�na d�n��t�r�ld�.
		char date[80];
		strftime(date, sizeof(date), "%Y-%m-%d %H_%M_%S" , dateNowInfo);	//Zaman diziye yaz�ld�.
		
		return string(date);
	}


	public:
	void manageLogFiles() {

		while (numberOfFiles >= maxFiles) {

			string oldestFile = logFilesLocation + fileList.front();	//En eski dosyan�n ad� de�i�kene atand�.
			remove(oldestFile.c_str());		//En eski dosya silindi.
			fileList.erase(fileList.begin());	
			numberOfFiles--;

		}
		
	}
	
};

	int main() {
		
		Logger log("C:/Dosyalar/Logs/config.json" , "C:/Dosyalar/Logs/");	//Yap�c� metodun i�ine JSON dosyas�n�n konumu ve Log dosyalar�n�n olu�turulaca�� yer yaz�lmal�d�r.
		log.log("Deneme mesaj�");	
		
		
}
