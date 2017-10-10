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
        int data[6];
        std::ifstream input(CODEFILENAME);
        std::string temp;
        std::string buildString = "";
        int counter = 0;
        int currentPosition = 0;
		int tempPosition;
		PCB p = PCB();
        while(getline(input, temp))
{
			// If the line is PCB Data
			if (temp.at(0) == '/')
			{
				if (temp.at(3) == 'J')
				{
					p = PCB();
                    p.jobDiskAddress = currentPosition + 1;
					temp = temp.substr(7, std::string::npos);
					for(int i = 0; i < temp.length(); i++)
                    {
                        if(temp.at(i) != ' ')
                            buildString += temp.at(i);
                        else
                            {
                                if(buildString.at(i) != ' ' && buildString.length() != 0)
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
             temp = temp.substr(8, std::string::npos);
             for(int i = 0; i < temp.length(); i++)
                    {
                        if(temp.at(i) != ' ')
                            buildString += temp.at(i);
                        else
                            {
                                if(buildString.at(i) != ' ' && buildString.length() != 0)
                                {
                            data[counter] = Utility::convertHexToDecimal(buildString);
                            counter++;
                            buildString = "";
                                }
                    }
				}
				}

			}


        }
    }
        //logic for actually reading file goes here










