//
// Created by Eshin Griffith on 9/26/17.
//

#include "Loader.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Utility.h"

    Loader::Loader(){

    }

    void Loader::init (Disk *disk_to_load, std::list<PCB> *pcbs) {
        std::ifstream input(CODEFILENAME);
        std::string temp;
        int currentPosition = 0;
		int tempPosition;
        while(getline(input, temp))
        {
            
			// If the line is PCB Data
			if (temp.at(0) == '/')
			{
				if (temp.at(3) == 'J')
				{
					pcbs->push_back(PCB());
					temp = temp.substr(7, std::string::npos); 
					tempPosition = temp.find(" "); 
					


				}

				else
				{

				}

			}

			else
			{
				
			}
            // Else it is hexcode

        }
    }
        //logic for actually reading file goes here










