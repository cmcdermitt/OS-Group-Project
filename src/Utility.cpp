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
}
