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

struct Graph {
    time_t origin;
    std::string label;
    std::vector<Point*> points;
};

struct Point {
    double x;
    int y;
};


class Log {
private:

    double average; // Average time required to complete something
    int total; // How many times something has been done
    double last;  // The time for the last one
    std::clock_t current_start_time; // Last time a process was started
    std::clock_t current_end_time; // Last time process ended
    bool on; // The function has started
    std::string label; // What the log is describing
    std::vector<Graph*> graphs;
    std::vector<std::string> rawText;
    static int num_of_logs; // Total number of logs
    static bool logged;
    static std::vector<std::string> records; // All records from logs
    std::string verboseLog;

    // PRIVATE Functions
    void update_average(); // Updates Log Information
    // Stores All of the Log information in a Text File
    void update_individual_log(); // Generates individual log string for log object to be stored
    static void record_log();


public:
    //static const std::string STORAGE_NAME = "AccountingData.txt";
    Log(std::string label);

    bool turn_on();
    bool record_data();
    bool turn_off();

    static bool logEverything();

    std::mutex log_it;

    ~Log();

    bool add_graph(std::string label);

    bool add_point(std::string label, int y_coord);

    bool remove_graph(std::string label);



    void addRawText(std::string addText);

    double getAverage();

    double getLast();

  static  std::string total_average_wait_time(std::vector<Log*> l);

};


namespace Debug {
    // Debugging flags; set to true if you want to print debug logs
    enum Debugging_Places {
        ALL = true,
        DRIVER = false,
        LOADER = false,
        DISK = false,
        RAM = false,
        SCHEDULER = true,
        UTILITY = false,
        VERBOSE = true,
        DISPATCHER = true,
        OUTPUT = true
    };

    // Debug Logs; can be turned off adn on by editing the Debugging_Places
    void debug(Debugging_Places p, std::string message);

    // verbose_debug is for if you want something to be printed out that is big and that
    // you would not want printed out during smaller debug times
    void verbose_debug(Debugging_Places p, std::string message);

    const int ONLY_FOR_TEST = false;
    void translate_program_file_to_binary();



}

#endif
