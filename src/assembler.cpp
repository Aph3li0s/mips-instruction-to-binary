#include <bits/stdc++.h>
using namespace std;

map<string, string> REG;
map<string, string> OPCODE;
map<string, string> FUNCT;

void init();
vector<string> restructure(char code[255]);

int main() {
    init();
    fstream fi("../testcases/input.txt");
    fstream fo("../output/output.txt");
    string tmp;
    while(getline(fi, tmp)) {
        vector<string> words;
        char* c_str = new char [tmp.size() + 1];
        strcpy(c_str, tmp.c_str());
        words = restructure(c_str);
      
        // test ket qua
        for(auto &word : words) {
            cout << word << " ";
        }
        cout << endl;
        
        // test chuyen doi, vi du sub $t3 $t1 $t2
        // cout << OPCODE[words[0]] << REG[words[2]] << REG[words[3]] << REG[words[1]] << "00000" << FUNCT[words[0]];
        // -> can viet if/else de xu li tung cau lenh giong nhu tren ...
        // 00000001001010100101100000100010 -> dung
        
    }
}

void init() {
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

    // OPCODE
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

    // FUNCT
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

// Xoa comments, spaces, commas, .data, .text
// Tra ve vector
vector<string> restructure(char code[255]) {
    vector<string> _;
    auto k = strtok(code, " ,\t");
    while(k != NULL) {
        if(*k == '#') break;
        if(*k != '.') {
            std::string str(k);
            _.push_back(k);
        }
        k = strtok(NULL, " ,\t");
    }
    return _;
}
