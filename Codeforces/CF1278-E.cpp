#include <bits/stdc++.h>
#define pb push_back
#define pll pair <ll, ll>
#define mp make_pair
#define pyshnapyshnakaa ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
#pragma optimize("TKACHENKO-GORYACHENKO")
#define psl pair <string, ll>
#define pls pair <ll, string>
#pragma GCC optimize("O3")
#define plll pair <pair <ll, ll>, ll>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
 
typedef long long ll;
 
typedef long double ld;
 
using namespace std;
 
const ll maxn = 1e6;
 
ll n, m, k;
 
vector <ll> V[maxn];
 
ll L[maxn];
 
ll R[maxn];
 
ll uk;
 
void dfs(ll v, ll p) {
	ll q;
	ll cnt = 0;
	for (q = 0; q < V[v].size(); q++) {
		if (V[v][q] == p) {
			continue;
		}
		cnt++;
	}
	// cout << v << " " << uk << " DEBUG" << endl;
	R[v] = uk + cnt;
	uk = R[v] + 1;
	ll x = 0;
	for (q = 0; q < V[v].size(); q++) {
		if (V[v][q] == p) {
			continue;
		}
		// cout << "V[v][q] " << V[v][q] << " " << R[v] << " " << v << " " << q<< endl;
		L[V[v][q]] = R[v] - x - 1;
		x++;
		dfs(V[v][q], v);
	}
}
 
int main()
{
	ll q, w, e, a, b, c;
	pyshnapyshnakaa;
	string s;
	cin >> n;
	for (q = 0; q < n - 1; q++) {
		cin >> a >> b;
		a--; b--;
		V[a].pb(b); V[b].pb(a);
	}
	L[0] = 1;
	uk = 2;
	dfs(0, 0);
	for (q = 0; q < n; q++) {
		cout << L[q] << " " << R[q] << '\n';
	}
 	return 0;
}
