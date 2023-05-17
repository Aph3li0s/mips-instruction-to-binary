#include <bits/stdc++.h>
using namespace std;


std::string binary_convert(string s, int n) {
    int dec = stoi(s);
    string bin;
    bin.reserve(n); // Reserve space to avoid reallocation

    for (int i = 0; i < n; ++i) {
        bin = std::to_string(dec % 2) + bin;
        dec /= 2;
    }

    return bin;
}

int main(){
    string n; cin >> n;
    cout << binary_convert(n, 5);

}