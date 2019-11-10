/*
	We brute force, the number we will take. If we take it, then we know the next number we will have to take and so on. This way 
	we find all the cycles. Then our task is to find some non-intersecting cycles, so that every box exists in one cycle. We
	can do it in 3^n using dynamics over submasks. 
*/
#include <bits/stdc++.h>
#define pb push_back
#define pll pair <ll, ll>
#define MOMI using namespace std;
#define mp make_pair
#define pvb pair <vector <pll>, bool>
#define pyshnapyshnakaa ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
#pragma optimize("TKACHENKO-GORYACHENKO")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
 
typedef long long ll;
 
typedef long double ld;
 
using namespace std;
 
const ll maxn = 17;
const ll maxm = 6e3;
const ll st2n = 2e6;
 
ll n, m, k;
 
vector <ll> A[maxn];
 
vector <ll> cycles[maxn][maxm];
 
ll msk[maxn][maxm];
 
ll DX[maxn];
 
vector <pll> P[st2n]; 
 
ll st2[st2n];
 
bool pos[st2n];
 
bool used[maxn];
 
map <ll, ll> C;
 
ll start = 0, cnt_start = 0;
 
void dfs(ll v, ll c, ll i) {
	// if (start == 0 && i == 1)cout << "DFS " << v << " " << c << endl;
	if ((used[v] && v != start) || (used[v] && A[start][i] != c)) {
		msk[start][i] = -1;
		return;
	}
	used[v] = 1;
	if (v == start && cnt_start == 1) {
		// cycles[start][i].pb(c);
		if (P[msk[start][i]].size() != 0) {
			return;
		}
		ll w;
		for (w = 0; w < cycles[start][i].size(); w++) {
			ll i1 = (w - 1 + cycles[start][i].size()) % cycles[start][i].size();
			// cout << ans.first[q] << " " << C[ans.first[i1]] + 1 << endl;
			P[msk[start][i]].pb(mp(cycles[start][i][w], C[cycles[start][i][i1]] + 1));
		}
		// P[msk[start][i]] = (cycles[start][i];
		return;
	}
	if (v == start) {
		cnt_start = 1;
	}
	msk[start][i] |= st2[v];
	cycles[start][i].pb(c);
	ll nc = DX[v] + c;
	// if (start == 0 && i == 1)cout << "nc " << nc << endl;
	if (C.find(nc) == C.end()) {
		msk[start][i] = -1;
		return;
	}
	ll v1 = C[nc];
	dfs(v1, nc, i);
}
 
inline vector <pll> mrg(vector <pll> A, vector <pll> B) {
	vector <pll> ANS = A;
	for (ll q = 0; q < B.size(); q++) {
		ANS.pb(B[q]);
	}
	return ANS;
}
 
map <ll, pvb> DP;
 
pvb can(ll mskask) {
	ll q, w;
	if (DP.find(mskask) != DP.end()) {
		return DP[mskask];
	}
	// cout << mskask << endl;
	if (msk == 0) {
		vector <pll> E;
		return mp(E, 1);
	}
	if (P[mskask].size() != 0) {
		return mp(P[mskask], 1);
	} 
	vector <ll> B;
	for (q = mskask - 1; q > 0; q = ((q - 1) & mskask)) {
		// cout << mskask << " " << q << '\n';
		// for (w = 0; w < A[q].size(); w++) {
			ll nmsk = q;
			if (nmsk == -1) {
				continue;
			}
			if (P[nmsk].size() == 0) {
				continue;
			}
			// if ((nmsk | mskask) == mskask) {
			// auto p1 = can(nmsk);
			auto p = can(mskask - nmsk);
			if (p.second) {
				DP[mskask] = mp(mrg(p.first, P[nmsk]), 1);
				return DP[mskask];
			}
			// }
		// }
	}
	// cout << endl;
	vector <pll> E;
	DP[mskask] = mp(E, 0);
	return DP[mskask];
}
 
bool cmp(pll a, pll b) {
	return C[a.first] < C[b.first];
}
 
signed main() {
	ll q, w, e, a, b;
	pyshnapyshnakaa;
	cin >> n;
	st2[0] = 1;
	for (q = 1; q < 50; q++) {
		st2[q] = st2[q - 1] * 2;
	}
	ll sum = 0;
	for (q = 0; q < n; q++) {
		cin >> m;
		ll sum1 = 0;
		for (w = 0; w < m; w++) {
			cin >> a;
			C[a] = q;
			A[q].pb(a);
			sum += a;
		}
	}
	if (sum % n != 0) {
		cout << "No";
		return 0;
	}
	for (q = 0; q < n; q++) {
		DX[q] = sum / n;
		for (w = 0; w < A[q].size(); w++) {
			DX[q] -= A[q][w];
		}
		// cout << "DX " << q << " " << DX[q] << endl;
	}
	// cout << endl;
	for (q = 0; q < n; q++) {
		// cycles[q].resize(A[q].size());
		for (w = 0; w < A[q].size(); w++) {
			for (e = 0; e < n; e++) {
				used[e] = 0;
			}
			start = q;
			cnt_start = 0;
			dfs(q, A[q][w], w);
			// cout << msk[q][w] << " MSK" << endl;
		}
	}
	// cout << " DFSED" << endl;
	pvb ans = can(st2[n] - 1);
	// cout << "UMOM" << endl;
	if (ans.second == 0) {
		cout << "No";
		return 0;
	}
	sort(ans.first.begin(), ans.first.end(), cmp);
	cout << "Yes" << endl;
	for (q = 0; q < ans.first.size(); q++) {
		cout << ans.first[q].first << " " << ans.first[q].second << endl;
	}
	return 0;
}
