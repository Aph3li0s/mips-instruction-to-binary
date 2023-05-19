#include <bits/stdc++.h>
#include "instruction.h"
using namespace std;

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
    ifstream fin("../in_out/testcases/test1.asm");
    ofstream fout("../in_out/input/test1.txt", ios_base::trunc);
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
map<string, int> labelAddress;
int PC = 0;

void read_txt(){
    //Lưu ý cho việc làm test case: 
    //Các instruction thì các tham số của nó bắt buộc nằm trên 1 dòng, tức là có \n là sai cú pháp
    
    ifstream fin("../in_out/input/test1.txt");
    ofstream fout("../in_out/output/test1.txt", ios_base::trunc);
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
            labelAddress.insert({words[0], PC});
        }
        PC += 4;
    }
    
    for(auto &line : lines) {
        // khuc nay van la int, chua chuyen sang hex
        fout << line.first << ": ";
        for (auto &j : line.second) fout << j << " ";
        fout << "\n";
    }
}
    
int main(){
    txt_convert();
    read_txt();
    reg_dict();
    size_t size = lines.size();
    cout << "Size: " << size << "\n";
    for (const auto& words : lines) {
        string output;
        //Thêm giá trị vào thanh ghi
        register_value[17] = 3; //0011
        register_value[18] = 5; //0101

        if (TYPE[words[0]] == "R") output = instruct_R(words[0], words[2], words[3], words[1]);
        //else output = instruct_I();
        
        //Thử in giá trị thanh ghi sau khi thực hiện lệnh add
        for (const auto& j : words) {
            cout << j << " ";
        }
        cout << endl;
        cout << "rd register value: " <<register_value[decimal_convert(REG[words[1]])] << "\n";
        cout << "Bit length: " << output.length() << "\n";
        cout << "Binary address: " << output << "\n";
        cout << "Hex address: " << hex_convert(output) << "\n";

        cout << endl;
    }
}
