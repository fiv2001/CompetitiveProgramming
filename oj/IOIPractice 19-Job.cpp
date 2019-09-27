/*
    If the tree is a bush (every vertex is a son of 0) we would sort the vertex by (d[v] / u[v]) and visit them in this order. So we 
    only have to take into the account the parentnesses. So let's maintain in sets (using small-to-large algorithm) the vertexes for
    every subtree, that we haven't merged with other vertexes. And we will merge the vertexes this way: while a vertex has any vertex 
    in it's subtree which is better that it, we will merge this vertex with that better vertex. After that we can ignore the 
    parentnesses.
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

ll n, m, k;

ll P[maxn];

ll U[maxn];

ll D[maxn];

ll ans = 0;

bool BAD[maxn];

vector <ll> V[maxn];

pll ANS[maxn];

bool cmp(pll a, pll b){
    return a.first * b.second < b.first * a.second;
}

struct cmp1{
    bool operator ()(ll a1, ll b1){
        pll a = ANS[a1], b = ANS[b1];
        if (a.first * b.second == b.first * a.second){
            return a1 < b1;
        }
        return a.first * b.second < b.first * a.second;
    }
};

bool cmp2(ll a, ll b){
    return cmp(ANS[a], ANS[b]);
}

ll I[maxn];

set <ll, cmp1> S[maxn];

void dfs(ll v, ll p){
    ll q;
    I[v] = v;
    ll mx = 0;
    for (q = 0; q < V[v].size(); q++){
        if (V[v][q] == p){
            continue;
        }
        dfs(V[v][q], v);
        ll i = I[V[v][q]];
        if (S[i].size() > mx){
            mx = S[i].size();
            I[v] = i;
        }
    }
//    cout << "V " << v << " " << I[v] << endl;
    for (q = 0; q < V[v].size(); q++){
        if (V[v][q] == p){
            continue;
        }
        if (I[V[v][q]] == I[v]){
//            cout << "CONTINUE " << V[v][q] << endl;
            continue;
        }
        ll i = I[V[v][q]];
        for (auto el : S[i]){
//            cout << S[I[v]].size() << " SIZE 1" << endl;
            S[I[v]].insert(el);
//            cout << "INSERTING " << el << endl;
//            cout << S[I[v]].size() << " SIZE 2" << endl;
        }
    }
//    cout << "SZ " << S[I[v]].size() << endl;
//    cout << "FIRST " << *(S[I[v]].begin()) << endl;
    ANS[v] = mp(D[v], U[v]);
    vector <ll> merged;
    ll t = D[v], st = D[v];
    while (!S[I[v]].empty()){
        ll i = *(S[I[v]].begin());
//        cout << "I " << i << endl;
        if (cmp2(i, v)){
            merged.pb(i);
            st += ANS[i].first;
            S[I[v]].erase(S[I[v]].begin());
            ANS[v].first += ANS[i].first;
            ANS[v].second += ANS[i].second;
        }
        else{
//            cout << "BREAKING " << i << " " << v << endl;
            break;
        }
    }
    ans -= (st - t) * (U[v]);
//    cout << "DANS " << (st - t) * (U[v]) << " " << st << " " << t << " " << v << endl;
    for (q = 0; q < merged.size(); q++){
        ll i = merged[q];
        BAD[i] = 1;
        t += ANS[i].first;
        ans -= ANS[i].second * (st - t);
//        cout << "DANS1 " << (st - t) * (ANS[i].second) << endl;
    }
    S[I[v]].insert(v);
}

ll scheduling_cost(vector <int> p, vector <int> u, vector <int> d){
    n = p.size();
    bool is_bamboo = 1;
    ll q, w, e, a, b;
    for (q = 0; q < n; q++){
        P[q] = p[q];
        U[q] = u[q];
        D[q] = d[q];
        if (p[q] != q - 1){
            is_bamboo = 0;
        }
        if (p[q] != -1){
            V[p[q]].pb(q);
            V[q].pb(p[q]);
        }
    }
    dfs(0, 0);
    vector <ll> ALL;
    for (q = 0; q < n; q++){
        ALL.pb(q);
    }
    sort(ALL.begin(), ALL.end(), cmp2);
    ll t = 0;
//    cout << "ANS B4 " << ans << endl;
    for (q = 0; q < ALL.size(); q++){
        if (BAD[ALL[q]]){
            continue;
        }
//        cout << "GOOD " << ALL[q] << " " << ANS[ALL[q]].first << " " << ANS[ALL[q]].second << endl;
        t += ANS[ALL[q]].first;
        ans += ANS[ALL[q]].second * t;
    }
    return ans;
}

int main(){
    ll q, w, e, t, a, b, c;
    cin >> n;
    vector <int> p(n), u(n), d(n);
    for (q = 0; q < n; q++){
        cin >> p[q];
    }
    for (q = 0; q < n; q++){
        cin >> u[q];
    }
    for (q = 0; q < n; q++){
        cin >> d[q];
    }
    cout << scheduling_cost(p, u, d);
    return 0;
}
