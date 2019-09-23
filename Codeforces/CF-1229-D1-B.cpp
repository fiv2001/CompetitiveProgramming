/*
    While dfsing we keep the map of <number i, number of parents of current vertex with gcd on the way equal to i>; every time
    in dfs we iterate over the map and create a new map; This works in O(n * log(A[v])) because the size of map is never bigger
    than log(A[v]) because every time the gcd of numbers decreases, it decreases at least twice;
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

const ll maxn = 1e5 + 100;
const ll mod = 1e9 + 7;

ll A[maxn];

ll gcd(ll a, ll b){
    while (a != 0){
        b = b % a;
        swap(a, b);
    }
    return b;
}

vector <ll> V[maxn];

ll ans = 0;

void dfs(ll v, ll p, map <ll, ll> &M){
    ll q;
    map <ll, ll> M1;
    M1[A[v]]++;
    ans += A[v];
    for (auto p : M){
        ll g = gcd(p.first, A[v]);
        M1[g] += p.second;
        ans += g * p.second;
        ans %= mod;
    }
    for (q = 0; q < V[v].size(); q++){
        if (V[v][q] != p){
            dfs(V[v][q], v, M1);
        }
    }
}

ll n, m, k;

int main(){
    ll q, w, e, t, a, b, c;
    cin >> n;
    for (q = 0; q < n; q++){
        cin >> A[q];
    }
    for (q = 0; q < n - 1; q++){
        cin >> a >> b;
        a--; b--;
        V[a].pb(b);
        V[b].pb(a);
    }
    map <ll, ll> start;
    dfs(0, 0, start);
    cout << ans;
    return 0;
}
