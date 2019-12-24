/*
    We greedily take the vertex which is exactly in one triple right now, then we delete the triple it is in and keep going. This way
    we find one of the good orders for the triplets. To find the order of vertexes we iterate over the order of triplets from the 
    end and maintain a linked list of vertexes. When we have a triplet we have exactly one vertex from it, which is not from the 
    current linked list, and the other 2 vertexes are neighbours in this list. So we add the first vertex between them.
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
 
ll n, m, k;
 
ll getp(vector <ll> &P, ll i) {
	if (P[i] == i) {
		return i;
	}
	ll p = getp(P, P[i]);
	P[i] = p;
	return p;
}
 
int main()
{
	ll q, w, e, a, b, c;
	pyshnapyshnakaa;
	string s;
	cin >> k;
	for (e = 0; e < k; e++) {
		cin >> n;
		// vector <ll> cnt(n);
		// set <pll> ban;
		set <pll> S;
		vector <vector <ll> > Q;
		vector <set <vector <ll> > > V(n);
		vector <vector <ll> > G(n);
		map <vector <ll>, ll> M;
		vector <ll> L(n);
		vector <ll> R(n);
		for (q = 0; q < n; q++) {
			L[q] = R[q] = q;
		}
		for (q = 0; q < n - 2; q++) {
			cin >> a >> b >> c;
			a--; b--; c--;
			// cnt[a]++; cnt[b]++; cnt[c]++;
			vector <ll> X = {a, b, c};
			sort(X.begin(), X.end());
			M[X] = q;
			Q.pb(X);
			V[a].insert(X);
			V[b].insert(X);
			V[c].insert(X);
		}
		vector <ll> ANS1;
		vector <ll> ANS2;
		for (q = 0; q < n; q++) {
			S.insert(mp(V[q].size(), q));
		}
		while (!S.empty()) {
			pll p = *(S.begin());
			if (p.first != 1) {
				cout << "HUYCA_POSOSI" << endl;
				exit(-1);
			}
			ll i = p.second;
			// cout << i << " i" << endl;
			// used[i] = 1;
			vector <ll> neighs = *(V[i].begin());
			ANS2.pb(M[neighs]);
			vector <ll> neighs2;
			for (q = 0; q < neighs.size(); q++) {
				if (neighs[q] != i) {
					neighs2.pb(neighs[q]);
				}
				ll j = neighs[q];
				S.erase(mp(V[j].size(), j));
				V[j].erase(neighs);
				if (V[j].size() != 0) {
					S.insert(mp(V[j].size(), j));
				}
			}
			// ban.insert(mp(neighs2[0], neighs2[1]));
			// for (q = 0; q < neighs2.size(); q++) {
			// 	ll j = neighs2[q];
			// 	// cout << "j " << j << endl;
			// 	// if (ban.find(mp(min(i, j), max(i, j))) != ban.end()) {
			// 	// 	continue;
			// 	// }
			// 	// ban.insert(mp(min(i, j), max(i, j)));
			// 	if (getp(L, i) == getp(L, j)) {
			// 		continue;
			// 	}
			// 	ll i1 = i, j1 = j;
			// 	if (q == 0) {
			// 		j1 = getp(R, j);
			// 		i1 = getp(L, i);
			// 		R[j1] = i1;
			// 		L[i1] = j1;
			// 	}
			// 	else {
			// 		j1 = getp(L, j);
			// 		i1 = getp(R, i);
			// 		L[j1] = i1;
			// 		R[i1] = j1;
			// 	}
			// 	cout << i1 << " " << j1 << endl;
			// 	G[i1].pb(j1);
			// 	G[j1].pb(i1);
			// 	// cout << "ADD " << endl;
			// }
			// cout << endl;
		}
		vector <ll> nxt(n);
		// vector <ll> prev(n);
		for (q = 0; q < n; q++) {
			nxt[q] = -1;
		}
		vector <ll> I = Q[ANS2.back()];
		for (q = 0; q < I.size(); q++) {
			// cout << I[q] << " ";
			nxt[I[q]] = I[(q + 1) % 3];
			// prev[I[q]] = I[(q + 2) % 3];
		}
		// cout << " I" << endl;
		for (q = (ll)ANS2.size() - 2; q >= 0; q--) {
			vector <ll> I = Q[ANS2[q]];
			// cout << "ANS2 " << ANS2[q] << endl;
			// for (w = 0; w < Q[ANS2[q]].size(); w++) {
			// 	cout << Q[ANS2[q]][w] << " ";
			// }
			// cout << endl;
			// cout << "WASq" << endl;
			ll i = 0;
			vector <ll> neighs2;
			for (w = 0; w < 3; w++) {
				if (nxt[I[w]] == -1) {
					i = I[w];
					// break;
				}
				else {
					neighs2.pb(I[w]);
				}
			}
			// cout << "sz " << neighs2.size() << endl;
			// cout << i << " " << neighs2[0] << " " << neighs2[1] << " DEBUG" << endl;
			if (nxt[neighs2[0]] == neighs2[1]) {
				nxt[neighs2[0]] = i;
				nxt[i] = neighs2[1];
			}
			else {
				nxt[neighs2[1]] = i;
				nxt[i] = neighs2[0];
			}
		}
		// ll v = G[start][0];
		ll v = nxt[0];
		ll last = 0;
		ANS1.pb(0);
		while (v != 0) {
			// cout << "v " << v << " " << G[v].size() << endl; 
			ANS1.pb(v);
			last = v;
			v = nxt[v];
		}
		// cout << endl;
		for (q = 0; q < ANS1.size(); q++) {
			cout << ANS1[q] + 1 << " ";
		}
		cout << endl;
		for (q = 0 ;q < ANS2.size(); q++) {
			cout << ANS2[q] + 1 << " ";
		}
		cout << endl;
	}
 	return 0;
}
