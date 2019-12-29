/*
      The consequence of vertexes on our way always leads us to the vertex with biggest number. Thus we can find numbers of all
      the vertexes on our way. 
*/
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
#define pllll pair <pair <ll, ll>, pair <ll, ll> >
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

typedef long long ll;

typedef long double ld;

using namespace std;

const ll maxn = 1e6;

ll n, m, k;

ll A[maxn];

vector <ll> V[maxn];

bool used[maxn];

// ll I[maxn];

// void dfs(ll v) {
// 	ll q;
// 	for (auto v1 : V[v]) {
// 		dfs(v1);
// 	}
// }

int main()
{
	ll q, w, e, a, b, c;
	pyshnapyshnakaa;
	string s;
	cin >> n;
	set <ll> S;
	for (q = 0; q <  n - 1; q++) {
		cin >> A[q];
		S.insert(-q);
		A[q]--;
	}
	S.insert(-n + 1);
	ll root = A[0];
	used[root] = 1;
	ll lst = root;
	S.erase(-root);
	for (q = 1; q < n; q++) {
		ll nxt = A[q];
		// cout << "DEBUG " << lst + 1 << " " << nxt + 1 << endl;
		if (used[nxt] || q == n - 1) {
			ll mx = -*(S.begin());
			V[lst].pb(mx);
			used[mx] = 1;
			// cout << "mx " << mx + 1 << endl;
			S.erase(S.begin());
			lst = nxt;
		}
		else {
			V[lst].pb(nxt);
			S.erase(-nxt);
			used[nxt] = 1;
			lst = nxt;
		}
	}
	cout << root + 1 << endl;
	for (q = 0; q < n; q++) {
		for (w = 0; w < V[q].size(); w++) {
			cout << q + 1 << " " << V[q][w] + 1 << endl;
		}
	}
	// dfs(root);
 	return 0;
}
