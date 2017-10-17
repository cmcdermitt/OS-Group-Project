/* Usage: 
- All Logs must be dynamically allocated
- All Logs must be deleted using the delete operator
- When creating a log, pass in a string as its name
- To start a log call turn on
- To end a log call turn off
- This class currently does not have support for threads 
*/

#ifndef OS_GROUP_PROJECT_LOG_H
#define OS_GROUP_PROJECT_LOG_H

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
class Log
{
private: 
	
	double average; // Average time required to complete something
	int total; // How many times something has been done
	double last;  // The time for the last one
	std::clock_t currentStartTime; // Last time a process was started 
	std::clock_t currentEndTime; // Last time process ended 
	bool on; // The function has started
	std::string label; // What the log is describing
	static int numOfLogs; // Total number of logs
	static std::vector<std::string> records; // All records from logs 

	// PRIVATE Functions 
	void updateAverage(); // Updates Log Information
 	static void recordLogs(); // Stores All of the Log information in a Text File 
	void createIndividualLog(); // Generates individual log string for log object to be stored 
public: 
	//static const std::string STORAGE_NAME = "AccountingData.txt";
	Log(std::string label);
	bool turnOn();
	bool turnOff(); 
	~Log(); 



};

#endif
