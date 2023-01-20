#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
    string s = "20814804c1767293b99f1d9cab3bc3e7ac1e37bfb15599e5f40eef805488281d";
    for (int i = 0;i < s.length();i += 2){
        if (i == 18) cout << endl;
        cout << s[i] << s[i + 1];
        if (i == 18) cout << endl;
    }
    cout << endl;
    int a = 0x9f;
    printf("%x", (a ^ 49 ^ 53));
}