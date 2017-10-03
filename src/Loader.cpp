//
// Created by Eshin Griffith on 9/26/17.
//

#include "Loader.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

    Loader::Loader(){

    }

    void Loader::init (Disk *disk_to_load) {
        std::ifstream input(CODEFILENAME);
        std::string temp;
        int currentPosition = 0;
        while(getline(input, temp))
        {
            // If the line is PCB Data

            // Else it is hexcode

        }
    }
        //logic for actually reading file goes here










