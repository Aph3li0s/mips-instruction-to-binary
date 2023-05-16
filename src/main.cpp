#include <bits/stdc++.h>
#include "instruction.h"
#include "trans.h"
using namespace std;

void txt_convert(){
    ifstream fin("../testcases/test1.asm");
    ofstream fout("../in_out/input/test1.txt", ios_base::trunc);
    string str_read;
    while (getline(fin, str_read)) {
        fout << str_read;
        fout << "\n";
    }
    fin.close();
    fout.close();
}

int main(){
    txt_convert();
}
