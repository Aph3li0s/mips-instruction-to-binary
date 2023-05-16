#include <bits/stdc++.h>
#include "instruction.h"
using namespace std;

vector<string> restructure(char code[255]) {
    vector<string> formatted_str;
    auto k = strtok(code, " ,\t");
    while(k != NULL) {
        if(*k == '#') break;
        if(*k != '.') {
            std::string str(k);
            formatted_str.push_back(k);
        }
        k = strtok(NULL, " ,\t");
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

void read_txt(){
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
        
        // test ket qua
        for(auto &word : words) {
            cout << word << " ";
        }
        cout << endl;
    }
}
int main(){
    txt_convert();
    read_txt();
}
