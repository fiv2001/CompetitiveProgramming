/*
    For every vertex v we count for every height h the most-left and the most-right character in the subtree of v on the height h. We can
    do it fast using small-to-large algorithm.
*/
#include <bits/stdc++.h>
#define pb push_back
#define pll pair <ll, ll>
#define MOMI using namespace std;
#define mp make_pair
#define pyshnapyshnakaa ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
#pragma optimize("TKACHENKO-GORYACHENKO")
#pragma GCC optimize("O3")
 
//#pragma GCC optimize("unroll-loops")
 
typedef int ll;
 
typedef long double ld;

using namespace std;

const ll inf = 1e9;
const ll maxn = 3e5 + 10;

ll n, m, k;

// string S[maxn];

int S[maxn];

vector <int> V[maxn];

struct seg {
	ll l;
	ll r;
};

ll getmid(seg s) {
	// cout << s.l << " " << s.r << " " << s.l + ()
	return s.l + (s.r - s.l) / 2;
}

seg getseg(ll m, ll len) { // len of string
	seg ans;
	if (len % 2 == 0) {
		ans.l = m - (len / 2 - 1);
		ans.r = m + (len / 2);
	}
	else {
		ans.l = m - (len / 2);
		ans.r = m + (len / 2);
	}
	return ans;
}

long long allans = 0;

ll I[maxn];

vector <pll> H[maxn];

ll D[maxn];

int P[maxn];

pll get(ll i, ll j) {
	pll ans = H[i][j];
	ans.first -= D[i];
	ans.second += D[i];
	return ans;
}

void dfs(ll v, ll p) {
	pll ans;
	ans = mp((S[v] + 1) / 2, (S[v] + 2) / 2);
	I[v] = v;
	if (V[v].size() == 0) {
		H[v].pb(ans);
	}
	else {
		allans++;
	}
	if (V[v].size() == 1) {
		allans++;
		dfs(V[v][0], v);
		I[v] = I[V[v][0]];
		ans.first += D[I[v]];
		ans.second -= D[I[v]];
		H[I[v]].pb(ans);
	}
	if (V[v].size() == 2) {
		ll v1 = V[v][0], v2 = V[v][1];
		dfs(v1, v);
		dfs(v2, v);
		// cout << "DIFFICULT " << v << endl;
		if (H[I[v1]].size() >= H[I[v2]].size()) {
			I[v] = I[v1];
			ll mid = 0;
			for (ll q = 0; q < H[I[v2]].size(); q++) {
				ll h = H[I[v2]].size() - q - 1;
				ll j = H[I[v]].size() - h - 1;
				pll l = get(I[v], j), r = get(I[v2], q);
				ll dmid = l.second + r.first + 2;
				mid = max(mid, dmid);
			}
			if (mid % 2 == 0) {
				mid++;
			}
			// D[I[v]] -= mid / 2;
			ll dd = D[I[v]] - mid / 2;
			// cout << "DD " << dd << endl; 
			for (ll q = 0; q < H[I[v2]].size(); q++) {
				ll h = H[I[v2]].size() - q - 1;
				ll j = H[I[v]].size() - h - 1;
				pll l = get(I[v], j), r = get(I[v2], q);
				// cout << "MRG " << l.first << " " << l.second << " " <<
				// r.first << " " << r.second << endl;
				H[I[v]][j] = mp(l.first + mid / 2 + dd,
					r.second + mid / 2 - dd);
				// cout << "DEBUG " << v << " V " <<  
				// cout << "RES " << H[I[v]][j].first << " " << H[I[v]][j].second << endl;
				// cout << endl;
			}	
			D[I[v]] = dd;
			ans.first += dd;
			ans.second -= dd;
			// cout << "MID " << mid << " V " << v << endl << endl << endl;;
			allans += mid;
		}
		else {
			I[v] = I[v2];
			ll mid = 0;
			for (ll q = 0; q < H[I[v1]].size(); q++) {
				ll h = H[I[v1]].size() - q - 1;
				ll j = H[I[v]].size() - h - 1;
				pll l = get(I[v1], q), r = get(I[v], j);
				ll dmid = l.second + r.first + 2;
				mid = max(mid, dmid);
			}
			if (mid % 2 == 0) {
				mid++;
			}
			// D[I[v]] += mid / 2;
			ll dd = D[I[v]] + mid / 2;
			for (ll q = 0; q < H[I[v1]].size(); q++) {
				ll h = H[I[v1]].size() - q - 1;
				ll j = H[I[v]].size() - h - 1;
				pll l = get(I[v1], q), r = get(I[v], j);
				H[I[v]][j] = mp(l.first + mid / 2 + dd, 
					r.second + mid / 2 - dd);
			}
			D[I[v]] = dd;
			ans.first += dd;
			ans.second -= dd;
			// cout << "MID " << mid << " V " << v << endl << endl;
			allans += mid;
		}
		H[I[v]].pb(ans);
		// cout << "DEBUG " << v << endl;
		// for (ll q = 0; q < H[I[v]].size(); q++) {
		// 	pll c = get(I[v], q);
		// 	// cout << c.first << " " << c.second << endl;
		// }
	}
}

signed main() {
	ll x;
	// string s = "  o------------";
	// cout << s.length() << endl;
	ll q, w, e, a, b, c;
	cin >> n;
	allans += n * 6 + (n - 1);
	for (q = 0; q < n; q++) {
		string s;
		cin >> s;
		S[q] = s.length();
		allans += S[q] * 3;
		if (q != 0) {
			cin >> x;
			x--;
			P[q] = x;
			V[x].pb(q);
		}
	}
	dfs(0, 0);
	cout << allans;
	return 0;
}
