/* We iterate of the table and see what happens if we do/don't xor the row this number is and do/don't xor the column this number is.
If the result isn't what we want, we add edges in our graph. Then we write a 2-sat on this graph.
*/

#include <iostream>
#include <bits/stdc++.h>
#define pb push_back
#define pll pair <ll, ll>
 
using namespace std;
 
typedef long long ll;
 
const ll maxn = 2e3 + 10;
 
ll A[maxn][maxn];
 
ll B[maxn][maxn];
 
ll X[maxn];
 
ll n, m, k;
 
vector <ll> P;
 
bool used[4 * maxn];
 
ll C[4 * maxn];
 
bool dor[maxn];
 
bool dos[maxn];
 
ll RP[4 * maxn];
 
vector <ll> V[4 * maxn];
 
void dfs(ll v){
	used[v] = 1;
	ll q;
	for (q = 0; q < V[v].size(); q++){
		if (used[V[v][q]]){
			continue;
		}
		dfs(V[v][q]);
	}
	P.pb(v);
}
 
// vector <ll> V[4 * maxn]; // (str, 0), (str, 1), (row, 0), (row, 1);
 
void addedge(ll i, ll is1, ll isrow1, ll j, ll is2, ll isrow2){
	ll i1 = i + n * 2 * isrow1 + n * is1;
	ll j1 = j + n * 2 * isrow2 + n * is2;
	V[i1].pb(j1);
	// cout << "add! " << i << " " << is1 << " " << isrow1 << " " << j << " " << is2 << " " << isrow2 << endl;
	// cout << "add " << i1 << " " << j1 << endl;
}
 
ll color = 1;
 
void dfs1(ll v){
	used[v] = 1;
	C[v] = color;
	ll q;
	for (q = 0; q < V[v].size(); q++){
		if (used[V[v][q]]){
			continue;
		}
		dfs1(V[v][q]);
	}
}
 
ll getnotx(ll x){
	if ((x / n) % 2 == 0){
		return x + n;
	}
	return x - n;
}
 
void choose(ll x){
	if ((x / n) % 2 == 1){
		if (x / n < 2){
			dos[x % n] = 1;
		}
		else{
			dor[x % n] = 1;
		}
	}
}
 
int main(){
	ll q, w, a, b;
	cin >> n;
	string s;
	for (q = 0; q < n; q++){
		cin >> s;
		for (w = 0; w < n; w++){
			if (s[w] == '1'){
				A[q][w] = 1;
			}
		} 
	}
	for (q = 0; q < n; q++){
		cin >> s;
		for (w = 0; w < n; w++){
			if (s[w] == '1'){
				B[q][w] = 1;
			}
		}
	}
	cin >> s;
	// cout << "S " << s << endl;
	for (q = 0; q < n; q++){
		if (s[q] == '1'){
			X[q] = 1;
		}
	}
	// for (q = 0; q < n; q++){
	// 	cout << X[q] << " ";
	// }
	// cout << "X " << endl;
	// for (q = 0; q < n; q++){
	// 	for (w = 0; w < n; w++){
	// 		cin >> A[q][w];
	// 	}
	// }
	// for (q = 0; q < n; q++){
	// 	for (w = 0; w < n; w++){
	// 		cin >> B[q][w];
	// 	}
	// }
	for (q = 0; q < n; q++){
		for (w = 0; w < n; w++){
			ll a00 = A[q][w];
			ll a01 = A[q][w] ^ X[q];
			ll a10 = A[q][w] ^ X[w];
			ll a11 = A[q][w] ^ X[q] ^ X[w];
			// cout << "Q W " << q << " " << w << endl;
			if (a00 != B[q][w]){
				// cout << "CASE 0 0 " << endl;
				addedge(q, 0, 0, w, 1, 1);
				addedge(w, 0, 1, q, 1, 0);
			}
			if (a01 != B[q][w]){
				// cout << "CASE 0 1 " << endl;
				addedge(q, 0, 0, w, 0, 1);
				addedge(w, 1, 1, q, 1, 0);
			}
			if (a10 != B[q][w]){
				// cout << "CASE 1 0 " << endl;
				addedge(q, 1, 0, w, 1, 1);
				addedge(w, 0, 1, q, 0, 0);
			}
			if (a11 != B[q][w]){
				// cout << "CASE 1 1 " << endl;
				addedge(q, 1, 0, w, 0, 1);
				addedge(w, 1, 1, q, 0, 0);
			}
		}
	}
	for (q = 0; q < 4 * n; q++){
		if (!used[q]){
			dfs(q);
		}
	}
	for (q = 0; q < 4 * n; q++){
		used[q] = 0;
	}
	// reverse(P.begin(), P.end());
	for (q = 0; q < P.size(); q++){
		if (!used[P[q]]){
			dfs1(P[q]);
			color++;
		}
	}
	// for (q = 0; q < 4 * n; q++){
	// 	cout << C[q] << " ";
	// }
	// cout << endl;
	for (q = 0; q < 4 * n; q++){
		ll nq = getnotx(q);
		// cout <<"NOT " << q << " " << nq << endl;
		if (C[q] == C[nq]){
			cout << -1;
			return 0;
		}
	}
	for (q = 0; q < 4 * n; q++){
		RP[P[q]] = q;
	}
	for (q = 0; q < 4 * n; q++){
		ll nq = getnotx(q);
		if (RP[q] < RP[nq]){
			choose(q);
		}
		else{
			choose(nq);
		}
	}
	ll sum = 0;
	for (q = 0; q < n; q++){
		sum += dos[q];
		sum += dor[q];
	}
	cout << sum << endl;
	for (q = 0; q < n; q++){
		if (dos[q]){
			cout << "row " << q << endl;
		}
		if (dor[q]){
			cout << "col " << q << endl;
		}
	}
}
