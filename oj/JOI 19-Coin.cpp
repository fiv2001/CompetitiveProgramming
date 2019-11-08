/*
  Firstly, we move all the coins into the rectangle (1, 1) x (N, 2) (every coin to the closest cell to it); After that we greedily make
  them stand in different cells;
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
#pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

typedef long long ll;

typedef long double ld;

using namespace std;

const ll maxn = 5e5;

ll n, m, k;

ll X[maxn];

ll Y[maxn];

ll A[maxn][2];

ll ans = 0;

vector <ll> P[2];
vector <ll> M[2];

void add(ll i) {
	ll x, y;
	if (Y[i] >= 2) {
		y = 2;
		// ans += Y[i] - 2;

	}
	else {
		y = 1;
		// ans += 1 - Y[i];
	}
	if (X[i] < 1) {
		x = 1;
	}
	else {
		if (X[i] > n) {
			x = n;
		}
		else {
			x = X[i];
		}
	}
	// cout << "DX " << X[i] - x << " " << " DY " << Y[i] - y << endl;
	ans += abs(X[i] - x) + abs(Y[i] - y);
	A[x - 1][y - 1]++;
}

signed main() {
	ll q, w, e, a, b, c, d;
	pyshnapyshnakaa;
	cin >> n;
	for (q = 0; q < 2 * n; q++) {
		cin >> X[q] >> Y[q];
		add(q);
	}
	// cout << ans << " PREANS" << endl;
	for (q = 0; q < n; q++) {
		for (w = 0; w < 2; w++) {
			while (A[q][w] > 1) {
				// cout << q << 
				if (!M[w].empty()) {
					ll i = M[w].back();
					M[w].pop_back();
					ans += q - i;
					// cout << "TYPE 0" << endl;
					A[q][w]--;
				}
				else {
					P[w].pb(q);
					// break;
					A[q][w]--;
				}
			}

			while (A[q][w] < 1) {
		// cout << q << " Q" << endl;
				if (!P[w].empty()) {
					ll i = P[w].back();
					P[w].pop_back();
					ans += q - i;
					// cout << "TYPE 1" << endl;
					A[q][w]++;
				}
				else {
					M[w].pb(q);
					break;
				}
			}
 		}
 		for (w = 0; w < 2; w++) {
 			while (!P[w].empty() && !M[1 - w].empty()) {
 				ll i = P[w].back(), j = M[1 - w].back();
 				P[w].pop_back(); M[1 - w].pop_back();
 				ans += abs(i - j) + 1;
 				// cout << "TYPE 2 " << i << " " << j << endl; 	
 			}
 		}
	}
	cout << ans;
	return 0;
}
