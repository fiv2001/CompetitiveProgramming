/*
    We create a segtree, in which we keep for every index i, the sum in point we will get if we have a square with left corner in
    (0, 0) and right in (i, i); And we initialize this tree with -i for every i; Then we add points one by one by adding a number on 
    suffix; Then we iterate over the left corner of our square and delete points, we can't reach from all the next left corners.
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

const ll maxn = 1e6 + 100;
const ll inf = 1e15;

ll n, m, k;

pll V[4 * maxn];

ll T[4 * maxn];

ll C[maxn];

struct point{
    ll x;
    ll y;
    ll c;
};

point A[maxn];

void push(ll v, ll tl, ll tr){
    if (T[v] == 0){
        return;
    }
    V[v].first += T[v];
    if (tl != tr){
        T[2 * v] += T[v];
        T[2 * v + 1] += T[v];
    }
    T[v] = 0;
}

void build(ll v, ll tl, ll tr){
    if (tl == tr){
        V[v] = mp(C[tl], tl);
//        cout << tl << " " << tr << " " << V[v].second << " " << v << endl;
        return;
    }
    ll tm = (tl + tr) / 2;
    build(2 * v, tl, tm);
    build(2 * v + 1, tm + 1, tr);
    V[v] = max(V[2 * v], V[2 * v + 1]);
//    cout << "BUILD " << V[v].first << " " << V[v].second << " " << tl << " " << tr << endl;
}

void update(ll v, ll tl, ll tr, ll l, ll r, ll color){
    push(v, tl, tr);
    if (l > tr || tl > r || l > r){
        return;
    }
    if (tl == l && tr == r){
        T[v] += color;
        push(v, tl, tr);
        return;
    }
    ll tm = (tl + tr) / 2;
    update(2 * v, tl, tm, l, min(r, tm), color);
    update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, color);
    V[v] = max(V[2 * v], V[2 * v + 1]);
}

pll getmx(ll v, ll tl, ll tr, ll l, ll r){
    push(v, tl, tr);
    if (l > tr || tl > r || l > r){
        return mp(-inf, 0);
    }
//    cout << v << " " << tl << " " << tr << endl;
    if (l == tl && tr == r){
//        cout << "RET " << tl << " " << tr << " " << V[v].first << " " << V[v].second << " " << v << endl;
        return V[v];
    }
    ll tm = (tl + tr) / 2;
    pll mx1 = getmx(2 * v, tl, tm, l, min(r, tm));
    pll mx2 = getmx(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
    return max(mx1, mx2);
}

inline ll getlen(point a){
    return max(a.x, a.y);
}

map <ll, vector <point> > M;

map <ll, ll> P;

set <pll> S;

vector <ll> lens;

inline ll small_from_big(ll i){
    ll ans = lower_bound(lens.begin(), lens.end(), i) - lens.begin();
    return ans;
}

inline ll big_from_small(ll i){
    return lens[i];
}

int main(){
    ll q, w, e, t, a, b, c;
    cin >> n;
    for (q = 0; q < n; q++){
        cin >> A[q].x >> A[q].y >> A[q].c;
        S.insert(mp(A[q].x, A[q].y));
        ll len = getlen(A[q]);
        lens.pb(len);
        lens.pb(min(A[q].x, A[q].y));
        M[min(A[q].x, A[q].y)].pb(A[q]);
    }
    lens.pb(0);
    sort(lens.begin(), lens.end());
    lens.resize(unique(lens.begin(), lens.end()) - lens.begin());
    for (q = 0; q < lens.size(); q++){
        C[q] = -lens[q];
    }
    build(1, 0, lens.size() - 1);
//    cout << lens.size() << " LENS" << endl;
    for (q = 0; q < lens.size(); q++){
        P[lens[q]] = q;
    }
    for (q = 0; q < n; q++){
        ll len = getlen(A[q]);
//        cout << "len " << small_from_big(len) << " " << A[q].c << endl;
        update(1, 0, lens.size() - 1, small_from_big(len), lens.size() - 1, A[q].c);
    }
    ll mxi = 0, mxj = 0, mx = -inf;
    for (auto p : M){
        vector <point> P = p.second;
        ll i = p.first;
        if (small_from_big(i) > lens.size()){
            continue;
        }
//        cout << "I SI " << i << " " << small_from_big(i) << endl;
        pll p1 = getmx(1, 0, lens.size() - 1, small_from_big(i), lens.size() - 1);
//        cout << p1.first << " " << p1.second << endl;
        ll dmx = p1.first + i, dmxj = big_from_small(p1.second);
//        cout << "DMX " << dmx << " " << dmxj << endl;
        if (dmx > mx){
            mx = dmx;
            mxi = i;
            mxj = dmxj;
        }
        for (q = 0; q < M[i].size(); q++){
//            cout << "Sminus " << small_from_big(getlen(M[i][q])) << " " << -M[i][q].c << endl;
            update(1, 0, lens.size() - 1, small_from_big(getlen(M[i][q])), lens.size() - 1, -M[i][q].c);
        }
//        cout << endl << endl;
    }
    if (mx <= 0){
        cout << 0 << endl;
        for (q = 0; 1; q++){
            if (S.find(mp(q, q)) == S.end()){
                cout << q << " " << q << " " << q << " " << q << endl;
                break;
            }
        }
        return 0;
    }
    cout << mx << endl;
    cout << mxi << " " << mxi << " " << mxj << " " << mxj << endl;
    return 0;
}
