/*
    We count the dp[i][j] - the number of good permutations of length i with first number j. To find the answer for a query we use this dp
    and the usual algorithm for restoring k-th lexicographical something. We also need to find the kth cycle, to do it we also use
    this algorithm.
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

const ll maxn = 1e2;
const ll inf = 2e18;
const ll maxk = 1e18;
const ll mod = 998244353;

ll n, m, k;

ll D[maxn][maxn];

ll S[maxn];

ll F[maxn];

ll C[maxn];

ll getf(ll x) {
	if (x >= 2) {
		return F[x];
	}
	return 1;
}

vector <ll> kth_cycle(ll x, ll k) {
	ll q, w;
	k--;
	vector <ll> ANS(x);
	vector <ll> RANS(x);
	for (q = 0; q < x; q++) {
		ANS[q] = -1;
		RANS[q] = -1;
	}
	ANS[0] = x - 1;
	RANS[x - 1] = 0;
	ll k1 = k;
	for (q = 1; q < x; q++) {
		ll fact = getf(x - q - 2);
		ll c = k1 / fact;
		k1 %= fact; 
		vector <bool> ban(x);
		ll i = q;
		while (i != -1) {
			if (q == x - 1) {
				if (RANS[i] == -1) {
					ANS[x - 1] = i;
					break;
				}
			}
			ban[i] = 1;
			i = RANS[i];
		}
		for (w = 0; w < q; w++) {
			ban[ANS[w]] = 1;
		}
		ll cnt = 0;
		for (w = 0; w < x; w++) {
			if (!ban[w]) {
				if (cnt == c) {
					ANS[q] = w;
					RANS[w] = q;
					break;
				}
				cnt++;
			}
		}
	}
	return ANS;
}

int main()
{
	ll q, w, e, a, b, c;
	pyshnapyshnakaa;
	D[0][0] = 1;
	S[0] = 1;
	F[0] = 1;
	for (q = 1; q <= 50; q++) {
		if (F[q] >= inf * 1.0 / q) {
			F[q] = inf;
		}
		else {	
			F[q] = F[q - 1] * q;
		}
	}
	for (q = 1; q < maxn; q++) {
		for (w = 1; w <= q; w++) {
			if (S[q - w] >= inf * 1.0 / getf(w - 2)) {
				D[q][w] = inf;
			}
			else {
				D[q][w] = S[q - w] * getf(w - 2);
			}
			S[q] += D[q][w];
			if (S[q] >= inf) {
				S[q] = inf;
			}
		}
	}
	cin >> k;
	for (e = 0; e < k; e++) {
		cin >> n >> m;
		if (S[n] < m) {
			cout << -1 << endl;
			continue;
		}
		vector <ll> ANS;
		ll d = 0;
		ll n1 = n, m1 = m;
		while (1) {
			ll s = 0;
			for (q = 0; q <= n1; q++) {
				s += D[n1][q];
				if (s >= m1) {
					break;
				}
			}
			ll i = q;
			m1 = m1 - s + D[n1][i]; 
			ll c = (m1 - 1) / S[n1 - i] + 1;
			m1 -= (c - 1) * S[n1 - i];
			vector <ll> CYC = kth_cycle(i, c);
			for (q = 0; q < CYC.size(); q++) {
				CYC[q] += d;
				ANS.pb(CYC[q]);
			}
			d += i;
			n1 -= i;
			if (d == n) {
				break;
			}
		}
		for (q = 0; q < ANS.size(); q++) {
			cout << ANS[q] + 1 << " ";
		}
		cout << endl;
	}
 	return 0;
}
