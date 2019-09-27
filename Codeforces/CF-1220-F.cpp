/*
    We do a binary search about where the minimmum element is. If the height of the left subtree is bigger then the height of the right
    subtree then it means that we shouldn't put the minimum element to the left from where we check now, because it's not going to
    decrease the height of left subtree.
    We find the heights of left and right parts by stupidly simulating the tree building(I used segment tree for finding the minimum
    on the segment, so this solution is O(n * log(n) ^ 2), but if you use sparse table and don't build them every time(it's possible, 
    because the query on the shifted array is equal to 1-2 queries on the main array)).
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

const ll maxn = 2e5 + 100;
const ll inf = 1e15;

ll n, m, k;

ll V[4 * maxn];

vector <ll> A;

vector <ll> A1;

ll C[maxn];

void build(ll v, ll tl, ll tr){
    if (tl == tr){
        V[v] = A[tl];
        return;
    }
    ll tm = (tl + tr) / 2;
    build(2 * v, tl, tm);
    build(2 * v + 1, tm + 1, tr);
    V[v] = min(V[2 * v], V[2 * v + 1]);
}

ll getmn(ll v, ll tl, ll tr, ll l, ll r){
    if (l > tr || tl > r || l > r){
        return inf;
    }
    if (tl == l && tr == r){
        return V[v];
    }
    ll tm = (tl + tr) / 2;
    ll mn1 = getmn(2 * v, tl, tm, l, min(r, tm));
    ll mn2 = getmn(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
    return min(mn1, mn2);
}

ll root;

ll hl, hr;

ll C1[maxn];

void bld(ll p, ll l, ll r, bool is_left_part, ll h){
    if (l > r){
        return;
    }
    ll mn = getmn(1, 0, n - 1, l, r);
//    cout << l << " " << r << " " << mn << endl;
    ll mni = C1[mn];
//    cout << mni << endl;
    if (is_left_part){
//        cout << "mn " << mn << endl;
        hl = max(hl, h);
    }
    else{
        hr = max(hr, h);
    }
    bool is_left_part1 = is_left_part, is_left_part2 = is_left_part;
    if (p == -1){
        is_left_part1 = 1;
        is_left_part2 = 0;
    }
    bld(mn, l, mni - 1, is_left_part1, h + 1);
    bld(mn, mni + 1, r, is_left_part2, h + 1);
}

ll ans = inf, ansi = 0;

void shift(ll i){
//    cout << "I " << i << endl;
    reverse(A.begin(), A.begin() + n - i);
    reverse(A.begin() + n - i, A.end());
    reverse(A.begin(), A.end());
//    for (ll q = 0; q < A.size(); q++){
//        cout << A[q] << " ";
//    }
//    cout << endl;
}

void make_tree(ll i){
//    cout << "MAKE " << i << endl;
    hl = hr = 0;
    shift((i - C[0] + n) % n);
    for (ll q = 0; q < n; q++){
        C1[A[q]] = q;
    }
    build(1, 0, n - 1);
//    cout << "DO " << endl;
    bld(-1, 0, n - 1, 0, 0);
//    cout << "DG " << endl;
//    cout << max(hl, hr) << " H" << endl;
    if (max(hl, hr) < ans){
        ansi = (i - C[0] + n) % n;
    }
    ans = min(ans, max(hl, hr));
    A = A1;
}

int main(){
    ll q, w, e, t, a, b, c;
    cin >> n;
    A.resize(n);
    for (q = 0; q < n; q++){
        cin >> A[q];
        A[q]--;
        C[A[q]] = q;
    }
    A1 = A;
    ll L = 0, R = n, M;
    while (R - L > 1){
        M = (L + R) / 2;
        make_tree(M);
//        cout << hl << " " << hr << endl;
        if (hl > hr){
            R = M;
        }
        else{
            L = M;
        }
    }
//    for (q = 0; q < n; q++){
//        make_tree(q);
//    }
    make_tree(L);
    cout << ans + 1 << " " << (n - ansi) % n << endl;
    return 0;
}
