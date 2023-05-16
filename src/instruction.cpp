//Sử dụng để lưu từ điển
//Xác định loại lệnh (R hay I), chuyển các mã lệnh thành binary code
//Viết thêm 1 hàm chuyển từ binary sang hex để dễ đối chiếu hơn

#include "instruction.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

vector<string> restructure(char code[255]);

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