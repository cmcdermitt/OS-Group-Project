#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include<string>
class Utility
{
  public:
	std::string HexToBinary(std::string hexinput); //converts Hex values to 32-bit binary long
    std::string BinaryToHex (std::string binaryinput);
	std::string convertHexCharToBinary(char hex);
	char convertFourBitsToHexChar(std::string binary);
	int convertBinaryToDecimal(std::string binaryInput);
};

#endif // UTILITY_H_INCLUDED
