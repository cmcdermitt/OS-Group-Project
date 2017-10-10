#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include<string>
namespace Utility
{

	// Hex to Binary
	std::string HexToBinary(std::string hexinput); //converts Hex values to 32-bit binary long
	std::string convertHexCharToBinary(char hex);

	// Hex to Decimal
	int convertHexToDecimal(std::string hexInput);
	int convertIndividualHexToDecimal(char hexChar);


	// Binary to Hex
	std::string BinaryToHex (std::string binaryinput);
	char convertFourBitsToHexChar(std::string binary);

	// Binary to Decimal
	int convertBinaryToDecimal(std::string binaryInput);

	// Decimal to Binary

	// Decimal to Hex

	// String to decimal
	};

#endif // UTILITY_H_INCLUDED
