/*
  We dfs our tree and while dfsing we maintain for each j the amount of paths from vertex v to vertexes from it's subtree which 
  length has remainder j (mod k); Also we maintain the same thing but for paths from vertex v to vertexes not from the subtree of v;
  then using it we can maintain the answer for vertex v: sum of all other vertexes v1 the number of jumps a bear has to jump to get from
  vertex v to vertex v1; then we take the sum of it for all vertices and divide it by 2 because we counted every pair of vertices 2 times.
*/
#include <bits/stdc++.h>
#include <complex>
#define pb push_back
#define pll pair <ll, ll>
#define MOMI using namespace std;
#define mp make_pair
#define pyshnapyshnakaa ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
//#pragma optimize("TKACHENKO-GORYACHENKO")
#pragma GCC optimize("O3")

//#pragma GCC optimize("unroll-loops")
//#define double long double

typedef long long ll;

typedef long double ld;

using namespace std;

const ll maxn = 3e5;
const ll maxk = 6;

ll n, m, k;

ll D[maxn][maxk];

vector <ll> V[maxn];

ll H[maxn];

ll ans = 0;

void dfs(ll v, ll p){
    ll q, w;
    D[v][0]++;
    if (v != 0){
        H[v] = H[p] + 1;
    }
    for (q = 0; q < V[v].size(); q++){
        if (V[v][q] == p){
            continue;
        }
        dfs(V[v][q], v);
        for (w = 0; w < k; w++){
            D[v][w] += D[V[v][q]][(w - 1 + k) % k];
        }
    }
}

void dfs1(ll v, ll p, ll curans, vector <ll> down, vector <ll> up){
    ll q, w;
//    vector <ll> DS;
//    DS.resize(maxk);
//    cout << endl << v << " " << curans << endl;
//    for (q = 0; q < k; q++){
//        cout << down[q] << " ";
//    }
//    cout << endl;
//    for (q = 0; q < k; q++){
//        cout << up[q] << " ";
//    }
//    cout << endl;
//    for (q = 0; q < k; q++){
//        cout << D[v][q] << " ";
//    }
//    cout << endl;
    ans += curans;
    for (q = 0; q < V[v].size(); q++){
        if (V[v][q] == p){
            continue;
        }
        ll v1 = V[v][q];
        vector <ll> up2, down2;
        up2 = up; down2 = down;
        for (w = 0; w < k; w++){
            down2[w] -= (D[v][w] - D[v1][(w - 1 + k) % k]);
            up2[w] += (D[v][w] - D[v1][(w - 1 + k) % k]);
        }
        vector <ll> up1, down1;
        up1.resize(k); down1.resize(k);
        for (w = 0; w < k; w++){
            up1[w] = up2[(w - 1 + k) % k];
            down1[w] = down2[(w + 1) % k];
        }
        ll curans1 = curans + (up1[1 % k] - down1[0]);
        dfs1(V[v][q], v, curans1, down1, up1);
    }
}

int main(){
    ll q, w, e, t, a, b, c;
    cin >> n >> k;
    for (q = 0; q < n - 1; q++){
        cin >> a >> b;
        a--; b--;
        V[a].pb(b); V[b].pb(a);
    }
    dfs(0, 0);
    ll curans = 0;
    vector <ll> down, up;
    down.resize(k);
    up.resize(k);
    for (q = 0; q < k; q++){
        up[q] = 0;
        down[q] = D[0][q];
    }
    for (q = 0; q < n; q++){
        curans += (H[q] + k - 1) / k;
    }
    dfs1(0, 0, curans, down, up);
    cout << ans / 2;
    return 0;
}
