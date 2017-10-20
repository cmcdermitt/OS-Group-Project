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
#include <mutex>
#include <vector>

struct Point;

struct Graph

{
	std::string label;
	std::vector<Point> points;
};

struct Point
{
	time_t x;
	int y;
};



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
	std::vector<Graph> graphs;
	static int numOfLogs; // Total number of logs
	static bool logged;
	static std::vector<std::string> records; // All records from logs
	std::string verboseLog;

	// PRIVATE Functions 
	void updateAverage(); // Updates Log Information
 	static void recordLogs(); // Stores All of the Log information in a Text File 
	void createIndividualLog(); // Generates individual log string for log object to be stored
	bool logEverything();

public: 
	//static const std::string STORAGE_NAME = "AccountingData.txt";
	Log(std::string label);
	bool turnOn();
	bool turnOff();
	bool recordData();
	std::mutex logIt;
	~Log();
	bool addGraph(std::string label);
	bool addPoint(std::string label, int yCoord);
	bool removeGraph(std::string label);



};



namespace Debug
{
	// Debugging flags; set to true if you want to print debug logs
	enum Debugging_Places {
		 DEBUG_ALL = true,
		 DEBUG_DRIVER = false,
		 DEBUG_LOADER = false,
		 DEBUG_DISK = false,
		 DEBUG_RAM = false,
		 DEBUG_SCHEDULER = true,
		 DEBUG_UTILITY = false,
		 DEBUG_VERBOSE = false,
		 DEBUG_DISPATCHER = true
	};
	// Debug Logs; can be turned off adn on by editing the Debugging_Places
	void debug(Debugging_Places p, std::string message);
	// verboseDebug is for if you want something to be printed out that is big and that
	// you would not want printed out during smaller debug times
	void verboseDebug(Debugging_Places p, std::string message);
}

#endif
