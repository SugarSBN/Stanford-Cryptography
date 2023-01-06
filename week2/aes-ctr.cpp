// g++ aes-ctr.cpp -I /usr/include/crypto++ -o aes-ctr -lcryptopp
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
    // Question 3.
    //string keys = transfer("36f18357be4dbd77f050515c73fcf9f2");
    //string cts = transfer("69dda8455c7dd4254bf353b773304eec0ec7702330098ce7f7520d1cbbb20fc388d1b0adb5054dbd7370849dbf0b88d393f252e764f1f5f7ad97ef79d59ce29f5f51eeca32eabedd9afa9329");
    //string ivs = cts.substr(0, 16);
    //string ct = cts.substr(16, cts.length() - 16);
    // Question 4.
    string keys = transfer("36f18357be4dbd77f050515c73fcf9f2");
    string cts = transfer("770b80259ec33beb2561358a9f2dc617e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451");
    string ivs = cts.substr(0, 16);
    string ct = cts.substr(16, cts.length() - 16);

    SecByteBlock key(reinterpret_cast<const byte*>(&keys[0]), keys.size());
    SecByteBlock iv(reinterpret_cast<const byte*>(&ivs[0]), ivs.size());

    string recovered = "";
    try{
        CTR_Mode< AES > :: Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource s(ct, true, 
            new StreamTransformationFilter(d,
                new StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource

        
        cout << recovered <<  endl;
        
        cout << recovered.length() << endl;
    }catch(const Exception& e){
        cerr << e.what() <<  endl;
        exit(1);
    }

    return 0;
}