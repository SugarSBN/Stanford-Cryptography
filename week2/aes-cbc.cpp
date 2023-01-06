// g++ aes-cbc.cpp -I /usr/include/crypto++ -o aes-cbc -lcryptopp
#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"

#include <iostream>
#include <string>

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

int main(int argc, char* argv[]){

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink( cout));
    // Question 1.
    // string keys = transfer("140b41b22a29beb4061bda66b6747e14");
    // string cts = transfer("4ca00ff4c898d61e1edbf1800618fb2828a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c6822236e1daafb94ffe0c5da05d9476be028ad7c1d81");
    // string ivs = cts.substr(0, 16);
    
    // Question 2.
    string keys = transfer("140b41b22a29beb4061bda66b6747e14");
    string cts = transfer("5b68629feb8606f9a6667670b75b38a5b4832d0f26e1ab7da33249de7d4afc48e713ac646ace36e872ad5fb8a512428a6e21364b0c374df45503473c5242a253");
    string ivs = cts.substr(0, 16);
    
    
    SecByteBlock key(reinterpret_cast<const byte*>(&keys[0]), keys.size());
    SecByteBlock iv(reinterpret_cast<const byte*>(&ivs[0]), ivs.size());

    string recovered;
    try{
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource s(cts, true, 
            new StreamTransformationFilter(d,
                new StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource

        // length of recoved is 56(Q1) and 48(Q2), we need to desert 16 bytes of IV, so we print the last 40(Q1) and 32(Q2) bytes. 
        
        // Question 1:
        // cout << "recovered text: " << recovered.substr(recovered.length() - 40, 40) <<  endl;
        // Question 2:
        cout << "recovered text: " << recovered.substr(recovered.length() - 32, 32) <<  endl;
        
        cout << recovered.length() << endl;
    }catch(const Exception& e){
        cerr << e.what() <<  endl;
        exit(1);
    }

    return 0;
}