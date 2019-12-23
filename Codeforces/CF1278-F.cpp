/*
	The idea is that E(x^k) is the expected number of arrays of size k of positions, on which try we will get joker. For a fixed
	array this value is 1 / m ^ d, where d is the number of different numbers in this array, so we use dp to count the amount of 
	such arrays for every d, and then find the sum of expected values for every d.
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
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
 
typedef long long ll;
 
typedef long double ld;
 
using namespace std;
 
const ll maxn = 5e3 + 100;
const ll mod = 998244353;
 
ll n, m, k;
 
ll D[maxn][maxn]; /// len, number of x;
 
ll step(ll a, ll x) {
	if (x == 0) {
		return 1;
	}
	if (x % 2 == 1) {
		return step(a, x - 1) * a % mod;
	}
	ll t = step(a, x / 2);
	return t * t % mod;
}
 
inline ll del(ll p, ll q) {
	return p * step(q, mod - 2) % mod;
}
 
int main()
{
	ll q, w, e, a, b, c;
	pyshnapyshnakaa;
	cin >> n >> m >> k;
	D[0][0] = 1;
	// ll zn = step(m, n);
	for (q = 1; q <= k; q++) {
		for (w = 0; w <= k; w++) {
			D[q][w] = D[q - 1][w] * w;
			if (w != 0) {
				D[q][w] += D[q - 1][w - 1] * (n - w + 1); 
			}
			D[q][w] %= mod;
			// if (D[q][w] != 0)cout << q << " " << w << " " << D[q][w] << " D" << endl;
		}
	}
	ll sum = 0;
	ll zn = 1;
	ll rm = del(1, m);
	for (q = 0; q <= k; q++) {
		sum += zn * D[k][q];
		// cout << zn << " " << D[k][q] << endl;
		sum %= mod;
		zn *= rm;
		zn %= mod;
	}
	cout << sum;
 	return 0;
}
