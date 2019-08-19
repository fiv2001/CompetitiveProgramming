/*
    We make a bipartile graph of 2 * n vertices: we connect every number to every place in array; In this graph we
    have some bad edges - some numbers we can't put in some places; For every k we count the amount of ways to
    choose from bad edges a matching of size k; then using inclusion-exclusion formula we get the answer;
*/

#include <bits/stdc++.h>
#include <complex>
#define pb push_back
#define pll pair <ll, ll>
#define MOMI using namespace std;
#define mp make_pair
#define pyshnapyshnakaa ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
#pragma optimize("TKACHENKO-GORYACHENKO")
#pragma GCC optimize("O3")

//#pragma GCC optimize("unroll-loops")
//#define double long double

typedef long long ll;

typedef long double ld;

using namespace std;

const ll maxn = 7e3;
const ll mod = 924844033;

ll n, k;

ll ANS[maxn];

ll F[maxn];

ll RF[maxn];

ll step(ll a, ll x){
    if (x == 0){
        return 1;
    }
    if (x % 2 == 1){
        return a * (step(a, x - 1)) % mod;;
    }
    ll t = step(a, x / 2);
    return t * t % mod;
}

ll del(ll a, ll b){
    return a * step(b, mod - 2) % mod;
}

ll getc(ll n, ll k){
//    cout << "getc " << n << " " << k << " " << F[n] * RF[k] % mod * RF[n - k] % mod << endl;
    return F[n] * RF[k] % mod * RF[n - k] % mod;
}

int main() {
    ll q, w, e, a, b;
    pyshnapyshnakaa;
    F[0] = 1;
    RF[0] = del(1, F[0]);
    for (q = 1; q < maxn; q++){
        F[q] = F[q - 1] * q;
        F[q] %= mod;
        RF[q] = del(1, F[q]);
    }
    cin >> n >> k;
    if (2 * k >= n){
        ll c = min(2 * n - 2 * k, n);
        ll ans = F[n];
        for (q = 1; q <= c; q++){
            if (q % 2 == 1){
                ans -= F[n - q] * getc(c, q);
                ans += mod * mod;
                ans %= mod;
            }
            else{
                ans += F[n - q] * getc(c, q);
                ans %= mod;
            }
        }
        cout << ans;
    }
    else{
        ANS[0] = 1;
        for (q = 0; q < k; q++){
            ll c = 0;
            for (w = q; w < n; w += k){
                c++;
            }
//            cout << c << " C" << endl;
            vector <vector <ll> > D1;
            D1.resize(c + 10);
            for (w = 0; w < c; w++){
                D1[w].resize(n + 10);
            }
            D1[1][1] = 1;
            for (w = 2; w < c; w++){
                for (e = 1; e <= c; e++){
                    if (e == 1){
                        D1[w][e] = D1[w - 1][e] + 1;
//                        cout << "D " << w << " " << e << " " << D1[w][e] << endl;
                        continue;
                    }
                    if (w - 2 >= 0 && e >= 1){
                        D1[w][e] = D1[w - 1][e] + D1[w - 2][e - 1];
                        D1[w][e] %= mod;
                    }
                    else{
                        D1[w][e] = D1[w - 1][e];
                    }
//                    cout << "D " << w << " " << e << " " << D1[w][e] << endl;
                }
            }
//            DP.pb(D1);
            ll ANS1[maxn];
            for (w = 0; w < 2 * n; w++){
                ANS1[w] = ANS[w];
            }
            for (w = 0; w <= c; w++){
                for (e = 2 * n - 1; e >= 0; e--){
                    if (e - w >= 0){
                        ANS1[e] = D1[c - 1][w] * ANS[e - w] + ANS1[e];
                        ANS1[e] %= mod;
                    }
                }
            }
            for (w = 0; w < 2 * n; w++){
                ANS[w] = ANS1[w];
//                ANS1[w] = 0;
            }
//            cout << "ANS" << endl;
//            for (w = 0; w < 2 * n; w++){
//                cout << ANS[w] << " ";
//            }
//            cout << endl;
            for (w = 0; w <= c; w++){
                for (e = 2 * n - 1; e >= 0; e--){
                    if (e - w >= 0){
                        ANS1[e] = D1[c - 1][w] * ANS[e - w] + ANS1[e];
                        ANS1[e] %= mod;
                    }
                }
            }
            for (w = 0; w < 2 * n; w++){
                ANS[w] = ANS1[w];
//                ANS1[w] = 0;
            }
//            cout << "ANS" << endl;
//            for (w = 0; w < 2 * n; w++){
//                cout << ANS[w] << " ";
//            }
//            cout << endl;
//            for (w = 0; w < c; w++){
//                cout << D1[c - 1][w] << " ";
//            }
//            cout << endl << endl;
        }
        ll ans = F[n];
        for (q = 1; q <= 2 * n; q++){
            if (q % 2 == 1){
//                if (F[n - q] > 1e10){
//                    return -1;
//                }
                ans -= (F[n - q] * ANS[q] % mod);
                ans += mod;
                ans %= mod;
            }
            else{
                ans += F[n - q] * ANS[q];
                ans %= mod;
            }
        }
        cout << ans;
    }
    return 0;
}
