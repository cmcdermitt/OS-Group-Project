//
// Created by Eshin Griffith on 9/26/17.
//

#include "Driver.h"
#include "Disk.h"
#include "Loader.h"

class Driver{
    
    Driver(){
        Disk disk = Disk();
        Loader loader = loader();
    }
    
    void run() {
        loader.init(&disk); 
        
        
    }
    
    
    
}