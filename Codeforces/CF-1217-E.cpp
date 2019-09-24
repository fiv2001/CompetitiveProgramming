/*
    If there are 2 numbers who don't end by zero, they form a bad set of numbers; And let's prove by induction of the i that if 
    none of 2 numbers has a zero in the i-th digit, then they form a bad set of numbers: basis is i == 0, and if 2 numbers (a and b) 
    both don't have a zero in the i-th state and the sum of these numbers has in the i-th position a digit equal to one of the digits 
    on the i-th position from one of the two numbers, then the second number ends by 9 and in the a[i - 1] + b[i - 1] >= 10 or 
    a[i - 1] + b[i - 1] == 9 and a[i - 2] + b[i - 2] >= 10 or ... and so on, so finally we come to a j-th digit (j < i) where a[j] != 0
    and b[j] != 0; then by the proposition of induction they form a bad set.
    So we build a segment tree for each place of digit (from 0 to 9) and get on the segment the two minimums on the segment;
    In every segment tree for every number a we store a if a hasn't got a zero in the digit of this segment tree and inf otherwise. 
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

typedef int ll;

typedef long double ld;

using namespace std;

const ll maxn = 2e5 + 100;
const ll mxst = 9;
const ll inf = 2e9;

ll n, m, k;

pll V[4 * maxn][mxst];

ll A[maxn];

bool is[maxn][mxst];

pll dflt = {inf, inf};

inline pll mrg(pll a, pll b){
    if (a.first > b.first){
        swap(a, b);
    }
    a.second = min(a.second, b.first);
    return a;
}

inline void build(ll v, ll tl, ll tr, ll i){
    if (tl == tr){
        if (is[tl][i]){
//            cout << "GOOD_BUILD " << tl << " " << i << " " << A[tl] << endl;
            V[v][i] = mp(A[tl], inf);
        }
        else{
            V[v][i] = mp(inf, inf);
        }
        return;
    }
    ll tm = (tl + tr) / 2;
    build(2 * v, tl, tm, i);
    build(2 * v + 1, tm + 1, tr, i);
    V[v][i] = mrg(V[2 * v][i], V[2 * v + 1][i]);
//    cout << "BUILD " << tl << " " << tr << " " << V[v][i].first << " " << V[v][i].second << endl;
}

inline void update(ll v, ll tl, ll tr, ll i, ll color, ll i1){
    if (tl > i || tr < i){
        return;
    }
    if (tl == tr){
        V[v][i1] = mp(color, inf);
        return;
    }
    ll tm = (tl + tr) / 2;
    if (tm >= i){
        update(2 * v, tl, tm, i, color, i1);
    }
    else {
        update(2 * v + 1, tm + 1, tr, i, color, i1);
    }
    V[v][i1] = mrg(V[2 * v][i1], V[2 * v + 1][i1]);
}

inline pll getmn(ll v, ll tl, ll tr, ll l, ll r, ll i){
    if (l > tr || tl > r || l > r){
        return dflt;
    }
    if (tl == l && tr == r){
        return V[v][i];
    }
    ll tm = (tl + tr) / 2;
    pll mn1 = getmn(2 * v, tl, tm, l, min(r, tm), i);
    pll mn2 = getmn(2 * v + 1, tm + 1, tr, max(tm + 1, l), r, i);
    return mrg(mn1, mn2);
}

int main(){
    ll q, w, e, t, a, b, c;
    pyshnapyshnakaa;
    cin >> n >> k;
    for (q = 0; q < n; q++){
        cin >> A[q];
        ll i = 0;
        ll a = A[q];
        while (a != 0){
            ll c = a % 10;
            if (c != 0){
                is[q][i] = 1;
            }
            a /= 10;
            i++;
        }
    }
    for (q = 0; q < mxst; q++){
        build(1, 0, n - 1, q);
//        cout << endl << endl;
    }
    ll comm;
    for (e = 0; e < k; e++){
        cin >> comm;
        if (comm == 1){
            ll i, x;
            cin >> i >> x;
            i--;
            ll j = 0, a = x;
            ll cnt = 0;
            while (cnt < mxst){
                ll c = a % 10;
                if (c != 0){
                    update(1, 0, n - 1, i, x, j);
                }
                else{
                    update(1, 0, n - 1, i, inf, j);
                }
                a /= 10;
                j++;
                cnt++;
            }
//            cout << "ARTEM" << endl;
        }
        else{
            ll l, r;
            cin >> l >> r;
            l--; r--;
            ll ans = inf;
            for (q = 0; q < mxst; q++){
                pll mn = getmn(1, 0, n - 1, l, r, q);
                if (mn.second == inf){
                    continue;
                }
                ans = min(ans, mn.first + mn.second);
//                if (ans != inf){
//                    cout << "GOODANS " << q << " " << ans << endl;
//                }
            }
            if (ans == inf){
                cout << -1 << '\n';
            }
            else{
                cout << ans << '\n';
            }
        }
    }
    return 0;
}
