#include 'Utility.h'
#include <bitset>
#include <string>

class Utility
{
  string HexToBinary(int hexinput)
  {
    string s = hex;
    stringstream ss;
    ss << hex << s;
    unsigned n;
    ss >> n;
    bitset<32> b(n);
    return b.to_string();
  }
  int BinaryToHex (string binaryinput)
  {
    for(size_t i = 0; i < (binaryinput.size() - 1); i++)
    {
      string binToHex, tmp = "0000";
      for (size_t j = 0; j < binaryinput[i].size(); j += 4)
      {
        tmp = binaryinput[i].substr(j, 4);
        if      (!tmp.compare("0000")) binToHex += "0";
        else if (!tmp.compare("0001")) binToHex += "1";
        else if (!tmp.compare("0010")) binToHex += "2";
        else if (!tmp.compare("0011")) binToHex += "3";
        else if (!tmp.compare("0100")) binToHex += "4";
        else if (!tmp.compare("0101")) binToHex += "5";
        else if (!tmp.compare("0110")) binToHex += "6";
        else if (!tmp.compare("0111")) binToHex += "7";
        else if (!tmp.compare("1000")) binToHex += "8";
        else if (!tmp.compare("1001")) binToHex += "9";
        else if (!tmp.compare("1010")) binToHex += "A";
        else if (!tmp.compare("1011")) binToHex += "B";
        else if (!tmp.compare("1100")) binToHex += "C";
        else if (!tmp.compare("1101")) binToHex += "D";
        else if (!tmp.compare("1110")) binToHex += "E";
        else if (!tmp.compare("1111")) binToHex += "F";
        else continue;
      }
    hexOStr << binToHex;
    hexOStr << " ";
   }
   return hexOStr;
  }
}
