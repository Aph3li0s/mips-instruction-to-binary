#include <bits/stdc++.h>
using namespace std;

map<string, string> REG;
map<string, string> OPCODE;
map<string, string> FUNCT;
map<string, string> TYPE;
void init();

int register_value[32] = {0};


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

//Convert to n-bit binary string
string binary_convert(string s, int n) {
    int dec = stoi(s);
    string bin;
    bin.reserve(n); // Reserve space to avoid reallocation

    for (int i = 0; i < n; ++i) {
        bin = to_string(dec % 2) + bin;
        dec /= 2;
    }

    return bin;
}

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

bool check_opcode(string s){
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
//add $s3, $s1, $s2
/*
    nên là:
        check op : nếu op là sll / srl thì trường shamt khác "00000", mà thay vào
        đó là độ dời bit dịch: từ 0 - 31
        Khi này, format = op + "00000" + s1 + s3 + shamt + funct
        Các trường hợp khác thì mới có công thức như dưới
*/
string format_R(string op, string rs, string rt, string rd, string shamt = "00000"){
    string format = OPCODE[op] + REG[rs] + REG[rt] + REG[rd] + shamt + FUNCT[op];
    return format;
}

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
    if (ins == "jr"){
        //Cái này là lệnh jump
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
//addi $s3, $s1, $s2->n value
    /*
        phải check trước s3 là số âm hay dương
        nếu s3 là số âm thì phải chuyển sang biểu diễn dạng bù 2
        nếu s3 là số dương/0 thì mới dùng công thức ở bên dưới
    */
string format_I(string op, string s1, string s2, string s3){
    string format = OPCODE[op] + REG[s1] + REG[s2] + binary_convert(s3, 16);
    return format;
}

string instruct_I(){
    return "a";
}

int main() {
    init();
    //Đọc file và xuất file
    fstream fi("../in_out/input/test2.txt");
    fstream fo("../in_out/output/test2.txt");
    string tmp;
    vector<vector<string>> lines;
    while(getline(fi, tmp)) {
        vector<string> words;
        char* c_str = new char [tmp.size() + 1];
        strcpy(c_str, tmp.c_str());
        words = restructure(c_str);
        if(!words.size()) continue;
        
        lines.push_back(words);
        // test ket qua
        for(auto &word : words) {
            cout << word << " ";
        }
        cout << endl;
        

    }
    //Lưu số dòng trong file input.txt
    size_t size = lines.size();
    cout << "Size: " << size << "\n";
    for (const auto& words : lines) {
        string output;
        //Thêm giá trị vào thanh ghi
        //register_value[17] = 30; //0011
        //register_value[18] = 5; //0101

        if (TYPE[words[0]] == "R") output = instruct_R(words[0], words[2], words[3], words[1]);
        else output = instruct_I();
        
        //Thử in giá trị thanh ghi sau khi thực hiện lệnh add
        cout << "rd register value: " <<register_value[decimal_convert(REG[words[1]])] << "\n";
        cout << "Binary address: " << output << "\n";
        cout << "binary length: " << output.length() << "\n";
        //cout << "Hex address: " << hex_convert(output) << "\n";
        // Inner loop to iterate over each inner vector
        for (const auto& j : words) {
            cout << j << " ";
        }
        cout << endl;
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

    // reg
    REG["$zero"] = "00000";
    REG["$at"] = "00001";
    REG["$v0"] = "00010";
    REG["$v1"] = "00011";
    REG["$a0"] = "00100";
    REG["$a1"] = "00101"; //5
    REG["$a2"] = "00110";
    REG["$a3"] = "00111";
    REG["$t0"] = "01000"; 
    REG["$t1"] = "01001";
    REG["$t2"] = "01010"; //10
    REG["$t3"] = "01011";
    REG["$t4"] = "01100";
    REG["$t5"] = "01101";
    REG["$t6"] = "01110";
    REG["$t7"] = "01111"; //15
    REG["$s0"] = "10000";
    REG["$s1"] = "10001";
    REG["$s2"] = "10010";
    REG["$s3"] = "10011";
    REG["$s4"] = "10100"; //20
    REG["$s5"] = "10101";
    REG["$s6"] = "10110";
    REG["$s7"] = "10111";
    REG["$t8"] = "11000";
    REG["$t9"] = "11001"; //25
    REG["$k0"] = "11010";
    REG["$k1"] = "11011";
    REG["$gp"] = "11100";
    REG["$sp"] = "11101";
    REG["$fp"] = "11110";
    REG["$ra"] = "11111"; //31
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

