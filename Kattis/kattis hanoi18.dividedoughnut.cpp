/*
    Let F(x) be the amout of sprinkles in the segment [x, x + 5e8 - 1]; Then we can note that the difference between F(x) and F(x + 1) 
    is not bigger than 2 and not less than -2; If we also note that the sum of F(0) and F(5e8) is n (and n is even) we can see that 
    the answer is always yes. We do the binary search for x in (0, 5e8 - 1); Also we can see that we have 28 queries and for doing the
    usual binary search we need 29 queries, so if (R - L == 2) we can ask no more queries and just print R - 1;
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

const ll maxn = 1e9;
const ll maxc = 2000;

ll n, m, k;

void answer(ll x){
    cout << "YES " << x << endl;
    exit(0);
}

ll ask(ll l){
    cout << "QUERY " << l << " " << (l + maxn / 2 - 1) % maxn << endl;
    ll ans;
    cin >> ans;
    if (ans == n / 2){
        answer(l);
    }
    return ans;
}

int main(){
    ll q, w, e, t, a, b, c;
    cin >> n;
    bool abob = 0;
    ll L = -1, R = maxn / 2;
    a = ask(0);
    if (a >= n / 2){
        abob = 1;
    }
    if (abob == 0){
        while (R - L > 2){
            ll M = (L + R) / 2;
            ll c = ask(M);
            if (c >= n / 2){
                R = M;
            }
            else{
                L = M;
            }
        }
        answer((L + R) / 2);
    }
    else{
        while (R - L > 2){
            ll M = (L + R) / 2;
            ll c = ask(M);
            if (c >= n / 2){
                L = M;
            }
            else{
                R = M;
            }
        }
        answer((L + R) / 2);
    }
    return -1;
}
