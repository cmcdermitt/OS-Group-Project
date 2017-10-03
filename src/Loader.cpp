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
        while(getline(input, temp));
    }
        //logic for actually reading file goes here










