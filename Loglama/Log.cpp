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

		ifstream configFile(jsonAddress);	//Dosya açýldý.
		
		if (configFile.is_open()) {
			
			json jsonConfig;	//JSON dosyasný kullanmak için deðiþken.
			configFile >> jsonConfig;	//Dosya içeriði JSON nesnesine aktarýldý.

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

			logFile.open(logFileName, ios::app);	//Log dosyasý oluþturuldu.
			logFile << dateNow() + " : " + logMessage;	//Dosyanýn içine mesaj yazýldý.
			logFile.close();

			numberOfFiles++;

			fileList.push_back(dateNow()+".log");	//Eklenen dosyanýn adý listeye yazýldý.
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
		
		time_t dateNow = time(NULL);	//Zaman saniye olarak deðiþkene atandý.
		struct tm* dateNowInfo = localtime(&dateNow);	//Zaman struct tm yapýsýna dönüþtürüldü.
		char date[80];
		strftime(date, sizeof(date), "%Y-%m-%d %H_%M_%S" , dateNowInfo);	//Zaman diziye yazýldý.
		
		return string(date);
	}


	public:
	void manageLogFiles() {

		while (numberOfFiles >= maxFiles) {

			string oldestFile = logFilesLocation + fileList.front();	//En eski dosyanýn adý deðiþkene atandý.
			remove(oldestFile.c_str());		//En eski dosya silindi.
			fileList.erase(fileList.begin());	
			numberOfFiles--;

		}
		
	}
	
};

	int main() {
		
		Logger log("C:/Dosyalar/Logs/config.json" , "C:/Dosyalar/Logs/");	//Yapýcý metodun içine JSON dosyasýnýn konumu ve Log dosyalarýnýn oluþturulacaðý yer yazýlmalýdýr.
		log.log("Deneme mesajý");	
		
		
}
