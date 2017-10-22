#include "Log.h"
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "termcolor.hpp"
#include "Utility.h"
#include <fstream>

bool Log::logged = false;
// Static variable initialization
int Log::num_of_logs = 0;
std::vector<std::string> Log::records = std::vector<std::string>();

// Initializes a log object
Log::Log(std::string label) {
    this->label = label;
    on = false;
    num_of_logs++;
    average = 0;
    total = 0;
    graphs = std::vector<Graph*>();
    rawText = std::vector<std::string>();
}

Log::~Log() {

}

// Records the current average time for 
void Log::update_average() {
    double temp = average * static_cast<double>(total);
    temp += static_cast<double>((static_cast<double>(current_end_time) - static_cast<double>(current_start_time)) /
                                CLOCKS_PER_SEC);
    total++;
    average = temp / static_cast<double>(total);
}

// Starts a timer for whatever process you are using 
bool Log::turn_on() {
    if (on)
        return false;
    on = true;
    current_start_time = std::clock();
    return true;
}

// Ends a timer for whatever process you are using
bool Log::turn_off() {
    if (!on)
        return false;
    on = false;
    current_end_time = std::clock();
    last = static_cast<double>(current_end_time) - static_cast<double>(current_start_time);
    last = last / CLOCKS_PER_SEC;
    update_average();
    return true;
}

void Log::record_log() {
    std::ofstream log = std::ofstream();
    log.open("LogFile.txt");
    log << "Log Data for " + std::to_string(time(0)) << "\n\n";
    for (std::string element : Log::records) {
        log << element;
        log << "\n-----------------------------------------------\n";
    }
    log.close();
}

bool Log::logEverything() {
    if (Log::logged)
        return false;
    else {
        record_log();
        Log::logged = true;
        return true;
    }

}

void Log::update_individual_log() {
    std::string log =
            "Label:\t\t" + label + "\nTotal:\t\t" + std::to_string(total) + "\nAverage:\t" + std::to_string(average) +
            " seconds\nLast:\t\t"
            + std::to_string(last) + " seconds";
    std::string graph_string;
    log += "\nGraphs:\t";
    for (int i = 0; i < graphs.size(); i++) {
        std::cout << "\n";
        graph_string += graphs[i]->label + ":\t";
        for (int j = 0; j < graphs[i]->points.size(); j++) {
            graph_string +=
                    std::to_string(graphs[i]->points[j]->x) + "," + std::to_string(graphs[i]->points[j]->y) + "\n";
        }


    }

    log+= "\nRaw Text\n";
    for(std::string s : rawText)
    {
        log+= s;
    }
    log = log + graph_string;

    Log::records.push_back(log);
}

bool Log::record_data() {
    log_it.lock();
    this->update_individual_log();
    log_it.unlock();
}

bool Log::add_graph(std::string label) {
    Graph *g = new Graph();
    g->label = label;
    g->points = std::vector<Point*>();
    g->origin = std::clock() / CLOCKS_PER_SEC;
    graphs.push_back(g);
    return true;
}

bool Log::add_point(std::string label, int y_coord) {
    for (Graph *g : graphs) {
        if (g->label == label) {
            Point *p = new Point();
            p->x = (std::clock()/static_cast<double>(CLOCKS_PER_SEC)) - g->origin;
            p->y = y_coord;
            g->points.push_back(p);
            return true;
        }

    }
    return false;
}

bool Log::remove_graph(std::string label) {
    for (int i = 0; i < graphs.size(); i++) {
        if (label == graphs[i]->label) {
            graphs.erase(graphs.begin() + i);
            return true;
        }

    }
    return false;
}

void Log::addRawText(std::string addText) {
    rawText.push_back(addText);
}

double Log::getAverage() { return  average;}
double Log::getLast() { return last;}
std::string Log::total_average_wait_time(std::vector<Log *> l) {
    double waitTime = 0;
    double completeTime = 0;
    double jobCount = 0;
    for(int i = 0; i < l.size(); i = i + 2)
    {
        waitTime += l.at(i)->getLast();
        completeTime += l.at(i + 1)->getLast();
        jobCount++;
    }
    waitTime /= jobCount;
    completeTime /= jobCount;
    Log *finalLog = new Log("All Jobs");
    finalLog->addRawText("Average wait time " + std::to_string(waitTime) + "\n");
    finalLog->addRawText("Average complete time " + std::to_string(completeTime) + "\n");
    finalLog->turn_on();
    finalLog->turn_off();
    finalLog->record_data();



}

// Logging function
void Debug::debug(Debugging_Places p, std::string message) {
    if (p && Debugging_Places::ALL) {
        char color = message[0];
        message = message.substr(1);

        switch (color) {
            case 'R':
                std::cout << termcolor::red << message << termcolor::reset << std::endl;
                break;
            case 'G':
                std::cout << termcolor::green << message << termcolor::reset << std::endl;
                break;
            case 'C':
                std::cout << termcolor::cyan << message << termcolor::reset << std::endl;
                break;
            case 'Y':
                std::cout << termcolor::yellow << message << termcolor::reset << std::endl;
                break;
            case '_':
                std::cout << termcolor::underline << message << termcolor::reset << std::endl;
                break;
            default:
                std::cout << color + message << termcolor::reset << std::endl;
        }

    }

}



// Logging function for verbose output that you might not always want
void Debug::verbose_debug(Debugging_Places p, std::string message) {
    if (Debugging_Places::VERBOSE) {
        Debug::debug(p, message);
    }
}

void Debug::translate_program_file_to_binary()
{
    std::ifstream input("../src/Program.txt");
    std::ofstream of("../src/ProgramTranslate.txt");
    std::string current_line = "";
    int line_count = 0;

    while(getline(input, current_line))
    {
        if(current_line.length() != 0) {
            line_count++;
            if (current_line.at(0) == '/')
                of << current_line << std::endl;
            else {
                current_line = current_line.substr(2, std::string::npos);
                current_line = Utility::hex_to_binary(current_line);
                of << current_line << std::endl;
            }
        }
    }
    of.close();
    input.close();
}

