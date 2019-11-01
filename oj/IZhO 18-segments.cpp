/*
  Let's split the query into 3 subqueries (l and r are bounds of a segment given in a query):
  1. Find the amount of segments with size at least k;
  2. Find the amount of segments with size at least k that end before l + k - 1;
  3. Find the amount of segments with size at least k that start after r - k + 1;
  The overall answer is ans1 - ans2 - ans3;
  We can answer these queries using sqrt decomposition in O(n * sqrt(n) * log(n));
*/
#include <bits/stdc++.h>
#define pb push_back
#define pll pair <ll, ll>
#define MOMI using namespace std;
#define mp make_pair
#define pyshnapyshnakaa ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
#pragma optimize("TKACHENKO-GORYACHENKO")
#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
 
typedef int ll;
 
typedef long double ld;
 
using namespace std;
 
const ll inf = 2e9 + 500;
const ll maxn = 2e5;
const ll block = 300;
const ll block_sz = (maxn + block - 1) / block;
 
ll n, m, k, t;
 
struct seg{
	ll l;
	ll r;
	inline ll sz() const {
		return r - l + 1;
	}
	ll i;
};
 
seg S[maxn];
 
ll ssz = 0;
 
vector <ll> lasts;
 
inline bool cmpl(const ll& a, const ll& b) {
	return S[a].l < S[b].l;
}
 
inline bool cmpr(const ll& a, const ll& b) {
	return S[a].r < S[b].r;
}
 
inline bool cmpsz(const ll& a, const ll& b) {
	return S[a].sz() < S[b].sz();
}
 
vector <ll> segsl;
vector <ll> segsr;
 
vector <ll> R[block];
 
vector <ll> L[block];
 
ll MNL[block];
ll MXL[block];
ll MNR[block];
ll MXR[block];
 
ll IL[maxn];
ll IR[maxn];
 
bool used[maxn];
 
inline void buildL(ll q) {
	ll w;
	sort(L[q].begin(), L[q].end(), cmpsz);
	MNL[q] = inf;
	MXL[q] = -inf;
	for (w = 0; w < L[q].size(); w++) {
		MNL[q] = min(MNL[q], S[L[q][w]].l);
		MXL[q] = max(MXL[q], S[L[q][w]].l);
	}
}
 
inline void buildR(ll q) {
	ll w;
 	MNR[q] = inf;
	MXR[q] = -inf;
	sort(R[q].begin(), R[q].end(), cmpsz);
	for (w = 0; w < R[q].size(); w++) {
		MNR[q] = min(MNR[q], S[R[q][w]].r);
		MXR[q] = max(MXR[q], S[R[q][w]].r);
	}
}
 
inline void mrgl() {
	ll i, j;
	vector <ll> ANS;
	while (i != segsl.size() && j != lasts.size()) {
		if (cmpl(segsl[i], lasts[j])) {
			ANS.pb(segsl[i]);
			i++;
		}
		else {
			ANS.pb(lasts[j]);
			j++;
		}
	}
	for (; i < segsl.size(); i++) {
		ANS.pb(segsl[i]);
	}
	for (; j < lasts.size(); j++) {
		ANS.pb(lasts[j]);
	}
	segsl = ANS;
}
 
inline void mrgr() {
	ll i, j;
	vector <ll> ANS;
	while (i != segsr.size() && j != lasts.size()) {
		if (cmpr(segsr[i], lasts[j])) {
			ANS.pb(segsr[i]);
			i++;
		}
		else {
			ANS.pb(lasts[j]);
			j++;
		}
	}
	for (; i < segsr.size(); i++) {
		ANS.pb(segsr[i]);
	}
	for (; j < lasts.size(); j++) {
		ANS.pb(lasts[j]);
	}
	segsr = ANS;
}
 
inline void rebuild() { 
	ll q, w;
	ll blocki = 0;
	for (q = 0; q < block; q++) {
		R[q].clear();
		L[q].clear();
	}
	sort(lasts.begin(), lasts.end(), cmpl);
	mrgl();
	// sort(segs.begin(), segs.end(), cmpl);
	for (auto p : segsl) {
		IL[p] = -1;
		if (used[p]) {
			continue;
		}
		if (L[blocki].size() > block_sz) {
			blocki++;
		}
		IL[p] = blocki;
		L[blocki].pb(p);
	}
	sort(lasts.begin(), lasts.end(), cmpr);
	mrgr();
	lasts.clear();
	blocki = 0;
	// sort(segs.begin(), segs.end(), cmpr);
	for (auto p: segsr) {
		IR[p] = -1;
		if (used[p]) {
			continue;
		}
		if (R[blocki].size() > block_sz) {
			blocki++;
		}
		IR[p] = blocki;
		R[blocki].pb(p);
	}
	for (q = 0; q < block; q++) {
		buildL(q);
	}
	for (q = 0; q < block; q++) {
		buildR(q);
	}
}
 
inline void add(seg a) {
	lasts.pb(a.i);
	// S.pb(a);
	S[ssz] = a;
	ssz++;
	// segs.push_back(a.i);
	IL[a.i] = IR[a.i] = -1;
}
 
inline void del(seg b) { 
	ll il = IL[b.i], ir = IR[b.i];
	used[b.i] = 1;
	if (il == -1) {
		return;
	}
	L[il].erase(find(L[il].begin(), L[il].end(), b.i));
	R[ir].erase(find(R[ir].begin(), R[ir].end(), b.i));
	buildL(il);
	buildR(ir);
}
 
inline ll slowL(ll i, ll x, ll l) {
	ll q;
	ll ans = 0;
	for (q = 0; q < L[i].size(); q++) {
		if (S[L[i][q]].l >= l && S[L[i][q]].sz() >= x) {
			ans++;
		}
	}
	return ans;
}
 
inline ll slowR(ll i, ll x, ll r) {
	ll q;
	ll ans = 0;
	for (q = 0; q < R[i].size(); q++) {
		if (S[R[i][q]].r <= r && S[R[i][q]].sz() >= x) {
			ans++;
		}
	}
	return ans;
}
 
inline ll bpl(ll i, ll x) {
	ll l = -1, r = L[i].size(), M;
	while (r - l > 1) {
		M = (l + r) / 2;
		if (S[L[i][M]].sz() >= x) {
			r = M;
		}
		else {
			l = M;
		}
	}
	return r;
}
 
inline ll bpr(ll i, ll x) {
	ll l = -1, r = R[i].size(), M;
	while (r - l > 1) {
		M = (l + r) / 2;
		if (S[R[i][M]].sz() >= x) {
			r = M;
		}
		else {
			l = M;
		}
	}
	return r;
}
 
inline ll fastL(ll i, ll x) {
	if (L[i].empty()) {
		return 0;
	}
	seg good;
	good.l = 0; good.r = x - 1; 
	S[ssz] = good;
	ll j = (lower_bound(L[i].begin(), L[i].end(), ssz, cmpsz) - L[i].begin());
	// S.pop_back();
	return L[i].size() - j;
}
 
inline ll fastR(ll i, ll x) {
	if (R[i].empty()) {
		return 0;
	}
	seg good;
	good.l = 0; good.r = x - 1;
	S[ssz] = good;
	ll j = (lower_bound(R[i].begin(), R[i].end(), ssz, cmpsz) - R[i].begin());
	// S.pop_back();
	return R[i].size() - j;
}
 
inline ll getansL(ll x, ll l) {
	ll q;
	ll ans = 0;
	for (q = 0; q < block; q++) {
		if (MNL[q] == inf) {
			continue;
		}
		if (MNL[q] >= l) {
			ans += fastL(q, x);
			continue;
		}
		if (MXL[q] < l) {
			continue;
		}
		ans += slowL(q, x, l);
	}
 
	for (q = 0; q < lasts.size(); q++) {
		if (used[lasts[q]]) {
			continue;
		}
		if (S[lasts[q]].l >= l && S[lasts[q]].sz() >= x) {
			ans++;
		}
	}
	return ans;
}
 
inline ll getansR(ll x, ll r) {
	ll q;
	ll ans = 0;
	ll cnt = 0;
	for (q = 0; q < block; q++) {
		if (MNR[q] == inf) {
			continue;
		}
		// if (q > 1) {
		// 	if (MXR[q - 1] > MNR[q]) {
		// 		exit(-1);
		// 	}
		// }
		if (MXR[q] <= r) {
			ll dans = fastR(q, x);
			ans += dans;
			continue;
		}
		if (MNR[q] > r) {
			continue;
		}
		/// MXR[q] > r && MNR[q] <= r, 
		ll dans = slowR(q, x, r);
		ans += dans;
		cnt++;
	}
	// if (cnt > 5) {
	// 	exit(-1);
	// }
	for (q = 0; q < lasts.size(); q++) {
		if (used[lasts[q]]) {
			continue;
		}
		if (S[lasts[q]].r <= r && S[lasts[q]].sz() >= x) {
			ans++;
		}
	}
	return ans;
}
 
inline ll answer(seg c, ll k) {
	if (c.sz() < k) {
		return 0;
	}
	ll q, w;
	ll ans = 0;
	ll lk = c.r - k + 2, rk = c.l + k - 2;
	ll allans = getansR(k, inf);
	ll dansl = getansL(k, lk);
	ll dansr = getansR(k, rk);
	ans = allans - dansr - dansl;
	return ans;
}
 
signed main() {
	ll q, w, e, a, b, c;
	pyshnapyshnakaa;
	cin >> n >> t;
	// cout << block_sz * block << endl;
	ll nxt = 0;
	ll lastans = 0;
	// ll cnt3 = 0;
	// segsl.reserve(n);
	// segsr.reserve(n);
	// S.reserve(n);
	for (q = 0; q < block; q++) {
		L[q].reserve(block_sz);
		R[q].reserve(block_sz);
	}
	for (q = 0; q < n; q++) {
		ll comm;
		cin >> comm;
		ll l, r;
		seg x;
		if (comm == 1) {
			cin >> l >> r;
			l ^= (lastans * t);
			r ^= (lastans * t);
			if (l > r) {
				swap(l, r);
			}
			x.l = l; x.r = r;
			x.i = ssz;
			add(x);
		}
		if (comm == 2) {
			cin >> a;
			a--;
			del(S[a]);
		}
		// if (cnt3 > 8e4 && n > 1e5) {
		// 	exit(-1);
		// }
		if (comm == 3) {
			// cnt3++;
			cin >> l >> r;
			l ^= (lastans * t);
			r ^= (lastans * t);
			if (lasts.size() >= block_sz * 2) {
				rebuild();
			}
			if (l > r) {
				swap(l, r);
			} 
			x.l = l; x.r = r;
			cin >> c;
			lastans = answer(x, c);
			cout << lastans << '\n';
		}
	}
	return 0;
}
