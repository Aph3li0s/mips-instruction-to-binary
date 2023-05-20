#ifndef INSTRUCTION
#define INSTRUCTION

#include <bits/stdc++.h>

extern int register_value[32];
extern std::map<std::string, std::string> REG;
extern std::map<std::string, std::string> OPCODE;
extern std::map<std::string, std::string> FUNCT;
extern std::map<std::string, std::string> TYPE;

std::string hex_convert(std::string bin);
std::string binary_convert(std::string s, int n);
int decimal_convert(std::string& binary);
std::string twoComplement(std::string b);
bool check_opcode(std::string s);
bool check_rt(std::string s);
bool check_in_dict(std::string s);
std::string format_R(std::string op, std::string rs, std::string rt, std::string rd, std::string shamt);
std::string instruct_R(std::string op, std::string rs, std::string rt, std::string rd);
std::string instruct_I(std::vector<std::string> &words, int PC, std::map<std::string, int> labelsAddress);

void reg_dict();

#endif // INSTRUCTION
