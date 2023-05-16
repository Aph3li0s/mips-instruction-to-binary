#include <bits/stdc++.h>
using namespace std;

vector<char*> restructure(char code[255]);

int main() {
    fstream fi("../testcases/input.txt");
    fstream fo("../output/output.txt");
    string tmp;
    while(getline(fi, tmp)) {
        vector<char*> words;
        char* c_str = new char [tmp.size() + 1];
        strcpy(c_str, tmp.c_str());
        words = restructure(c_str);
      
        // test ket qua
        for(auto &word : words) {
            cout << word << " ";
        }
        cout << endl;
    }
}

// Xoa comments, spaces, commas, .data, .text
// Tra ve vector
vector<char*> restructure(char code[255]) {
    vector<char*> _;
    auto k = strtok(code, " ,");
    while(k != NULL) {
        if(*k == '#') break;
        if(*k != '.') _.push_back(k);
        k = strtok(NULL, " ,");
    }
    return _;
}
