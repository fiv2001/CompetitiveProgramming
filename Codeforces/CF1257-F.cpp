/*
  We do meet-in-the-middle: iterate over all masks under 2^15, apply them to the first half of every number, then to the second 
  half of every number, and then for every mask applied to the first half try to find a corresponding mask applied to the second half.
*/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

const ll maxn = 1e2;
const ll inf = 1e9;

ll n;

ll A[maxn];

ll st2[maxn];

map <vector <ll>, ll> M;

map <vector <ll>, ll> M1;

int main() {
	ll q, w, e, a, b;
	cin >> n;
	st2[0] = 1;
	for (q = 1; q < 40; q++) {
		st2[q] = st2[q - 1] * 2;
	}
	for (q = 0; q < n; q++) {
		cin >> A[q];
	}
	for (q = 0; q < st2[15]; q++) {
		// cout << q << " Q" << endl;
		vector <ll> A1;
		vector <ll> B1;
		for (w = 0; w < n; w++) {
			A1.pb((A[w] ^ q) % st2[15]);
			B1.pb(((A[w] ^ (q * st2[15])) / st2[15]) * st2[15]);
		}
		for (w = 0; w < n; w++) {
			A1[w] = __builtin_popcount(A1[w]);
			B1[w] = __builtin_popcount(B1[w]);
		}
		for (w = n - 1; w >= 0; w--) {
			A1[w] -= A1[0];
			B1[w] -= B1[0];
		}
		// cout << "DEBUG " << q << endl;
		// for (w = 0; w < n; w++) {
		// 	cout << A1[w] << " ";
		// }
		// cout << endl;
		// for (w = 0; w < n; w++) {
		// 	cout << B1[w] << " ";
		// }
		// cout << endl << endl;
		M[A1] = q;
		M1[B1] = q;
	}
	// cout << "SMERT" << endl;
	for (auto p : M) {
		vector <ll> A1 = p.first;
		vector <ll> B1(n);
		for (q = 0; q < n; q++) {
			B1[q] = -A1[q];
		}
		if (M1.find(B1) != M1.end()) {
			ll i = M1[B1];
			cout << p.second + i * st2[15] << endl;
			return 0;;
		}
	}
	cout << -1;
	return 0;
}
