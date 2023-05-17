//Sử dụng để lưu từ điển
//Xác định loại lệnh (R hay I), chuyển các mã lệnh thành binary code
//Viết thêm 1 hàm chuyển từ binary sang hex để dễ đối chiếu hơn

#include "instruction.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <map>

using namespace std;
//Lưu từ điển 
map<string, string> REG;
map<string, string> OPCODE;
map<string, string> FUNCT;
map<string, string> TYPE;

string bin_to_hex(string bin);
string binary_convert(string dec, int n);
string twoComplement(string b);

void reg_dict();
//Hàm chuyển từ nhị phân sang thập lục phân
string bin_to_hex(string bin) {
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

//Hàm chuyển từ thập phân sang nhị phân với độ dài n bit
string binary_convert(string s, int n) {
    int dec = stoi(s);
    string bin;
    bin.reserve(n); // Reserve space to avoid reallocation

    for (int i = 0; i < n; ++i) {
        bin = std::to_string(dec % 2) + bin;
        dec /= 2;
    }
    return bin;
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

//Kiểm tra xem từ có nằm trong từ điển không (nếu không là số nguyên)
bool check_in_dict(string s){
    auto it = REG.find(s);
    if (it != REG.end()) return true;
    else return false;
}

// xem thử cái này nha :v, thay cho 2 hàm format bên dưới
string assembler(vector<string> &words) {
    string format;
    if(TYPE[words[0]] == "R") {
        if(words[0] == "jr") {
            // chua biet lam
            // Hỏi thầy
        }

        else if(words[0] == "sll" || words[0] == "srl") {
            // do dịch bit không âm -> không cần xét âm dương
            string shamt = binary_convert(words[3], 5);
            format = OPCODE[words[0]] + "00000" + REG[words[2]] + REG[words[1]] + shamt + FUNCT[words[0]];
        }

        else {
            format = OPCODE[words[0]] + REG[words[2]] + REG[words[3]] + REG[words[1]] + "00000" + FUNCT[words[0]];
        }
    }

    else {
        // chua biet lam
        // m thêm phần này nha, hàm này chưa biết làm/ đặc biệt như lw/sw thì cứ chia ra if-else như trên để T6 hỏi thầy r xử lí sau
    }

    return format;
}

//Trả về dạng của type I và type R
//Input có dạng: add $s3, $s1, $s2
string format_R(string op, string s1, string s2, string s3){
    /*
        nên là:
            check op : nếu op là sll / srl thì trường shamt khác "00000", mà thay vào
                       đó là độ dời bit dịch: từ 0 - 31
                       Khi này, format = op + "00000" + s1 + s3 + shamt + funct
                          
                       Các trường hợp khác thì mới có công thức như dưới
    */
    string format = OPCODE[op] + REG[s1] + REG[s2] + REG[s3] + "00000" + FUNCT[op];
    return format;
}

//Input có dạng: addi $s3, $s1, $s2->n value
string format_I(string op, string s1, string s2, string s3){
    /*
        phải check trước s3 là số âm hay dương
        nếu s3 là số âm thì phải chuyển sang biểu diễn dạng bù 2
        nếu s3 là số dương/0 thì mới dùng công thức ở bên dưới
    */
    string format = OPCODE[op] + REG[s1] + REG[s2] + binary_convert(s3, 16);
    return format;
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
