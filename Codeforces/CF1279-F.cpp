/*
    We do binary search on the cost of one operation. We want the amount of operations we are doing be the biggest less then k. 
    For cost c we count the dp[i] - the minimal cost we can have on index i(we pay c for every operation and 1 for every remaining bad
    letter in array). Then we say that we can buy all k operations for this cost and find the amount of remaining bad letters in handle.
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

typedef long long ll;

typedef long double ld;

using namespace std;

const ll maxn = 1e6 + 10;

ll n, k, m;

pll D[maxn];

bool upper(ll x) {
	return x >= 'A' && x <= 'Z';
}

pll solve(vector <ll> A, ll c) {
	ll q, w;
	D[0] = mp(0, 0);
	for (q = 1; q <= n; q++) {
		if (q - m < 0) {
			D[q] = min(mp(D[q - 1].first + A[q - 1], D[q - 1].second), 
			mp(c, (ll)1));
			continue;
		}
		D[q] = min(mp(D[q - 1].first + A[q - 1], D[q - 1].second), 
			mp(D[q - m].first + c, D[q - m].second + 1));
		// cout << q << " " << D[q].first << " " << D[q].second << endl;
	}
	return D[n];
}

ll answer(vector <ll> A) {
	ll R = n + 1, L = -1, M;
	while (R - L > 1) {
		M = (L + R) / 2;
		pll ans = solve(A, M);
		// cout << ans.first << " " << ans.second << " " << M << " M" << endl;
		if (ans.second <= k) {
			R = M;
		}
		else {
			L = M;
		}
	}
	// cout << L << " " << R << " L R " << endl;
	pll ansl = solve(A, L), ansr = solve(A, R);
	ll al = ansl.first - ansl.second * L, ar = ansr.first - k * R;
	// cout <<al << " " << ar << " ANSWERS" << endl << endl;
	return ar;
}

int main()
{
	ll q, w, e, a, b, c;
	pyshnapyshnakaa;
	cin >> n >> k >> m;
	string s;
	cin >> s;
	vector <ll> A(n);
	for (q = 0; q < n; q++) {
		A[q] = upper(s[q]);
	}
	ll ans = maxn;
	ans = min(ans, answer(A));
	for (q = 0; q < n; q++) {
		A[q] = 1 - A[q];
	}
	ans = min(ans, answer(A));
	cout << ans;
 	return 0;
}
