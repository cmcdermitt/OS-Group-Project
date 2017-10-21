//
// Created by Charlie on 10/18/17.
//

#include "Utility.h"
#include <bitset>
#include <iostream>
#include <cmath>

// Converts HEX to Binary
std::string Utility::hex_to_binary(std::string hexinput) {
    char temp; // Temporry character
    std::string binaryVersion = "";

    for (int i = 0; i < hexinput.length(); i++) {
        binaryVersion = binaryVersion + hex_char_to_binary(hexinput.at(i));
    }
    return binaryVersion;
}

// Converts individual HEX chars to Binary
std::string Utility::hex_char_to_binary(char hex) {
    switch (hex) {
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
int Utility::hex_char_to_decimal(char hex) {
    switch (hex) {
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

// HEX to Decimal from string input
int Utility::hex_to_decimal(std::string hexInput) {
    int i = hexInput.length() - 1;
    int place = 0;
    int final = 0;
    while (i >= 0) {
        final += pow(16, place) * hex_char_to_decimal(hexInput.at(i));
        place++;
        --i;
    }

    return final;
}

// Converts Binary to HEX
std::string Utility::binary_to_hex(std::string binaryinput) {
    std::string hexVersion = "";

    while(binaryinput.length()%4!=0)binaryinput = '0' + binaryinput;
    for (int i = 0; i < binaryinput.length(); i = i + 4) {
        hexVersion += four_bits_to_hex(binaryinput.substr(i, 4));
    }
    return hexVersion;
}

// Converts individual bits to a HEX Char
char Utility::four_bits_to_hex(std::string binary) {
    int decimal = binary_to_decimal(binary);
    switch (decimal) {
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
int Utility::binary_to_decimal(std::string binaryInput) {
    int decimal = 0;
    for (int i = 0; i < binaryInput.length(); ++i) {
        decimal*=2;
        decimal+=(binaryInput.at(i)=='0')?0:1;
    }
    return decimal;
}

// Converts Decimal to HEX
std::string Utility::decimal_to_hex(int input) {
    std::string output = "";
    int temp;
    char next;

    while (input != 0) {
        temp = input % 16;
        switch (temp) {
            case 0:
                next = '0';
                break;
            case 1:
                next = '1';
                break;
            case 2:
                next = '2';
                break;
            case 3:
                next = '3';
                break;
            case 4:
                next = '4';
                break;
            case 5:
                next = '5';
                break;
            case 6:
                next = '6';
                break;
            case 7:
                next = '7';
                break;
            case 8:
                next = '8';
                break;
            case 9:
                next = '9';
                break;
            case 10:
                next = 'A';
                break;
            case 11:
                next = 'B';
                break;
            case 12:
                next = 'C';
                break;
            case 13:
                next = 'D';
                break;
            case 14:
                next = 'E';
                break;
            case 15:
                next = 'F';
                break;
        }
        input = input / 16;

        output = next + output;
    }

    while (output.length() < 8) {
        output = "0" + output;
    }

    return output;
}

std::string Utility::bool_to_string(bool s) {
    if(s)
        return "True";
    else
        return "False";
}



