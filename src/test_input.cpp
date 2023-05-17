#include <bits/stdc++.h>
using namespace std;

map<string, string> REG;
map<string, string> OPCODE;
map<string, string> FUNCT;
map<string, string> TYPE;
void init();
vector<string> restructure(char code[255]);

int register_value[32];


string binaryToHex(string bin) {
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

//Convert to n-bit binary string
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

bool check_in_dict(string s){
    auto it = REG.find(s);
    if (it != REG.end()){
        return true;
    }
    else return false;
}

//add $s3, $s1, $s2
string format_R(string op, string s1, string s2, string s3){
    string format = OPCODE[op] + REG[s1] + REG[s2] + REG[s3] + "00000" + FUNCT[op];
    return format;
}

//addi $s3, $s1, $s2->n value
string format_I(string op, string s1, string s2, string s3){
    string format = OPCODE[op] + REG[s1] + REG[s2] + binary_convert(s3, 16);
    return format;
}

int main() {
    init();
    for (auto& i : register_value) i = 0;
    //Đọc file và xuất file
    fstream fi("../in_out/input/test1.txt");
    fstream fo("../in_out/output.txt");
    string tmp;
    
    while(getline(fi, tmp)) {
        vector<string> words;
        char* c_str = new char [tmp.size() + 1];
        strcpy(c_str, tmp.c_str());
        words = restructure(c_str);
        if(!words.size()) continue;
        
        // test ket qua
        for(auto &word : words) {
            cout << word << " ";
        }
        cout << endl;
        string output;
        if (check_in_dict(words[3]) == true){
            output = format_R(words[0], words[2], words[3], words[1]);
        }  else output = format_I("addi", words[2], words[1], words[3]);
        cout << binaryToHex(output)<< "\n";
    }
}
//add $s3, $s1, $s2


void init() {
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
    // REG["$zero"] = "1";
    // REG["$at"] = "2";
    // REG["$v0"] = "3";
    // REG["$v1"] = "4";
    // REG["$a0"] = "5";
    // REG["$a1"] = "6";
    // REG["$a2"] = "7";
    // REG["$a3"] = "8";
    // REG["$t0"] = "9";
    // REG["$t1"] = "10";
    // REG["$t2"] = "11";
    // REG["$t3"] = "12";
    // REG["$t4"] = "13";
    // REG["$t5"] = "14";
    // REG["$t6"] = "15";
    // REG["$t7"] = "16";
    // REG["$s0"] = "17";
    // REG["$s1"] = "18";
    // REG["$s2"] = "19";
    // REG["$s3"] = "20";
    // REG["$s4"] = "21";
    // REG["$s5"] = "22";
    // REG["$s6"] = "23";
    // REG["$s7"] = "24";
    // REG["$t8"] = "25";
    // REG["$t9"] = "26";
    // REG["$k0"] = "27";
    // REG["$k1"] = "28";
    // REG["$gp"] = "29";
    // REG["$sp"] = "30";
    // REG["$fp"] = "31";
    // REG["$ra"] = "32";

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
