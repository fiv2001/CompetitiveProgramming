/*
  We count for every index i the number of resets we have to do to survive until the i-th move(greedily); Then we iterate through the 
  position we're going to win on, then we iterate through the position we will have to reset for the last time(we don't actually
  brute force it, we maintain a pointer to it).
*/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
 
using namespace std;
 
typedef long long ll;
 
const ll maxn = 5e5;
const ll inf = 1e9;
 
ll A[maxn];
 
ll B[maxn];
 
ll SA[maxn];
 
ll SB[maxn];
 
ll live[maxn];
 
ll n, m, k, t;
 
int main() {
	ll q, w, e, a, b;
	cin >> t;
	for (e = 0; e < t; e++) {
		cin >> n >> k;
		for (q = 0; q < n; q++) {
			cin >> B[q];
		}
		for (q = 0; q < n; q++) {
			cin >> A[q];
		}
		// cout << "SMISL " << endl;
		ll sa = 0, sb = 0;
		bool f = 0;
		for (q = 0; q < n; q++) {
			sb += B[q];
			SB[q] = sb;
			sa += A[q];
			SA[q] = sa;
			// cout << sa << " " << sb << endl;
			if (sa >= k && sb < k) {
				cout << 0 << endl << endl;
				f = 1;
				break;
			}
		}
		if (f) {
			continue;
		}
		ll lasti = inf;
		vector <ll> ANS;
		sa = 0, sb = 0;
		for (q = 0; q < n; q++) {
			ll ds = min(sa, sb);
			sb += B[q];
			// cout << q << " " << sa << " " << sb << " SA SB " << endl;
			if (sb >= k) {
				// cout << " Q " << q << endl;
				live[q + 1] = live[q] + 1;
				ANS.pb(q - 1);
				sb -= ds;
				sa -= ds;
				if (sb >= k) {
					for (w = q + 1; w <= n; w++) {
						live[w] = inf;
					}
					break;
				}
			}
			else {
				live[q + 1] = live[q];
			}
			sa += A[q];
		}
		ll xi = 0;
		bool can = 0;
		ll lastq = inf;
		ll ans = inf;
		for (q = 0; q < n && q < lasti; q++) {
			if (can) {
				break;
			}
			if (SA[q] >= SB[q]) {
				for (; xi < q; xi++) {
					ll ds = min(SA[xi], SB[xi]);
					ll nsa = SA[q] - ds;
					ll nsb = SB[q] - ds;
					// cout << "FISTING " << q << " " << ds << " " << nsa << " " << nsb << " " << xi << endl; 
					if (nsa >= k && nsb < k) {
						lastq = xi;
						can = 1;
						ans = live[xi + 1] + 1;
						break;
					}
					if (nsa < k) {
						break;
					}
				}
			}
		}
		if (!can || ans >= inf) {
			cout << -1 << endl;
			continue;
		}
		// cout << "DEBUG ANS " << endl;
		// for (q = 0; q < ANS.size(); q++) {
		// 	cout << ANS[q] << " ";
		// }
		// cout << endl;
		while (ANS.size() != 0) {
			if (!(ANS.back() >= lastq)) {
				break;
			}
			ANS.pop_back();
		}
		ANS.pb(xi);
		cout << ANS.size() << endl;
		for (q = 0; q < ANS.size(); q++) {
			cout << ANS[q] + 1 << " ";
		}
		cout << endl;
	}
	return 0;
}
