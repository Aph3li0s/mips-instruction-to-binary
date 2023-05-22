#include <bits/stdc++.h>
#include "instruction.h"
using namespace std;
string in; 

//Hàm chuẩn hóa, lược bỏ các cmt và các từ dư thừa 
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
//Hàm chuyển đổi file .asm thành file .txt
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
//PC là địa chỉ của dòng lệnh, tính từ dòng lệnh đầu tiên
int PC = 0;

// Hàm này lấy subvector của 1 vector trong 1 đoạn cho trước
// arr: vector gốc
// X: index vị trí đầu muốn lấy
// Y: index vị trí đuôi muốn lấy
// Lấy cả tại vị trí X và Y
vector<string> slicing(vector<string>& arr, int X, int Y) {
    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;
    vector<string> result(Y - X + 1);
    copy(start, end, result.begin());
    return result;
}

//Hàm đọc file .txt
void read_txt(){
    ifstream fin("../in_out/input/" + in + ".txt");
    ofstream fout("../in_out/output/" + in + ".txt", ios_base::trunc);
    if (!fin) cout << "Can't open file";
    string str_read;

    while (getline(fin, str_read)){
        vector<string> tmpWords;
        char* c_str = new char [str_read.size() + 1];
        strcpy(c_str, str_read.c_str());
        tmpWords = restructure(c_str);
        if(!tmpWords.size()) continue;
        
        // Trường hợp: Dòng ở dạng "label_name : code"
        // Ta tách code và label_name riêng
        else if(tmpWords.size() > 1 && !check_opcode(tmpWords[0])) {
            auto words = slicing(tmpWords, 1, tmpWords.size() - 1);
            lines.push_back({PC, words});
            labelsAddress.insert({tmpWords[0], PC});
            PC += 4;
        }
        
        // Trường hợp: Dòng ở dạng "code"
        else if(tmpWords.size() > 1 && check_opcode(tmpWords[0])) {
            auto words = tmpWords;
            //Chẻn words vào từng dòng để lấy thứ tự dòng
            lines.push_back({PC, words});
            PC += 4;
        }
        
        // Trường hợp dòng ở dạng "label_name"
        // Do dòng chỉ có label, không tăng biến đếm địa chỉ
        else if(tmpWords.size() == 1) {
            labelsAddress.insert({tmpWords[0], PC});
        }
    }

    //Xuất ra file ouput thứ tự dòng và dòng lệnh
    for(auto &line : lines) {
        fout << line.first << ": ";
        for (auto &j : line.second) fout << j << " ";
        fout << "\n";
    }
}
    
int main(){
    // Dict has to be loaded first to handle "label: code" cases
    reg_dict();
    cout << "Input file to test(EX: test1, test2,...): ";
    cin >> in;
    txt_convert();
    read_txt();

    ofstream bout("../in_out/binary/" + in + ".txt", ios_base::trunc);
    ofstream hout("../in_out/hex/" + in + ".txt", ios_base::trunc);
    //Số lượng dòng lệnh cần chuyển đổi
    size_t size = lines.size();
    cout << "Size: " << size << "\n";

    for (const auto& line : lines) {
        if(line.second.size() == 1) continue;
        string output;
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
        //Ghi giá trị vào file binary và file hex
        bout << output << "\n";
        hout << hex_convert(output) << "\n";
        cout << endl;
    }
}
