/*
    We split all the points in 4 groups by the parity of their x and y coordinates. Then, if all the points are in the same coordinate,
    we can divide every coordinate by 2 and solve it recursively. If there are some points with even sum of coordinates and some points 
    with odd sum, we can divide them by this criteria. If all points are with even (or all with odd) sum, but in different groups
    we can divide them by the group they are in.
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
const ll inf = 1e10;

ll n, k, m;

void solve(vector <pll> A) {
	// cout << "A " << endl;
	vector <ll> C[2][2];
	ll q, w, e;
	for (q = 0; q < A.size(); q++) {
		ll c1 = (A[q].first) % 2;
		ll c2 = (A[q].second) % 2;
		C[c1][c2].pb(q);
	}
	for (q = 0; q < 2; q++) {
		for (w = 0; w < 2; w++) {
			if (C[q][w].size() == A.size()) {
				for (e = 0; e < A.size(); e++) {
					A[e].first /= 2;
					A[e].second /= 2;
				}
				solve(A);
			}
		}
	}
	if (C[0][0].size() + C[1][1].size() != A.size() && C[0][0].size() + C[1][1].size() != 0) {
		cout << C[0][0].size() + C[1][1].size() << endl;
		for (q = 0; q < C[0][0].size(); q++) {
			cout << C[0][0][q] + 1 << " ";
		}
		for (q = 0; q < C[1][1].size(); q++) {
			cout << C[1][1][q] + 1 << " "; 
		}
		exit(0);
	}
	if (C[0][0].size() + C[1][1].size() == A.size()) {
		cout << C[0][0].size() << endl;
		for (q = 0; q < C[0][0].size(); q++) {
			cout << C[0][0][q] + 1 << " ";
		}
		exit(0);
	}
	if (C[0][0].size() + C[1][1].size() == 0) {
		cout << C[0][1].size() << endl;
		for (q = 0; q < C[0][1].size(); q++) {
			cout << C[0][1][q] + 1 << " ";
		}
		exit(0);
	}
	cout << "OoOoOo" << endl;
	exit(-1);
}

int main()
{
	ll q, w, e, a, b, c;
	pyshnapyshnakaa;
	cin >> n;
	vector <pll> A(n);
	for (q = 0; q < n; q++) {
		cin >> A[q].first >> A[q].second;
		A[q].first += inf; A[q].second += inf;
	}
	solve(A);
 	return 0;
}
