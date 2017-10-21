//
// Created by Eshin Griffith on 9/26/17.
//

#include "Loader.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Utility.h"
#include "Log.h"

    Loader::Loader(){
    }

    void Loader::init (Disk &disk_to_load, std::list<PCB*> &pcbs) {
		l = new Log("init"); 
		l->turnOn();

        //Variables
		int data[10];
        std::ifstream input("../src/Program.txt");
        std::string temp;
        std::string store;
        std::string build_string = "";
        int counter = 0;
        int current_position = 0;
		int lines = 0;
		PCB *p = new PCB();

		// Read the file 
        while(getline(input, temp)) {
            lines++;
            build_string = "";

			if(temp.length()  == 0)// If the line is PCB Data
                break;
			if (temp.at(0) == '/' && temp != "// END" && temp != "//END") {
				if (temp.at(3) == 'J')// Do this if the line is a PCB Job line
				{
                    //create a new PCB with registers, and address initialized
					p = new PCB();
                    for (int &j : p->registers) {
                        j =-1;
                    }
                    p->job_disk_address = current_position;

					temp = temp.substr(7, std::string::npos); //drop the characters before index 7

                    //Store the values from the line in data
					for(int i = 0; i < temp.length(); i++) {
                        if(temp.at(i) != ' ')
                            build_string += temp.at(i);
                        else {
                            if(build_string.length() != 0) {
                                data[counter] = Utility::hex_to_decimal(build_string);
                                counter++;
                                build_string = "";
                            }
                        }
				    }

                    // Last build string must be added
                    data[counter] = Utility::hex_to_decimal(build_string);
                    counter++;
                    build_string = "";

                } else { //if the line is a data buffer info line ?
			        int innerIterations = 0;

                    temp = temp.substr(8, std::string::npos);

                    //Store the values from the line in data
                    for(int i = 0; i < temp.length(); i++) {
                            innerIterations++;

                            if(temp.at(i) != ' ')
                                build_string += temp.at(i);
                            else {
                                // Last buildstring must be added
                                data[counter] = Utility::hex_to_decimal(build_string);
                                counter++;
                                build_string = "";
                            }
				    }

                data[counter] = Utility::hex_to_decimal(build_string);
                counter++;
                build_string = "";

			    // Once a PCB Data Line is recorded, store that into the PCB
				p->job_id = data[0];
				p->job_size = data[1];
				p->job_pri = data[2];
				p->in_buf_size = data[3];
				p->out_buf_size = data[4];
				p->temp_buf_size = data[5];
                p->total_size = p->job_size + p->in_buf_size + p->out_buf_size + p->temp_buf_size;
                p->state = PCB::PROCESS_STATUS::NEW;
                p->wait_time = new Log("Wait Time for " + std::to_string(p->job_id));
                p->comp_time = new Log("Completion Time for " + std::to_string(p->job_id));
                p->wait_time->turnOn();
                pcbs.push_back(p);
                counter = 0;
				}
            }
			// If the data is just raw hexcode, strip off the first few characters and store it as a string
			else if(temp.at(0) != '/') {
                temp = temp.substr(2, std::string::npos);
                disk_to_load.write(current_position, temp);
                current_position++;
            }
        }

		input.close();
		l->turnOff();
		delete l;
    }










