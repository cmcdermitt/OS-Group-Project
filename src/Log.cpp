#include "Log.h"
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "termcolor.hpp"

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
    graphs = std::vector<Graph>();
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
    log.open("LogFile" + std::to_string(time(0)) + ".txt");
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
        graph_string += graphs[i].label + ":\t";
        for (int j = 0; j < graphs[i].points.size(); j++) {
            graph_string +=
                    "(" + std::to_string(graphs[i].points[j].x) + "," + std::to_string(graphs[i].points[j].y) + "),";
        }
        graph_string.erase(graph_string.end());

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
    g->points = std::vector<Point>();
    g->origin = time(0);
    graphs.push_back(*g);
    return true;
}

bool Log::add_point(std::string label, int y_coord) {
    for (Graph g : graphs) {
        if (g.label == label) {
            Point *p = new Point();
            p->x = time(0) - g.origin;
            p->y = y_coord;
            g.points.push_back(*p);
            return true;
        }

    }
    return false;
}

bool Log::remove_graph(std::string label) {
    for (int i = 0; i < graphs.size(); i++) {
        if (label == graphs[i].label) {
            graphs.erase(graphs.begin() + i);
            return true;
        }

    }
    return false;
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
            case 'B':
                std::cout << termcolor::blue << message << termcolor::reset << std::endl;
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