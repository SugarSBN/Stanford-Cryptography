/*
 * @Author: SuBonan
 * @Date: 2023-02-03 18:46:01
 * @FilePath: /week6/main.cpp
 * @Github: https://github.com/SugarSBN
 * これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
 */
// g++ main.cpp -o main -lgmp -lgmpxx && ./main
#include <iostream>
#include <cstdio>
#include "gmpxx.h"

using namespace std;

mpz_class pow(mpz_class a, mpz_class b, mpz_class p){
    mpz_class ans = 1;
    while (b) {
        if (b % 2 == 1) ans = (ans * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ans;
}

pair<mpz_class, mpz_class> exgcd (mpz_class a, mpz_class b) {
    if (b == 0) return make_pair(1, 0);
    pair<mpz_class, mpz_class> t = exgcd(b, a % b);
    return make_pair(t.second, t.first - (a / b) * t.second);
}

mpz_class inv(mpz_class a, mpz_class p){
    pair<mpz_class, mpz_class> t = exgcd(a, p);
    return t.first % p;
}


int main(){
    // part1
    mpz_class N;
    N = "179769313486231590772930519078902473361797697894230657273430081157732675805505620686985379449212982959585501387537164015710139858647833778606925583497541085196591615128057575940752635007475935288710823649949940771895617054361149474865046711015101563940680527540071584560878577663743040086340742855278549092581";
    mpz_class A;
    A = sqrt(N) + 1;
    mpz_class x;
    x = sqrt(A * A - N);
    mpz_class c;
    c = (A - x) * (A + x);
    cout << (c == N) << endl;
    cout << A - x << endl;

    // part2
    mpz_class N1;
    N1 = "648455842808071669662824265346772278726343720706976263060439070378797308618081116462714015276061417569195587321840254520655424906719892428844841839353281972988531310511738648965962582821502504990264452100885281673303711142296421027840289307657458645233683357077834689715838646088239640236866252211790085787877";
    mpz_class A1;
    A1 = sqrt(N1) + 1;
    for (int i = 0;i <= 1024 * 1024;i++) {
        mpz_class B1;
        B1 = A1 + i;
        mpz_class x1;
        x1 = sqrt(B1 * B1 - N1);
        if (((B1 - x1) * (B1 + x1)) == N1) {
            cout << B1 - x1 << endl;
            break;
        }
    }

    // part3 noticing: 3q is odd and 2p is even
    mpz_class N2;
    N2 = "720062263747350425279564435525583738338084451473999841826653057981916355690188337790423408664187663938485175264994017897083524079135686877441155132015188279331812309091996246361896836573643119174094961348524639707885238799396839230364676670221627018353299443241192173812729276147530748597302192751375739387929";
    mpz_class A2;
    A2 = sqrt(6 * N2) + 1;
    mpz_class x2;
    // (A2 - 0.5 - x - 0.5)(A2 - 0.5 + x + 0.5) = 6N
    mpz_class a, b;
    a = 1; b = 1; c = A2 + 6 * N2 - A2 * A2;
    x2 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    mpz_class p, q;
    p = (A2 - x2 - 1) / 3;
    q = (A2 + x2) / 2;
    cout << ((p * q) == N2) << endl;
    cout << p << endl;

    cout << "---- " << endl;
    // part4
    p = A - x;
    q = A + x;
    mpz_class e;
    e = 65537;
    mpz_class ct;
    ct = "22096451867410381776306561134883418017410069787892831071731839143676135600120538004282329650473509424343946219751512256465839967942889460764542040581564748988013734864120452325229320176487916666402997509188729971690526083222067771600019329260870009579993724077458967773697817571267229951148662959627934791540";
    mpz_class phi;
    phi = (p - 1) * (q - 1);
    mpz_class d;
    d = inv(e, phi);
    mpz_class pt;
    pt = pow(ct, d, p * q);
    string s = pt.get_str(16);
    for (int i = 0;i < s.length();i++) if (s[i] == '0' && s[i - 1] == '0') s = s.substr(i + 1, s.length() - i - 1);
    for (int i = 0;i < s.length();i += 2){
        int a = (s[i] >= 'a' ? s[i] - 'a' + 10 : s[i] - '0');
        int b = (s[i + 1] >= 'a' ? s[i + 1] - 'a' + 10 : s[i + 1] - '0');
        cout << (char)(a * 16 + b);
    }cout<<endl;
    return 0;
}