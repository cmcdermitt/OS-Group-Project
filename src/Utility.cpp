#include "Utility.h"
#include <bitset>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
// ******** NOT TESTED ************
	// Hex to Binary
	// Converts hex to binary

	std::string Utility::HexToBinary(std::string hexinput)
	{
		char temp; // Temporry character
		std::string binaryVersion = "";

		for (int i = 0; i < 8; i++)
		{
			binaryVersion = binaryVersion + convertHexCharToBinary(hexinput.at(i));
		}
		return binaryVersion;
	}


	// Converts individual hex to binary
	std::string Utility::convertHexCharToBinary(char hex)
	{
		switch (hex)
		{
		case '0':
			return "0000";
			break;
		case '1':
			return "0001";
		case '2':
			return "0010";
		case '3':
			return "0011";
		case '4':
			return "0100";
		case '5':
			return "0101";
		case '6':
			return "0110";
		case '7':
			return "0111";
		case '8':
			return "1000";
		case '9':
			return "1001";
		case 'A':
			return "1010";
		case 'B':
			return "1011";
		case 'C':
			return "1100";
		case 'D':
			return "1101";
		case 'E':
			return "1110";
		case 'F':
			return "1111";
		}
	}


	// Hex to Decimal
	int Utility::convertIndividualHexToDecimal(char hex)
	{
		switch (hex)
		{
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case 'A':
			return 10;
		case 'B':
			return 11;
		case 'C':
			return 12;
		case 'D':
			return 13;
		case 'E':
			return 14;
		case 'F':
			return 15;
		}
		}

	int Utility::convertHexToDecimal(std::string hexInput)
	{
		int it = hexInput.length() - 1;
		int place = 0;
		int final = 0;
		while (it != 0)
		{
			final += pow(16, place) * convertIndividualHexToDecimal(hexInput.at(it));
			place++;
			--it;

		}

		final += pow(16, place) * convertIndividualHexToDecimal(hexInput.at(0));
		return final;
	}

	// Binary to Hex

	// Converts Binary to hex
	std::string Utility::BinaryToHex(std::string binaryinput)
	{
		std::string hexVersion = "";

		for (int i = 0; i <= binaryinput.length(); i = i + 4)
		{
			hexVersion += binaryinput.substr(i, 4);
		}
		return hexVersion;
	}

	// Converts individual bits to a hex Char
	char Utility::convertFourBitsToHexChar(std::string binary)
	{
		int decimal = convertBinaryToDecimal(binary);
		switch (decimal)
		{
		case 0:
			return '0';
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '7';
		case 8:
			return '8';
		case 9:
			return '9';
		case 10:
			return 'A';
		case 11:
			return 'B';
		case 12:
			return 'C';
		case 13:
			return 'D';
		case 14:
			return 'E';
		case 15:
			return 'F';
		}
	}

	// Converts Binary to decimal
	int Utility::convertBinaryToDecimal(std::string binaryInput)
	{
		int decimal = 0;
		int place = 1;
		for (int i = 0; i < binaryInput.length(); i++)
		{
			if (binaryInput.at(i) == '1')
				decimal += place;
			place *= 2;
		}
		return decimal;
	}




