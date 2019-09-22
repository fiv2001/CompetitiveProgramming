/*
    Let dp[msk] be the cost of placement of colors from msk as the prefix of our array; then we precalc the amount of inversions for
    every color; And then we count the dp iterating over the colors from msk and choosing the current color to be the last one in the 
    prefix;
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

const ll maxn = 5e5;
const ll maxc = 20;
const ll mxst2 = 2097152;
const ll inf = 1e15;

ll n, m, k;

ll A[maxn];

ll st2[maxn];

ll C[maxc][maxc];

ll CNT[maxc];

ll D[mxst2];

int main(){
    ll q, w, e, t, a, b, c;
    cin >> n;
    for (q = 0; q < n; q++){
        cin >> A[q];
        A[q]--;
    }
    st2[0] = 1;
    for (q = 1; q < maxn; q++){
        st2[q] = st2[q - 1] * 2;
    }
    for (q = 0; q < n; q++){
        for (w = 0; w < maxc; w++){
            if (w == A[q]){
                continue;
            }
            C[A[q]][w] += CNT[w];
        }
        CNT[A[q]]++;
    }
    for (q = 1; q < st2[maxc]; q++){
        D[q] = inf;
        ll msk = q;
        ll M[maxc];
        for (w = 0; w < maxc; w++){
            if ((msk & st2[w]) != 0){
                M[w] = 1;
            }
            else{
                M[w] = 0;
            }
        }
//        cout << "M " << endl;
//        for (w = 0; w < maxc; w++){
//            cout << M[w] << " ";
//        }
//        cout << endl;
        for (w = 0; w < maxc; w++){
            if (M[w] == 1){
                ll sum = 0;
//                cout << w << " " << q - st2[w] << endl;
                for (e = 0; e < maxc; e++){
                    if (M[e] == 0){
//                        cout << "W E " << w << " " << e << endl;
//                        cout << "CWE " << C[w][e] << endl;
                        sum += C[w][e];
                    }
                }
                D[q] = min(D[q], D[q - st2[w]] + sum);
            }
        }
//        cout << q << " " << D[q] << " D" << endl << endl;;
    }
    cout << D[st2[maxc] - 1];
    return 0;
}
