/*
  First we make a graph which looks like braid: we create a vertex x1 which has 2 ways to vertex 1, then we create a vertex x2
  which has 2 ways to vertex x1 and so on. After for every i we have a vertex which has 2 ^ i ways to vertex 1. Then we binary convert 
  number k and for every bit j which is in k, we connect the vertex which has 2 ^ j ways to vertex 1 with vertex 2(not by a single edge
  but by a sequence of edges).
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

const ll maxn = 1e3;
const ll inf = 1e16;

ll n, m, k;

bool ANS[maxn][maxn];

ll st2[maxn];

bool B[maxn];

void connect(ll i, ll j){
    ANS[i][j] = ANS[j][i] = 1;
//    cout << "connect " << i << " " << j << endl;
}

ll J[maxn];

int main() {
    ll q, w, e, a, b, t;
//    pyshnapyshnakaa;
    cin >> k;
    st2[0] = 1;
    for (q = 1; q < 40; q++){
        st2[q] = st2[q - 1] * 2;
    }
    for (q = 0; q < 40; q++){
        if (k & st2[q]){
            B[q] = 1;
        }
    }
    ll i = 2;
    ll j = 0;
    J[0] = 0;
    for (q = 0; q < 30; q++){
        connect(j, i);
        i++;
        connect(j, i);
        i++;
        connect(i, i - 2);
        connect(i, i - 1);
        j = i;
        J[q + 1] = j;
        i++;
    }
//    cout << "FINISHED BUILDING" << endl;
    ll len = 60;
    for (q = 0; q < 30; q++){
        if (B[q]){
            ll j = J[q];
            for (w = 0; w < len - 2 * q - 1; w++){
                connect(i, j);
                j = i;
                i++;
            }
            connect(j, 1);
        }
    }
    cout << i << endl;
    for (q = 0; q < i; q++){
        for (w = 0; w < i; w++){
            if (ANS[q][w]){
                cout << "Y";
            }
            else{
                cout << "N";
            }
        }
        cout << endl;
    }
    return 0;
}
