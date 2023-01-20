#include "HTTPRequest.hpp" //相关源码在文章末尾
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;
int main(){
    //注意：URI地址必须以 http:// 开头，否则不符合头文件校验规则
    string uri = "http://www.google.com/";
    string method = "GET";
    auto protocol = http::InternetProtocol::V4;
    http::Request req{ uri, protocol };
    
    try {
        const auto response = req.send(method, "", {
        {"Content-Type", "application/json"},
        {"User-Agent", "runscope/0.1"},
        {"Accept", "*/*"}
            }, std::chrono::seconds(5));
    }
    catch (exception& e) {
        cout << e.what() << endl;
        //捕获请求失败异常，处理逻辑自行添加
    }
}