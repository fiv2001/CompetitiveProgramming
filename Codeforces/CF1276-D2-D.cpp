/*
    Let dp[i][j] be the biggest amount of significance we can get if we have j soldiers on the castle i. After that we can say that 
    we will go back only from the furtherst portal, for every castle we delete all portals except the longest one. After that 
    it's easy to recompute the dp.
*/
#include <bits/stdc++.h>
#define pb push_back
#define pll pair <ll, ll>
#define mp make_pair
#define pyshnapyshnakaa ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
#pragma optimize("TKACHENKO-GORYACHENKO")
#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
#define psl pair <string, ll>
#define pls pair <ll, string>
 
typedef long long ll;
 
typedef long double ld;
 
using namespace std;
 
const ll maxn = 5e3 + 100;
const ll inf = 1e15;
 
ll n, m, k;
 
ll A[maxn];
 
ll B[maxn];
 
ll C[maxn];
 
vector <ll> V[maxn];
 
ll D[maxn + 100][maxn + 100];
 
ll MX[maxn];
 
bool cmp(ll i, ll j) {
	return C[i] > C[j];
}
 
int main()
{
	ll q, w, e, a, b;
	pyshnapyshnakaa;
	cin >> n >> m >> k;
	for (q = 0; q < n; q++) {
		cin >> A[q] >> B[q] >> C[q];
		MX[q] = q;
	}
	for (q = 0; q < m; q++) {
		cin >> a >> b;
		a--; b--;
		MX[b] = max(MX[b], a);
		// V[a].pb(b);
	}
	for (q = 0; q < n; q++) {
		// V[q].pb(q);
		V[MX[q]].pb(q);
	}
	for (q = 0; q < n; q++) {
		sort(V[q].begin(), V[q].end(), cmp);
	}
	for (q = 0; q < maxn; q++) {
		for (w = 0; w < maxn; w++) {
			D[q][w] = -inf;
		}
	}
	D[0][k] = 0;
	for (q = 0; q <= n; q++) {
		if (q != 0) {
			for (w = 0; w < maxn; w++) {
				// if (D[q][w] >= 0)cout << "D " << q << " " << w << " " << D[q][w] << endl;
				ll s = 0;
				for (e = 0; e < V[q - 1].size(); e++) {
					// cout << "ds " << C[V[q][e]] << endl;
					s += C[V[q - 1][e]];
					if (w - e - 1 >= 0) {
						D[q][w - e - 1] = max(D[q][w - e - 1], D[q][w] + s);
					}
				}
			}
		}
		if (q == n) {
			break;
		}
		for (w = maxn - 1; w >= 0; w--) {
			if (w + B[q] < maxn && w >= A[q]) {
				// if (D[q][w] >= 0)cout << "per " << q + 1 << " " << w + B[q] << endl;
				D[q + 1][w + B[q]] = max(D[q + 1][w + B[q]], D[q][w]);
			}
		}
	} 
	ll ans = -1;
	for (w = maxn - 1; w >= 0; w--) {
		ans = max(ans, D[n][w]);
	}
	cout << ans;
	return 0;
}
