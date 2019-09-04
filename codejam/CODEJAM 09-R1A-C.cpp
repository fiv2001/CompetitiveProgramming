/*
    We say that the chance of doing more than 2000 moves is very little, then we solve the task by dp[i][j] which means 
    the probability of having exactly i types of cards after j moves; 
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

const ll maxn = 50;
const ll maxc = 2000;

ll n, m, k;

ld D[maxn][maxc]; /// probability of getting i cards after j moves; i; j;

ll C[maxn][maxn];

ll getc(ll n, ll k){
//    cout << "START" << endl;
//    cout << n << " " << k << " " << C[n][k] << " getc" << endl;
//    cout << "END" << endl;
    return C[n][k];
}

int main(){
    ll q, w, e, t, a, b, c;
    freopen("C-large-practice.in", "r", stdin);
    freopen("C.txt", "w", stdout);
    cin >> k;
    cout << setprecision(40) << fixed;
    C[0][0] = 1;
    for (q = 1; q < maxn; q++){
        C[q][0] = C[q][q] = 1;
        for (w = 1; w < q; w++){
            C[q][w] = C[q - 1][w] + C[q - 1][w - 1];
        }
    }
//    cout << k << endl;
//    cout << "FIST" << endl;
    for (t = 0; t < k; t++){
        for (q = 0; q < maxn; q++){
            for (w = 0; w < maxc; w++){
                D[q][w] = 0;
            }
        }
        cin >> n >> m;
//        cout << n << " " << m << endl;
//        continue;
        D[0][0] = 1;
        ld ans = 0;
        for (q = 0; q < maxc - 1; q++){
            ans += q * (D[n][q]);
            for (w = 0; w < n; w++){
//                cout << "D " << w << " " << q << " " << D[w][q] << endl;
//                if (w == n){
//                    ans += q * (D[w][q]);
//                }
                for (e = w; e <= n; e++){
                    ld prob = 0;
                    if (getc(n, m) != 0 && (m - (e - w) >= 0)){
                        prob = getc(n - w, e - w) * getc(w, (m - (e - w))) * 1.0 / (getc(n, m));
                    }
                    D[e][q + 1] += D[w][q] * prob;
                }
            }
        }
        cout << "Case #" << t + 1 << ": " << ans << endl;
    }
    return 0;
}
