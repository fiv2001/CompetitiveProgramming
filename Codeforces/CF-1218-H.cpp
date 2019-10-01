/*
    Let's build a directed graph on this sequence(edges from A[i] to i); We see that every vertex has one incoming edge; That means that
    our graph is a "sun" (a cycle with trees on it's vertexes). Let's count for every tree the amount of vertexes on the height of h
    using the small-to-large algorithm. While doing it we can find the answer for queries to vertexes from trees (not from cycles).
    Then for every cycle let's imagine a matrix B where B[i][j] is the amount of vertexes in the subtree of i-th vertex in this cycle
    on the height j; It's easy to see that the amount of non-zero elements in this matrix is not bigger than the size of this component
    and the answer for the query to the vertex on the cycle is a prefix sum on one of the diagonals of this matrix. Then we can build 
    prefix sums on all non-zero elements in every diagonal and find answer by making lower_bound on the prefix sums.
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

const ll maxn = 3e5;
const ll inf = 1e15;

struct query{
    ll i;
    ll v;
    ll m;
};

vector <ll> V[maxn];

ll A[maxn];

vector <vector <ll> > cycles;

vector <query> Z;

bool used[maxn];

vector <ll> cur_cyc;

ll in_cycle[maxn];

vector <ll> H[maxn];

vector <vector <vector <ll> > > B;

vector <vector <vector <pll> > > SB;

vector <ll> Q[maxn];

ll icyc[maxn];

ll ANS[maxn];

ll I[maxn];

bool found = 0;

void dfs0(ll v){
    ll q;
    if (found){
        return;
    }
    used[v] = 1;
    cur_cyc.pb(v);
    for (q = 0; q < V[v].size(); q++){
        if (used[V[v][q]]){
            cur_cyc.pb(V[v][q]);
            found = 1;
        }
        dfs0(V[v][q]);
    }
    if (found){
        return;
    }
    cur_cyc.pop_back();
}

void dfs1(ll v, ll p){
    ll q, w;
    ll mxsz = 0, mxi = v;
    for (q = 0; q < V[v].size(); q++){
        if (V[v][q] == p){
            continue;
        }
        if (in_cycle[V[v][q]] != -1){
            continue;
        }
        ll v1 = V[v][q];
        dfs1(v1, v);
        if (H[I[v1]].size() > mxsz){
            mxsz = H[I[v1]].size();
            mxi = I[v1];
        }
    }
    I[v] = mxi;
    for (q = 0; q < V[v].size(); q++){
        if (V[v][q] == p){
            continue;
        }
        if (in_cycle[V[v][q]] != -1){
            continue;
        }
        if (I[V[v][q]] == I[v]){
            continue;
        }
        ll v1 = V[v][q];
        for (w = 0; w < H[I[v1]].size(); w++){
            ll h = H[I[v1]].size() - w;
            ll i = H[I[v]].size() - h;
            H[I[v]][i] += H[I[v1]][w];
        }
    }
    H[I[v]].pb(1);
    for (q = 0; q < Q[v].size(); q++){
        ll m = Z[Q[v][q]].m;
        if (H[I[v]].size() - m - 1 >= 0){
            ANS[Q[v][q]] = H[I[v]][H[I[v]].size() - m - 1];
        }
        else{
            ANS[Q[v][q]] = 0;
        }
    }
}

ll n, m, k;

int main(){
    ll q, w, e, t, a, b, c;
    pyshnapyshnakaa;
    cin >> n;
    for (q = 0; q < n; q++){
        cin >> A[q];
        A[q]--;
        V[A[q]].pb(q);
//        cout << "EDGE " << A[q] << " " << q << endl;
    }
    for (q = 0; q < n; q++){
        in_cycle[q] = -1;
    }
    for (w = 0; w < n; w++){
        found = 0;
//        cout << "W " << w << endl;
        cur_cyc.clear();
        if (!used[w]){
            dfs0(w);
        }
        else{
            continue;
        }
//        cout << "W " << w << endl;
        if (cur_cyc.empty()){
            continue;
        }
        vector <ll> new_cyc;
        bool write = 0;
        for (q = 0; q < cur_cyc.size(); q++){
            if (write){
                icyc[cur_cyc[q]] = new_cyc.size();
                new_cyc.pb(cur_cyc[q]);
                in_cycle[cur_cyc[q]] = cycles.size();
                continue;
            }
            if (cur_cyc[q] == cur_cyc.back()){
                write = 1;
                continue;
            }
        }
//        cout << "NEW CYC " << endl;
        cycles.pb(new_cyc);
//        for (q = 0; q < new_cyc.size(); q++){
//            cout << new_cyc[q] << " ";
//        }
//        cout << endl;
    }
//    cout << cycles.size() << " CYC SZ" << endl;
    cin >> k;
    for (q = 0; q < k; q++){
        ll a, b;
        cin >> a >> b;
        query z;
        z.i = q;
        z.m = a;
        b--;
        z.v = b;
        Z.pb(z);
        if (in_cycle[b] == -1){
            Q[b].pb(q);
        }
    }
//    cout << endl << endl;
    for (q = 0; q < n; q++){
        if (in_cycle[q] != -1){
            dfs1(q, q);
        }
    }
    for (q = 0; q < cycles.size(); q++){
        for (w = 0; w < cycles[q].size(); w++){
            H[cycles[q][w]] = H[I[cycles[q][w]]];
        }
    }
//    for (q = 0; q < cycles.size(); q++){
//        cout << endl << endl << "Q " << q << endl;
//        for (w = 0; w < cycles[q].size(); w++){
//            cout << "V " << cycles[q][w] << endl;
//            for (e = 0; e < H[cycles[q][w]].size(); e++){
//                cout << H[cycles[q][w]][e] << " ";
//            }
//            cout << endl;
//        }
//    }
    B.resize(cycles.size());
    SB.resize(cycles.size());
    for (q = 0; q < cycles.size(); q++){
//        cout << "Q " << q << endl;
        B[q].resize(cycles[q].size());
        SB[q].resize(cycles[q].size());
        for (w = 0; w < cycles[q].size(); w++){
//            mx = max(mx, H[cycles[q][w]].size());
            vector <ll> heights = H[cycles[q][w]];
            reverse(heights.begin(), heights.end());
            B[q][w] = heights;
        }
        for (w = 0; w < cycles[q].size(); w++){
            for (e = 0; e < B[q][w].size(); e++){
                ll i = (e + w) % cycles[q].size();
                ll j = e;
//                cout << B[q][w][e] << " " << w << " " << e << " B w e" << endl;
//                cout << i << " " << j << " i j" << endl << endl;
                SB[q][i].pb(mp(j, B[q][w][e]));
            }
        }
//        cout << endl << endl;
        for (w = 0; w < cycles[q].size(); w++){
            sort(SB[q][w].begin(), SB[q][w].end());
//            cout << "W " << w << endl;
//            for (e = 0; e < SB[q][w].size(); e++){
//                cout << SB[q][w][e].first << " " << SB[q][w][e].second << endl;
//            }
            for (e = 1; e < SB[q][w].size(); e++){
//                cout << SB[q][w][e].first << " " << SB[q][w][e].second << endl;
                SB[q][w][e].second += SB[q][w][e - 1].second;
            }
        }
    }
    for (e = 0; e < k; e++){
        if (in_cycle[Z[e].v] != -1){
            ll c = in_cycle[Z[e].v];
//            cout << "NEW_QUERY " << e << " V " << Z[e].v << " m " << Z[e].m << endl;
//            cout << "C " << c << endl;
            ll ic = icyc[Z[e].v];
//            cout << "IC " << ic << endl;
            ll m = Z[e].m;
            ll i = (ic + m) % cycles[c].size();
//            cout << "I " << i << endl;
            ll j = m;
            pll p = mp(j, inf);
            ll i1 = upper_bound(SB[c][i].begin(), SB[c][i].end(), p) - SB[c][i].begin();
//            cout << endl << endl;
            if (i1 <= 0){
                continue;
            }
            ANS[e] = SB[c][i][i1 - 1].second;
        }
    }
    for (q = 0; q < k; q++){
        cout << ANS[q] << '\n';
    }
    return 0;
}
