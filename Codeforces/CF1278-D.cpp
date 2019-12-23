/*
    We iterate over the left end of line and hold all the segments starting before it in set. We make a lower_bound on set and find all 
    the segments ending before current. Then we iterate over them and merge them with current segment in dsu.
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
 
const ll maxn = 1e6;
 
ll n, m, k, t;
 
vector <pll> V;
 
ll A[maxn];
 
ll B[maxn];
 
ll L[maxn];
 
ll R[maxn];
 
ll S[maxn];
 
ll E[maxn];
 
ll P[maxn];
 
ll getp(ll i) {
	if (P[i] == i) {
		return i;
	}
	ll p = getp(P[i]);
	P[i] = p;
	return P[i];
}
 
void mrg(ll i, ll j) {
	if (getp(i) == getp(j)) {
		cout << "NO";
		exit(0);
	}
	i = P[i];
	j = P[j];
	P[i] = j;
}
 
int main()
{
	ll q, w, e, a, b, c;
	pyshnapyshnakaa;
	string s;
	cin >> n;
	for (q = 0; q < 2 * n; q++) {
		S[q] = -1; E[q] = -1;
	}
	for (q = 0; q < n; q++) {
		P[q] = q;
	}
	for (q = 0; q < n; q++) {
		cin >> a >> b;
		a--; b--;
		A[q] = a; B[q] = b; 
		S[a] = q; E[b] = q;
		// cout << a << " " << b << " A B" << endl;
	}
	set <pll> st;
	ll cnt = 0;
	for (q = 0; q < 2 * n; q++) {
		// cout << q << " Q" << endl;
		ll i = S[q];
		if (S[q] == -1) {
			// cout << q << " " << E[q] << " e" << endl;
			st.erase(mp(B[E[q]], E[q]));
		}
		else {
			// cout << q << " " << S[q] << " S" << endl;
			auto it = st.lower_bound(mp(B[i], 0));
			while (1) {
				if (it == st.begin()) {
					break;
				}
				it--;
				ll j = (*it).second;
				// cout << i << " " << j << endl;
				mrg(i, j);
				cnt++;
				if (it == st.begin()) {
					break;
				}
			}
			st.insert(mp(B[i], i));
		}
	}
	if (cnt != n - 1) {
		cout << "NO";
		return 0;
	}
	cout << "YES";
 	return 0;
}
