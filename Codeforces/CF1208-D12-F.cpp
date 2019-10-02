/*
        We count for every x the two maximum-right different indexes j and k where x is a submask of A[j] and A[k]. We do it using SOS-DP
        (https://codeforces.com/blog/entry/45223). Then we iterate over i and go with j from the biggest degree of 2 to the smallest ones
        and try to get j-th bit in the current sum. We can do it if the smallest of two biggest indexes in dp[sum + st2[i]] is bigger 
        than j.
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

typedef long long ll;

typedef long double ld;

using namespace std;

const ll maxn = 3e6;
const ll maxlog = 21;
const ll inf = 1e15;

ll n, m, k;

ll st2[maxn];

ll A[maxn];

pll D[maxn];

pll mrg(pll a, pll b){
    if (a.first < b.first){
        swap(a, b);
    }
    a.second = max(a.second, b.first);
    return a;
}

int main(){
    ll q, w, e, t, a, b, c;
    pyshnapyshnakaa;
    st2[0] = 1;
    for (q = 1; q < maxlog + 5; q++){
        st2[q] = st2[q - 1] * 2;
//        cout << q << " " << st2[q] << endl;
    }
    for (q = 0; q < maxn; q++){
        D[q] = mp(-inf, -inf);
    }
    cin >> n;
    for (q = 0; q < n; q++){
        cin >> A[q];
        D[A[q]] = mrg(D[A[q]], mp(q, -inf));
    }
    for (w = 1; w < maxlog; w++){
        for (q = 0; q < st2[maxlog]; q++){
            if ((q & st2[w - 1]) == 0){
                D[q] = mrg(D[q], D[q + st2[w - 1]]);
            }
        }
    }
//    for (q = st2[maxlog] - 1; q >= 0; q--){
////        ll qq = q;
//        for (w = 1; w < maxlog; w++){
//            if ((q & st2[w - 1]) != 0){
//                D[q][w] = mrg(D[q][w], D[q][w - 1]);
////                cout << "PERESCHET " << D[q][w - 1].first << " " << D[q][w - 1].second << endl << endl;
//            }
//            else{
////                if (q - st2[w] < 0)cout << "DANGER " << q - st2[w] << " " << q << " " << st2[w] << endl;
//                D[q][w] = mrg(D[q][w], mrg(D[q][w - 1], D[q + st2[w - 1]][w - 1]));
////                q += st2[w];
////                if (q <= 15)cout << q + st2[w - 1] << " " << D[q + st2[w - 1]][w - 1].first << " "
////                << D[q + st2[w - 1]][w - 1].second << " VISOS" << endl;
//            }
////            if (q <= 15)cout << "DP " << q << " " << w << " " << D[q][w].first << " " << D[q][w].second << endl;
//        }
////        if (q <= 15)cout << endl << endl;
//    }
//    cout << "DP BUILT " << endl;
    ll ans = 0;
    for (q = 0; q < n - 2; q++){
        ll dans = A[q];
        ll dmx = 0;
        for (w = maxlog - 1; w >= 0; w--){
//            cout << w << " " << st2[w] << " ST2" << endl;
            if ((A[q] & st2[w]) == 0){
//                cout << " D " << w << " " << q << " " << st2[w] + dmx << " " << D[st2[w] + dmx][maxlog - 1].second << endl;
                if (D[st2[w] + dmx].second > q){
                    dmx += st2[w];
                }
            }
        }
//        cout << q << " " << dmx << endl;
        dans += dmx;
        ans = max(ans, dans);
    }
    cout << ans;
    return 0;
}
