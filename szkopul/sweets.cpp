#include <bits/stdc++.h>
#define pb push_back
#define pll pair <ll, ll>
#define MOMI using namespace std;
#define mp make_pair
#define pyshnapyshnakaa ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
#pragma optimize("TKACHENKO-GORYACHENKO")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

typedef long long ll;

typedef long double ld;

using namespace std;

const ll maxn = 20;
const ll mod = 2004;

ll n, m, k;

ll A[maxn];

ll st2[maxn];

ll gcd(ll a, ll b) {
	while (a != 0) {
		b = b % a;
		swap(a, b);
	}
	return b;
}

ll getc(ll n, ll k) {
	ll q, w;
	if (n < k) {
		return 0;
	}
	vector <ll> verh;
	vector <ll> niz;
	ll ans = 1;
	for (q = n - k + 1; q <= n; q++) {
		verh.pb(q);
	}
	for (q = 1; q <= k; q++) {
		niz.pb(q);
	}
	for (q = 0; q < niz.size(); q++) {
		for (w = 0; w < verh.size(); w++) {
			ll g = gcd(niz[q], verh[w]);
			niz[q] /= g; verh[w] /= g;
		}
	}
	for (q = 0; q < verh.size(); q++) {
		ans *= verh[q];
		ans %= mod;
	}
	// cout << "C " << n << " " << k << " " << ans << endl; 
	return ans;
}

ll getnless(ll x) {
	ll q, w, e;
	ll ans = 0;
	for (q = 0; q < st2[n]; q++) {
		ll cnt = 0;
		ll sum = x;
		for (w = 0; w < n; w++) {
			if ((q & st2[w]) != 0) {
				cnt++;
				sum -= (A[w] + 1);
			}
		}
		// cout << q << " q " << sum << endl;
		if (cnt % 2 == 0) {
			ans += getc(sum + n, n);
			ans %= mod;
		}
		else {
			ans -= getc(sum + n, n);
			ans = (ans + mod) % mod;
		}
	}
	// cout << "ANS " << ans << endl;
	return ans;
}

signed main() {
	ll q, w, e, a, b;
	pyshnapyshnakaa;
	cin >> n >> a >> b;
	st2[0] = 1;
	for (q = 1; q < maxn; q++) {
		st2[q] = st2[q - 1] * 2;
	}
	for (q = 0; q < n; q++) {
		cin >> A[q];
	}
	// cout << "AU" << endl;
	cout << (getnless(b) - getnless(a - 1) + mod) % mod;
	return 0;
}
