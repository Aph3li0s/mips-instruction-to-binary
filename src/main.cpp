#include <bits/stdc++.h>
#include "instruction.h"
using namespace std;

// Biến này để nhập file muốn dịch
string in; 

// Xóa các cmt, kí tự dư thừa, tokenize các từ, handle label và quăng vào vector
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

// Hàm này để chuyển đổi file .asm sang .txt trong trường hợp input dạng file .asm
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

// Biến này để lưu trữ từng dòng sau chuẩn hoá
vector<pair<int, vector<string>>> lines;

// Biến này để lưu trữ địa chỉ của label trong chương  trình
map<string, int> labelsAddress;

// Biến này để giữ địa chỉ từng dòng
int PC = 0;

// Hàm này đọc dữ liệu từ file text (chưa chuẩn hoá) để đưa vào bước tiền xử lí
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
        
        // Nếu dòng rỗng, bỏ qua
        if(!words.size()) continue;
        
        // Lưu giữ địa chỉ từng dòng
        lines.push_back({PC, words});
        
        // Nếu dòng hiện tại là label, không tăng biến địa chỉ
        // Thay vào đó lưu vào từ điển để dễ truy xuất lúc sau
        if(words.size() == 1) {
            labelsAddress.insert({words[0], PC});
        }
        
        else PC += 4;
    }

    // Xuất file output tạm thời
    // File là input đã được chuẩn hoá + đánh số từng dòng, đánh dưới dạng số nguyên
    for(auto &line : lines) {
        fout << line.first << ": ";
        for (auto &j : line.second) fout << j << " ";
        fout << "\n";
    }
}
    

int main(){
    cout << "Nhap file can test(VD: test1, test2,...): ";
    cin >> in;
    txt_convert();
    read_txt();
    reg_dict();
    ofstream bout("../in_out/binary/" + in + ".txt", ios_base::trunc);
    ofstream hout("../in_out/hex/" + in + ".txt", ios_base::trunc);
    size_t size = lines.size();
    cout << "Size: " << size << "\n";
    for (const auto& line : lines) {
        
        // Nếu dòng hiện tại là label -> không biểu diễn, bỏ qua
        if(line.second.size() == 1) continue;
        
        string output;
        // Thêm giá trị vào thanh ghi
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
        
        // In lại lệnh sau chuẩn hoá để dễ theo dõi
        for (const auto& j : words) {
            cout << j << " ";
        }
        
        // Test output
        cout << endl;
        cout << "rd register value: " <<register_value[decimal_convert(REG[words[1]])] << "\n";
        cout << "Bit length: " << output.length() << "\n";
        cout << "Binary address: " << output << "\n";
        cout << "Hex address: " << hex_convert(output) << "\n";
        
        // Ghi giá trị vào file binary, file hex
        bout << output << "\n";
        hout << hex_convert(output) << "\n";
        cout << endl;
    }
}
