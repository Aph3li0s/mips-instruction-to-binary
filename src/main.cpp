#include <bits/stdc++.h>
#include "instruction.h"
using namespace std;

// Xóa các cmt, kí tự dư thừa, tokenize các từ và quăng vào vector
//Nghĩ thêm được test nào chứa các ngoại lệ thì thêm vào
vector<string> restructure(char code[255]) {
    vector<string> formatted_str;
    auto k = strtok(code, " ,\t()");
    while(k != NULL) {
        if(*k == '#') break;
        if(*k != '.') {
            std::string str(k);
            formatted_str.push_back(k);
        }
        k = strtok(NULL, " ,\t()");
    }
    return formatted_str;
}

void txt_convert(){
    ifstream fin("../in_out/testcases/test2.asm");
    ofstream fout("../in_out/input/test2.txt", ios_base::trunc);
    if (!fin) cout << "Can't open file";

    string str_read;
    while (getline(fin, str_read)) {
        fout << str_read;
        fout << "\n";
    }
    fin.close();
    fout.close();
}

void read_txt(){
    //Lưu ý cho việc làm test case: 
    //Các instruction thì các tham số của nó bắt buộc nằm trên 1 dòng, tức là có \n là sai cú pháp
    
    ifstream fin("../in_out/input/test2.txt");
    ofstream fout("../in_out/output/test2.txt", ios_base::trunc);
    if (!fin) cout << "Can't open file";

    string str_read;
    vector<vector<string>> lines;
    while (getline(fin, str_read)){
        vector<string> words;
        char* c_str = new char [str_read.size() + 1];
        strcpy(c_str, str_read.c_str());
        words = restructure(c_str);
        if(!words.size()) continue;
        
        //Chẻn words vào từng dòng để lấy thứ tự dòng
        lines.push_back(words);
    }
    for(auto &i : lines) {
        for (auto &j : i) fout << j << " ";
        fout << "\n";
    }
}
    
int main(){
    txt_convert();
    read_txt();
}
