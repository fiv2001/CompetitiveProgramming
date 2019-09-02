/*
    Let's say that ai(our sequence of permutation) = Ai * Bi * (Ai) ^ (-1); then we can see that Bi is cyclic in with the size of cycle
    equal to 6; And Ai is also cyclic, but every time we go through this cycle we have to multiply the Ai to another sequence;
    We can quickly find the Bi and also quickly find the Ai using binpow algorithm;
*/
#include <bits/stdc++.h>
#include <complex>
#define pb push_back
#define pll pair <ll, ll>
#define MOMI using namespace std;
#define mp make_pair
#define pyshnapyshnakaa ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
#pragma optimize("TKACHENKO-GORYACHENKO")
#pragma GCC optimize("O3")

//#pragma GCC optimize("unroll-loops")
//#define double long double

typedef long long ll;

typedef long double ld;

using namespace std;

const ll maxn = 3e5;

ll n, m, k;

vector <ll> ID;

void vivod(vector <ll> V){
    ll q;
    for (q = 0; q < V.size(); q++){
        cout << V[q] << " ";
    }
    cout << endl << endl;
}

vector <ll> mul(vector <ll> A, vector <ll> B){
    vector <ll> ANS;
    ANS.resize(A.size());
    ll q;
    for (q = 0; q < A.size(); q++){
        ANS[q] = A[B[q]];
    }
    return ANS;
}

vector <ll> rev(vector <ll> A){
    vector <ll> ANS;
    ANS.resize(A.size());
    ll q;
    for (q = 0; q < A.size(); q++){
        ANS[A[q]] = q;
    }
    return ANS;
}

vector <ll> step(vector <ll> A, ll x){
    if (x == 0){
        return ID;
    }
    if (x % 2 == 1){
        return mul(step(A, x - 1), A);
    }
    vector <ll> T = step(A, x / 2);
    return mul(T, T);
}

int main(){
    ll q, w, e, t, a, b, c;
    cin >> n >> k;
    vector <ll> P, Q;
    ID.resize(n);
    for (q = 0; q < n; q++){
        ID[q] = q;
    }
    P.resize(n); Q.resize(n);
    for (q = 0; q < n; q++){
        cin >> P[q];
        P[q]--;
    }
    for (q = 0; q < n; q++){
        cin >> Q[q];
        Q[q]--;
    }
    k--;
//    vivod(P);vivod(Q);
    vector <ll> W = mul(mul(Q, rev(P)), mul(rev(Q), P));
//    vivod(W);
//    vector <ll> A = mul(mul(P, step(W, (k) / 6)), rev(P)); /// 0, 6, 12, 18, 24
//    vector <ll> B = mul(mul(Q, step(W, (k) / 6)), rev(Q)); /// 1, 7, 13, 19, 25;
    vector <ll> A = mul(step(W, (k) / 6), mul(P, rev(step(W, k / 6))));
    vector <ll> B = mul(step(W, (k) / 6), mul(Q, rev(step(W, k / 6))));
//    cout << "A " << endl; vivod(A);
//    cout << "B " << endl; vivod(B);
    if (k % 6 == 0){
        for (q = 0; q < n; q++){
            cout << A[q] + 1 << " ";
        }
        return 0;
    }
    ll i = (k / 6) * 6 + 1;
    for (;i < k; i++){
        vector <ll> C;
        C.resize(n);
        for (q = 0; q < n; q++){
            C[A[q]] = B[q];
        }
//        vivod(C);
        A = B;
        B = C;
    }
    for (q = 0; q < n; q++){
        cout << B[q] + 1 << " ";
    }
    return 0;
}
