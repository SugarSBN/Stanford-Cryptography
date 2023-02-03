#include <iostream>
#include <cstdio>
#include "gmpxx.h"

using namespace std;

mpz_class p, g, h, gb; 
const int MAXN = (1 << 20);

pair<mpz_class, int> table[MAXN];

pair<mpz_class, mpz_class> exgcd (mpz_class a, mpz_class b) {
    if (b == 0) return make_pair(1, 0);
    pair<mpz_class, mpz_class> t = exgcd(b, a % b);
    return make_pair(t.second, t.first - (a / b) * t.second);
}

mpz_class inv(mpz_class a){
    pair<mpz_class, mpz_class> t = exgcd(a, p);
    return t.first % p;
}

mpz_class pow(mpz_class a, long long b){
    mpz_class ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ans;
}

mpz_class mod(mpz_class a, mpz_class b){
    return (a % b + b) % b;
}

int main(){
    p = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171";
    g = "11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568";
    h = "3239475104050450443565264378728065788649097520952449527834792452971981976143292558073856937958553180532878928001494706097394108577585732452307673444020333";

    cout << pow(g, 375374217830) << endl;
    return 0;


    gb = pow(g, MAXN);

    for (int i = 0;i < MAXN;i++) {
        table[i] = make_pair(h * mod(inv(pow(g, i)), p) % p, i);
        if (i % 5000 == 0) cout << i << endl;
    }
    sort(table, table + MAXN);

    long long ans;
    for (int i = 0;i < MAXN;i++) {
        mpz_class t = pow(gb, i);
        int index = lower_bound(table, table + MAXN, make_pair(t, 0)) - table;
        if (index < MAXN && table[index].first == t) {
            ans = 1LL * i * MAXN + table[index].second;
            break;
        }
    }
    cout << ans << endl;
    cout << (pow(g, ans) == h) << endl;
}