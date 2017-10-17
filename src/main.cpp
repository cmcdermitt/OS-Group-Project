#include <iostream>
#include "Utility.h"
#include "Driver.h"

int main() {
    //calls Driver to start
	//std::cout << Utility::convertHexToDecimal("ABCDEF");
    //Driver *driver = new Driver();
    //driver->run();
    //driver->test();
	// system("pause");

    std::cout << Utility::convert_decimal_to_hex(16) << std::endl;
    std::cout << Utility::convert_decimal_to_hex(123) << std::endl;
    std::cout << Utility::convert_decimal_to_hex(1230432) << std::endl;
    std::cout << Utility::convert_decimal_to_hex(4) << std::endl;
	
}
