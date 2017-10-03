#include <iostream>
#include "Driver.h"

int main() {
    //calls Driver to start
    std::cout << "Hello, World!" << std::endl;
    
    Driver driver = new Driver();
    driver.run();
    
    return 0;
}