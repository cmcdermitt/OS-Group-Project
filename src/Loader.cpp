//
// Created by Eshin Griffith on 9/26/17.
//

#include "Loader.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Utility.h"
#include <string>

    Loader::Loader(){

    }

    void Loader::init (Disk *disk_to_load, std::list<PCB> *pcbs) {
        int data[10];
        std::ifstream input(CODEFILENAME);
        std::string temp;
        std::string store;
        std::string buildString = "";
        int counter = 0;
        int currentPosition = 0;
		int tempPosition;
		int lines = 0;
		PCB *p = new PCB();
        while(getline(input, temp))
{       lines++;
        buildString = "";

			// If the line is PCB Data
			if(temp.length()  == 0)
                break; // :D
			if (temp.at(0) == '/' && temp != "// END" && temp != "//END")
			{
				if (temp.at(3) == 'J')
				{

					p = new PCB();
                    p->job_disk_address = currentPosition;
					temp = temp.substr(7, std::string::npos);

					for(int i = 0; i < temp.length(); i++)
                    {
                        if(temp.at(i) != ' ')
                            buildString += temp.at(i);
                        else
                            {
                                if(buildString.length() != 0)
                                {
                            data[counter] = Utility::convertHexToDecimal(buildString);
                            counter++;
                            buildString = "";
                                }
                    }
				}
				}

			else
			{
			    int innerIterations = 0;

             temp = temp.substr(8, std::string::npos);

             for(int i = 0; i < temp.length(); i++)
                    {
                        innerIterations++;

                        if(temp.at(i) != ' ')
                            buildString += temp.at(i);
                        else
                            {

                                {
                            data[counter] = Utility::convertHexToDecimal(buildString);
                            counter++;
                            buildString = "";
                                }
                    }
				}
				p->job_id = data[0];
				p->job_size = data[1];
				p->job_pri = data[2];
				p->in_buf_size = data[3];
				p->out_buf_size = data[4];
				p->temp_buf_size = data[5];
                p->total_size = p->job_size + p->in_buf_size + p->out_buf_size + p->temp_buf_size;
                pcbs->push_back(*p);
                counter = 0;
				}
				}
            else if(temp.at(0) != '/')
            {
                temp = temp.substr(2, std::string::npos);
                disk_to_load->write(currentPosition, temp);
                currentPosition++;
            }



        }

    }










