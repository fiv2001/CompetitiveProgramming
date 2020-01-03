/*
    A segment is good if r - l + 1 = k * sum. First, we count the number of segments with k >= t; Then we count the answer for segments 
    with small k the following way: let's fix k, now let's imagine that we are keeping the index for every 1 in string, where for current
    left border the right border should be. Now we can see that we should add 1 to the answer if this border is between this 1 and the
    next 1. Now we notice that this index changes the same way for every 1: if we meet 0 it moves 1 to the right, otherwise it moves 
    on k to the left. So we can be recording the changes in an unordered map and then to find the answer for a fixed 1 we iterate through
    all the indexes between this 1 and the next 1 and add what is in corresponding index of the unordered map.
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

const ll maxn = 2e5 + 100;
const ll block = 1500;
const ll blocksz = (maxn + block - 1) / block;
// const ll blocksz = 1;

ll n, m;

ll S[maxn];

ll A[maxn];

ll C[maxn];

ll nxt[maxn];

string s;

int main()
{
	ll q, w, e, a, b, c;
	pyshnapyshnakaa;
	cin >> s;
	// s += '1';
	// for (q = 0; q < 2e5 - 3; q++) {
	// 	s += '0';
	// }
	// s += '1';
	n = s.length();
	vector <ll> I;
	for (q = 0; q < s.length(); q++) {
		A[q] = s[q] - '0';
		if (A[q] == 1) {
			I.pb(q);
		}
	}
	S[0] = s[0] - '0';
	for (q = 1; q < s.length(); q++) {
		S[q] = S[q - 1] + s[q] - '0';
	}
	ll ans = 0;
	ll i = 0;
	for (q = 0; q < n; q++) { /// k >= blocksz
		for (w = i; w < block + i && w < I.size(); w++) {
			ll cnt = w - i + 1;
			ll l = q + cnt * blocksz - 1;
			l = max(l, I[w]);
			ll r;
			if (w != I.size() - 1) {
				r = I[w + 1];
			}
			else {
				r = n;
			}
			// cout << q << " " << w << " DEBUG " << l << " " << r << " " << cnt << endl;
			if (l > r) {
				continue;
			}
			ll dans = (r - q) / cnt - (l - q) / cnt;
			// cout << "DANS " << dans << endl;
			ans += dans;
		}
		if (A[q] == 1) {
			i++;
		}
	}
	// cout << "FANS " << ans << endl;
	for (q = 0; q + 1 < I.size(); q++) {
		nxt[I[q]] = I[q + 1];
	}
	if (I.size() != 0) {
		nxt[I.back()] = n;
	}
	ll k;
	for (k = 1; k < blocksz; k++) {
		// cout << "K " << k << endl;
		// cout << "CURANS " << ans << endl;
		unordered_map <ll, ll> C;
		C[0] = 1;
		ll cur = 0;
		ll c = 0;
		for (q = 0; q < n; q++) {
			if (A[q] == 1) {
				c++;
				for (w = q; w < nxt[q]; w++) {
					ll ind = w - k * c + 1;
					// if (ind != 0)cout << "IND " << q << " " << w << " " << ind << endl;
					ans += C[ind];
					// cout << C[ind] << endl;
				}
			}
			cur++;
			if (A[q] == 1) {
				cur = cur - k;
			}
			// if (cur != 0)cout << cur << " CUR" << endl;
			C[cur]++;
		}
		// cout << endl << endl;
	}
	cout << ans;
 	return 0;
}
