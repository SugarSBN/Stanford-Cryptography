/*
 * @Author: SuBonan
 * @Date: 2023-01-12 20:08:42
 * @LastEditTime: 2023-01-12 20:09:00
 * @FilePath: \Stanford-Cryptography\week3\sha256.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */

// g++ sha256.cpp -I /usr/include/crypto++ -o sha256 -lcryptopp
#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"

#include <iostream>
#include <string>
#include <vector>

using namespace CryptoPP;
using namespace std;

int to_int(char c){
    if ('0' <= c && c <= '9')   return c - '0';
    if ('A' <= c && c <= 'Z')   return c - 'A' + 10;
    if ('a' <= c && c <= 'z')   return c - 'a' + 10;
    return 0;
}

char to_char(int n){
    if (n < 10) return n + '0';
    return n - 10 + 'a';
}

string transfer(string s){
    string res = "";
    for (int i = 0;i < s.length();i += 2)
        res = res + (char)(to_int(s[i]) * 16 + to_int(s[i + 1]));
    return res;
}

string transfer_back(string s){
    string res = "";
    for (int i = 0;i < s.length();i++){
        res = res + to_char(s[i] >> 4 & 0xF) + to_char(s[i] & 0xF);
    }
    return res;
}

string hashs(string s){
    HexEncoder encoder(new FileSink(std::cout));

    std::string msg = s;
    std::string digest;

    SHA256 hash;
    hash.Update((const byte*)msg.data(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((byte*)&digest[0]);
    StringSource(digest, true, new Redirector(encoder));
    return digest;
}

vector<string> readfile(string filename){
    std::ifstream is(filename, std::ifstream::binary);
    // Find the length of the file
    is.seekg(0, is.end);
    std::streampos length = is.tellg();
    is.seekg(0, is.beg);

    // Create a vector to read it into
    std::vector<unsigned char> bytes(length);

    // Actually read data
    is.read((char *)&bytes[0], length);

    // Close the file explicitly, since we're finished with it
    is.close();
    string res = "";
    vector<string> rua;
    for (int i = 0;i < bytes.size();i++){
        res = res + (char)bytes[i];
        if ((i + 1) % 1024 == 0) {
            rua.push_back(res);
            res = "";
        }
    }
    if (res.length() > 0) rua.push_back(res);
    return rua;
}

int main(){
    vector<string> file = readfile("intro.mp4");
    string s = hashs(file[file.size() - 1]);
    for (int i = file.size() - 2;i >= 0;i--){
        s = hashs(file[i] + s);
    }
    cout << endl;
    cout << transfer_back(s);
}
