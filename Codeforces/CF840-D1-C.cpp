/*
  First, if a * b = k^2 and b * c = l^2 then a * c = (k ^ 2/ b) * (l ^ 2 / b) = ((k * l) / (b)) ^ 2; that means that if a and b can't 
  be consecutive and b and c can't be consecutive then a and c can't be consecutive; then we can divide the numbers in groups and the 
  task becomes to count the ways to put numbers together so that every two consecutive numbers are from different groups.
  We make a dp[n][k] which means that on the prefix of n groups we have dp[n][k] consequences which have k bad places.
  We iterate over the number of segments we break the current group into and over the number of bad places we are fixing by adding 
  numbers from current group.
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

const ll maxn = 4e2;
const ll mod = 1e9 + 7;

ll n, m, k;

ll A[maxn];

ll F[maxn];

ll RF[maxn];

ll C[maxn];

ll D1[maxn][maxn];

bool base[maxn];

ll step(ll a, ll x){
    if (x == 0){
        return 1;
    }
    if (x % 2 == 1){
        return (step(a, x - 1) * a) % mod;
    }
    ll t = step(a, x / 2);
    return t * t % mod;
}

ll del(ll p, ll q){
    return p * (step(q, mod - 2)) % mod;
}

ll getc(ll n, ll k){
    if (k > n){
        return 0;
    }
//    cout <<"getc " << n << " " << k << " " << F[n] * RF[k] % mod * RF[n - k] % mod << endl;
    return F[n] * RF[k] % mod * RF[n - k] % mod;
}

ll stupid(vector <ll> G){
    vector <ll> B;
    ll q, w;
    for (q = 0; q < G.size(); q++){
        for (w = 0; w < G[q]; w++){
            B.pb(q);
        }
    }
//    for (q = 0; q < B.size(); q++){
//        cout << B[q] << " ";
//    }
//    cout << endl;
    ll ans = 0;
    for (w = 0; w < F[B.size()]; w++){
        next_permutation(B.begin(), B.end());
        bool f = 1;
        for (q = 1; q < B.size(); q++){
            if (B[q] == B[q - 1]){
                f = 0;
            }
        }
        if (f){
            ans++;
        }
    }
    return ans;
}

bool pos(ll a, ll b){
    ll L = -1, R = 1e9 + 1, M;
    while (R - L > 1){
        M = (L + R) / 2;
        if (M * M > a * b){
            R = M;
        }
        else{
            L = M;
        }
    }
    if (L * L == a * b){
        return 0;
    }
    return 1;
}

int main() {
    ll q, w, e, a, b, t;
//    pyshnapyshnakaa;
    F[0] = 1;
    RF[0] = 1;
    for (q = 1; q < maxn; q++){
        F[q] = F[q - 1] * q;
        F[q] %= mod;
        RF[q] = del(1, F[q]);
    }
    cin >> n;
    for (q = 0; q < n; q++){
        cin >> A[q];
        base[q] = 1;
        C[q] = 1;
    }
    for (q = 0; q < n; q++){
        for (w = 0; w < q; w++){
            if (!pos(A[q], A[w]) && base[w] == 1){
                base[q] = 0;
                C[w]++;
                C[q] = 0;
                break;
            }
        }
    }
    vector <ll> G;
//    ll s = 0;
    for (q = 0; q < n; q++){
        if (C[q] != 0){
            G.pb(C[q]);
//            s += C[q];
        }
    }
//    for (q = 0; q < G.size(); q++){
//        cout << G[q] << " ";
//    }
//    cout << endl;
    D1[0][0] = 1;
    ll s = 0;
    for (q = 0; q <= G.size(); q++){ /// prefix
        for (t = 0; t <= s; t++){ /// segs
//            if (D1[q][t] != 0)cout << "D1 " << q << " " << t << " " << D1[q][t] << endl;
            if (q == G.size()){
                continue;
            }
            for (w = 1; w <= G[q]; w++){ /// count of split segs
                for (e = 0; e <= w && e <= t; e++){ /// amount of upgraded pairs
                    D1[q + 1][t - e + G[q] - w] += getc(G[q] - 1, w - 1) * F[G[q]] % mod * getc(s + 1 - t, w - e) % mod
                    * D1[q][t] % mod * getc(t, e) % mod;
                    D1[q + 1][t - e + G[q] - w] %= mod;
                }
            }
        }
        s += G[q];
    }
    cout << D1[G.size()][0] << endl;
//    cout << stupid(G) << endl;
    return 0;
}
