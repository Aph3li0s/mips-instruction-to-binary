#include <bits/stdc++.h>
#include "instruction.h"
using namespace std;
string in; 
// Xóa các cmt, kí tự dư thừa, tokenize các từ và quăng vào vector
//Nghĩ thêm được test nào chứa các ngoại lệ thì thêm vào
vector<string> restructure(char code[255]) {
    vector<string> formatted_str;
    auto k = strtok(code, " ,\t():");
    while(k != NULL) {
        if(*k == '#') break;
        if(*k != '.') {
            std::string str(k);
            formatted_str.push_back(k);
        }
        k = strtok(NULL, " ,\t():");
    }
    return formatted_str;
}

void txt_convert(){
    ifstream fin("../in_out/testcases/" + in + ".asm");
    ofstream fout("../in_out/input/" + in + ".txt", ios_base::trunc);
    if (!fin) cout << "Can't open file";

    string str_read;
    while (getline(fin, str_read)) {
        fout << str_read;
        fout << "\n";
    }
    fin.close();
    fout.close();
}

vector<pair<int, vector<string>>> lines;
map<string, int> labelsAddress;
int PC = 0;

void read_txt(){
    ifstream fin("../in_out/input/" + in + ".txt");
    ofstream fout("../in_out/output/" + in + ".txt", ios_base::trunc);
    if (!fin) cout << "Can't open file";
    string str_read;

    while (getline(fin, str_read)){
        vector<string> words;
        char* c_str = new char [str_read.size() + 1];
        strcpy(c_str, str_read.c_str());
        words = restructure(c_str);
        if(!words.size()) continue;
        //Chẻn words vào từng dòng để lấy thứ tự dòng
        lines.push_back({PC, words});
        if(words.size() == 1) {
            // neu la label, them vao map cho de~ truy xuat
            labelsAddress.insert({words[0], PC});
        }
        else PC += 4;
    }

    for(auto &line : lines) {
        // khuc nay van la int, chua chuyen sang hex
        fout << line.first << ": ";
        for (auto &j : line.second) fout << j << " ";
        fout << "\n";
    }
}
    
int main(){
    cout << "Nhap file can test: (VD: test1, test2,...)";
    cin >> in;
    txt_convert();
    read_txt();
    reg_dict();
    ofstream bout("../in_out/binary/" + in + ".txt", ios_base::trunc);
    size_t size = lines.size();
    cout << "Size: " << size << "\n";
    for (const auto& line : lines) {
        if(line.second.size() == 1) continue;
        string output;
        //Thêm giá trị vào thanh ghi
        // register_value[17] = 3; //0011
        // register_value[18] = 5; //0101

        auto lineAddress = line.first;
        auto words = line.second;
        //Đọc từng dòng và chuyển đổi
        if (TYPE[words[0]] == "R") {
            if (words[0] == "jr") output = OPCODE[words[0]] + REG[words[1]] + REG["$zero"] + REG["$zero"] + "00000" + FUNCT[words[0]];
            else output = instruct_R(words[0], words[2], words[3], words[1]);
        }
        else output = instruct_I(words, lineAddress, labelsAddress);
        
        //Thử in giá trị thanh ghi sau khi thực hiện lệnh add
        for (const auto& j : words) {
            cout << j << " ";
        }
        //Test output
        cout << endl;
        cout << "rd register value: " <<register_value[decimal_convert(REG[words[1]])] << "\n";
        cout << "Bit length: " << output.length() << "\n";
        cout << "Binary address: " << output << "\n";
        cout << "Hex address: " << hex_convert(output) << "\n";
        //Ghi giá trị vào file binary
        bout << output << "\n";
        cout << endl;
    }
}
