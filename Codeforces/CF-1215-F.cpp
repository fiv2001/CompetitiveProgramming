/*
    We make an implication graph on radiostations and vertexes of the type (the chosen f is not bigger than x); then we do a 2-sat
    on this graph.
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

const ll maxn = 2e6;
const ll inf = 1e15;

ll n, m, k, mx;

vector <ll> V[maxn];

void add_edge(ll x, bool isx, ll y, bool isy){
    ll i = 2 * x + isx;
    ll j = 2 * y + isy;
    V[i].pb(j);
}

ll geti(ll x, bool isx){
    return 2 * x + isx;
}

ll getj(ll x, bool isx){
    return 2 * k + 2 * x + isx;
}

ll getnx(ll i){
    if (i % 2 == 0){
        return i + 1;
    }
    return i - 1;
}

bool used[maxn];

vector <ll> P;

ll RP[maxn];

ll C[maxn];

void dfs(ll v){
    used[v] = 1;
    ll q;
    for (q = 0; q < V[v].size(); q++){
        if (!used[V[v][q]]){
            dfs(V[v][q]);
        }
    }
    P.pb(v);
}

ll color = 1;

void dfs1(ll v){
    used[v] = 1;
    C[v] = color;
    ll q;
    for (q = 0; q < V[v].size(); q++){
        if (!used[V[v][q]]){
            dfs1(V[v][q]);
        }
    }
}

vector <ll> ANS;

ll ans = 0;

int main(){
    ll q, w, e, t, a, b, c;
    cin >> n >> k >> mx >> m;
    for (q = 0; q < n; q++){
        cin >> a >> b;
        a--; b--;
        add_edge(a, 0, b, 1);
        add_edge(b, 0, a, 1);
    }
    for (q = 0; q < k; q++){
        cin >> a >> b;
        ll j = getj(b, 0);
        ll i = geti(q, 0);
        V[j].pb(i);
        ll j1 = getj(a - 1, 1);
        V[j1].pb(i);
        j = getj(b, 1);
        i = geti(q, 1);
        V[i].pb(j);
        j1 = getj(a - 1, 0);
        V[i].pb(j1);
//        cout << "j1 j i " << j1 << " " << j << " " << i << endl;
    }
    for (q = 0; q < m; q++){
        cin >> a >> b;
        a--; b--;
        add_edge(a, 1, b, 0);
        add_edge(b, 1, a, 0);
    }
    for (q = 0; q <= mx; q++){
        if (q != 0){
            ll j = getj(q, 1);
            ll j1 = getj(q - 1, 1);
            V[j1].pb(j);
        }
        if (q != mx){
            ll j = getj(q, 0);
            ll j1 = getj(q + 1, 0);
            V[j1].pb(j);
        }
    }
    ll nv = 2 * (k + mx + 10);
    for (q = 0; q < nv; q++){
        if (!used[q]){
            dfs(q);
        }
    }
//    for (q = 0; q < P.size(); q++){
//        cout << P[q] << " ";
//    }
//    cout << endl;
    for (q = 0; q < nv; q++){
        used[q] = 0;
    }
    for (q = 0; q < nv; q++){
        if (!used[P[q]]){
            dfs1(P[q]);
            color++;
        }
    }
//    cout << nv << endl;
    for (q = 0; q < nv; q++){
        if (C[q] == C[getnx(q)]){
            cout << -1;
            return 0;
        }
    }
    ll mn = inf;
    for (q = 0; q < nv; q++){
        RP[P[q]] = q;
    }
    for (q = 0; q < nv; q++){
        if (!(RP[q] < RP[getnx(q)])){
            continue;
        }
        if (q < 2 * k){
            if (q % 2 == 1){
                ll i = (q - 1) / 2;
                ANS.pb(i);
            }
        }
        else{
            if (q % 2 == 1){
//                cout << q << " " << endl;
                mn = min(mn, (q - 2 * k - 1) / 2);
            }
        }
    }
    cout << ANS.size() << " " << mn << endl;
    for (q = 0; q < ANS.size(); q++){
        cout << ANS[q] + 1 << " ";
    }
    return 0;
}
