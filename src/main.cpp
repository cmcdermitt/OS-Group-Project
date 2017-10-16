#include <iostream>
#include "Utility.h"
#include "Driver.h"

int main() {
    //calls Driver to start
	//std::cout << Utility::convertHexToDecimal("ABCDEF");
    Driver *driver = new Driver();
    driver->run();
   driver->test();
	// system("pause"); 
	
}
