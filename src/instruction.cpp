#include "instruction.h"
#include <bits/stdc++.h>
using namespace std;

//Mapping các giá trị thanh ghi, opcode, function và type (R và I) 
map<string, string> REG;
map<string, string> OPCODE;
map<string, string> FUNCT;
map<string, string> TYPE;

//Mảng để lưu giá trị thanh ghi dưới dạng int
int register_value[32] = {0};

string hex_convert(string bin);
string binary_convert(string s, int n);
int decimal_convert(string& binary);
string twoComplement(string b);
bool check_opcode(string s);
bool check_rt(string s);
string instruct_I(vector<string> &words);                           // Sao hàm này không có khai báo bên dưới nè

string format_R(string op, string rs, string rt, string rd, string shamt);
string instruct_R(string op, string rs, string rt, string rd);
// string format_I(string op, string s1, string s2, string s3);  // Tạm thời không đi theo hướng này
// string instruct_I(string op, string s1, string s2, string s3); // Chuyển thành hàm dưới
string instruct_I(vector<string> &words);

void reg_dict();


//Hàm chuyển nhị phân sang thập lục phân
string hex_convert(string bin) {
    string hex = "0x";
    for(int i = 0; i < bin.size(); i+=4) {
        int v = (bin[i] - '0') * 8 + (bin[i + 1] - '0') * 4 + (bin[i + 2] - '0') * 2 + (bin[i + 3] - '0') * 1;
        if(v < 10) hex = hex + to_string(v);
        else if(v == 10) hex = hex + 'a';
        else if(v == 11) hex = hex + 'b';
        else if(v == 12) hex = hex + 'c';
        else if(v == 13) hex = hex + 'd';
        else if(v == 14) hex = hex + 'e';
        else hex = hex + 'f';
    }
    return hex;
}

//Hàm chuyển thập phân sang nhị phân với n bit
string binary_convert(string s, int n) {
    int dec = stoi(s);
    string bin;
    bin.reserve(n); 
    for (int i = 0; i < n; ++i) {
        bin = to_string(dec % 2) + bin;
        dec /= 2;
    }
    return bin;
}

//Hàm chuyển nhị phân sang thập phân (int)
int decimal_convert(string& binary) {
    int decimal = 0, power = 0;
    for (int i = binary.length() - 1; i >= 0; --i) {
        if (binary[i] == '1') {
            decimal += pow(2, power);
        }
        ++power;
    }
    return decimal;
}

//Hàm chuyển bù 2
string twoComplement(string b) {
    bool found1 = false;
    string b2 = "";
    int id = b.size() - 1;
    while(id > -1) {
        if(found1 == false) {
            b2 = b[id] + b2;
            if(b[id] == '1') found1 = true;
        }
        else {
            if(b[id] == '0') b2 = '1' + b2;
            if(b[id] == '1') b2 = '0' + b2;
        }
        id--;
    }
    return b2;
}

//Các hàm check xem opcode và thanh ghi có trong map hay ko
bool check_opcode(string s){
    //Kiểm tra xem từ s có trong OPCODE ko
    auto it = OPCODE.find(s);
    if (it != OPCODE.end()){
        return true;
    }
    else return false;
}

bool check_rt(string s){
    auto it = REG.find(s);
    if (it != REG.end()){
        return true;
    }
    else return false;
}

//Format của lệnh R
string format_R(string op, string rs, string rt, string rd, string shamt = "00000"){
    string format = OPCODE[op] + REG[rs] + REG[rt] + REG[rd] + shamt + FUNCT[op];
    return format;
}

//Instruction cho lệnh R
string instruct_R(string op, string rs, string rt, string rd){
    string ins;
    if (check_opcode(op) == true) ins = op;
    if (check_rt(rt) == false){
        if (ins == "sll"){
            register_value[decimal_convert(REG[rd])] = 
            register_value[decimal_convert(REG[rs])] << stoi(rt);
            string shamt = binary_convert(rt, 5);
            return format_R(op, "$zero", rs, rd, shamt);
        }
        if (ins == "srl"){
            register_value[decimal_convert(REG[rd])] = 
            register_value[decimal_convert(REG[rs])] >> stoi(rt);
            string shamt = binary_convert(rt, 5);
            return format_R(op, "$zero", rs, rd, shamt);
        }
    }
    if (ins == "add" || ins == "addu") {
        register_value[decimal_convert(REG[rd])] = register_value[decimal_convert(REG[rs])] + register_value[decimal_convert(REG[rt])];
    }
    if (ins == "and"){
        register_value[decimal_convert(REG[rd])] = register_value[decimal_convert(REG[rs])] & register_value[decimal_convert(REG[rt])];
    }
    if (ins == "nor"){
        register_value[decimal_convert(REG[rd])] = !(register_value[decimal_convert(REG[rs])] || register_value[decimal_convert(REG[rt])]);
    }
    if (ins == "or"){
        register_value[decimal_convert(REG[rd])] = register_value[decimal_convert(REG[rs])] || register_value[decimal_convert(REG[rt])];
    }
    if (ins == "slt"){
        (register_value[decimal_convert(REG[rs])] < register_value[decimal_convert(REG[rt])]) ?
        register_value[decimal_convert(REG[rd])] = 1 : register_value[decimal_convert(REG[rd])] = 0;

    }
    if (ins == "sltu"){
        abs(register_value[decimal_convert(REG[rs])]) < abs(register_value[decimal_convert(REG[rt])]) ?
        register_value[decimal_convert(REG[rd])] = 1 : register_value[decimal_convert(REG[rd])] = 0;
    }
    if (ins == "sub" || ins == "subu"){
        register_value[decimal_convert(REG[rd])] = register_value[decimal_convert(REG[rs])] - register_value[decimal_convert(REG[rt])];
    }

    return format_R(op, rs, rt, rd);
}

// tam thoi bo?
// string format_I(string op, string s1, string s2, string s3){
//     string format = OPCODE[op] + REG[s1] + REG[s2] + binary_convert(s3, 16);
//     return format;
// }

string instruct_I(vector<string> &words){
    string ins;
    if (check_opcode(words[0]) == true) ins = words[0];
    if(ins == "beq" || ins == "bne") {
        // chua biet lam
        return "a";
    }

    if(ins == "lw" || ins == "sw") {
        // op: words[0], rt = words[1], imme = words[2], rs = words[3]
        string opcode, rs, rt, immediate;
        opcode = OPCODE[words[0]]; rs = REG[words[3]]; rt = REG[words[1]]; immediate = words[2];
        if(stoi(immediate) < 0) {
            auto immediate16Bit = binary_convert(to_string(abs(stoi(immediate))), 16);
            auto twoComplementImmediate16Bit = twoComplement(immediate16Bit);
            return opcode + rs + rt + twoComplementImmediate16Bit;
        }
        else {
            auto immediate16Bit = binary_convert(immediate, 16);
            return opcode + rs + rt + immediate16Bit;
        }
    }

    if(ins == "lb" || ins == "sb") {
        // chua biet lam
        return "a";
    }

    if(ins == "addi" || ins == "addiu" || ins == "andi" || ins == "ori") {
        string opcode, rs, rt, immediate;
        opcode = OPCODE[words[0]]; rs = REG[words[2]]; rt = REG[words[1]]; immediate = words[3];
        if (ins == "addi" || "addiu"){
            register_value[decimal_convert(REG[rs])] = register_value[decimal_convert(REG[rt])] + stoi(words[3]);
        }
        if (ins == "andi"){
            register_value[decimal_convert(REG[rs])] = register_value[decimal_convert(REG[rt])] & stoi(words[3]);
        }
        if (ins == "ori"){
            register_value[decimal_convert(REG[rs])] = register_value[decimal_convert(REG[rt])] || stoi(words[3]);
        }
        if(stoi(immediate) < 0) {
            auto immediate16Bit = binary_convert(to_string(abs(stoi(immediate))), 16);
            auto twoComplementImmediate16Bit = twoComplement(immediate16Bit);
            return opcode + rs + rt + twoComplementImmediate16Bit;
        }

        else {
            auto immediate16Bit = binary_convert(immediate, 16);
            return opcode + rs + rt + immediate16Bit;
        }
    }
    //Nhớ return string về, nó báo lỗi:v
    return "a";
}

//Từ điển của MIPS
void reg_dict() {
    // type R
    TYPE["add"] = "R";
    TYPE["addu"] = "R";
    TYPE["and"] = "R";
    TYPE["jr"] = "R";
    TYPE["nor"] = "R";
    TYPE["or"] = "R";
    TYPE["slt"] = "R";
    TYPE["sltu"] = "R";
    TYPE["sll"] = "R";
    TYPE["srl"] = "R";
    TYPE["sub"] = "R";
    TYPE["subu"] = "R";

    // type I
    TYPE["addi"] = "I";
    TYPE["addiu"] = "I";
    TYPE["andi"] = "I";
    TYPE["beq"] = "I";
    TYPE["bne"] = "I";
    TYPE["lb"] = "I";
    TYPE["lw"] = "I";
    TYPE["ori"] = "I";
    TYPE["sb"] = "I";
    TYPE["sw"] = "I";

    // reg
    REG["$zero"] = "00000";
    REG["$at"] = "00001";
    REG["$v0"] = "00010";
    REG["$v1"] = "00011";
    REG["$a0"] = "00100";
    REG["$a1"] = "00101";
    REG["$a2"] = "00110";
    REG["$a3"] = "00111";
    REG["$t0"] = "01000";
    REG["$t1"] = "01001";
    REG["$t2"] = "01010";
    REG["$t3"] = "01011";
    REG["$t4"] = "01100";
    REG["$t5"] = "01101";
    REG["$t6"] = "01110";
    REG["$t7"] = "01111";
    REG["$s0"] = "10000";
    REG["$s1"] = "10001";
    REG["$s2"] = "10010";
    REG["$s3"] = "10011";
    REG["$s4"] = "10100";
    REG["$s5"] = "10101";
    REG["$s6"] = "10110";
    REG["$s7"] = "10111";
    REG["$t8"] = "11000";
    REG["$t9"] = "11001";
    REG["$k0"] = "11010";
    REG["$k1"] = "11011";
    REG["$gp"] = "11100";
    REG["$sp"] = "11101";
    REG["$fp"] = "11110";
    REG["$ra"] = "11111";

    // OPCODE for R ins
    OPCODE["add"] = "000000";
    OPCODE["addu"] = "000000";
    OPCODE["and"] = "000000";
    OPCODE["jr"] = "000000";
    OPCODE["nor"] = "000000";
    OPCODE["or"] = "000000";
    OPCODE["slt"] = "000000";
    OPCODE["sltu"] = "000000";
    OPCODE["sll"] = "000000";
    OPCODE["srl"] = "000000";
    OPCODE["sub"] = "000000";
    OPCODE["subu"] = "000000";

    // OPCODE for I ins
    OPCODE["addi"] = "001000";
    OPCODE["addiu"] = "001001";
    OPCODE["andi"] = "001100";
    OPCODE["beq"] = "000100";
    OPCODE["bne"] = "000101";
    OPCODE["lb"] = "100000";
    OPCODE["lw"] = "100011";
    OPCODE["ori"] = "001101";
    OPCODE["sb"] = "101000";
    OPCODE["sw"] = "101011";

    // FUNCT for R ins - I ins do not have FUNCT
    FUNCT["add"] = "100000";
    FUNCT["addu"] = "100001";
    FUNCT["and"] = "100100";
    FUNCT["jr"] = "001000";
    FUNCT["nor"] = "100111";
    FUNCT["or"] = "100101";
    FUNCT["slt"] = "101010";
    FUNCT["sltu"] = "101011";
    FUNCT["sll"] = "000000";
    FUNCT["srl"] = "000010";
    FUNCT["sub"] = "100010";
    FUNCT["subu"] = "100011";
}
//int main(){}
