/*
  We go from the end to the beginning and set the aims of person as the first present in his preference list which is not already
  someone's aim. After that we iterate from beginning and say that the i-th person chooses who to swap with this way: he goes where his 
  aim lies, if the owner of his aim is before him then he stops and takes his aim, otherwise he keeps on going, but instead of his aim
  he uses the aim of the owner of his aim. If by doing this he gets back to his aim, then he can pass his turn.
  Proof:
      Induction by the length of chain (len) (the number of times a person changes his aim).
      Basis : if n == 1 then if someone already owns his aim then he doesn't have to make a move, and if his aim's owner is before him
      then he should take it right now, or he will never get it (only the one who makes a move can get a gift from someone who has 
      already made the move). 
      Step : let's see what will do the first guy after the current one, which is in chain(j). He will take the present from the current 
      guy (because of the hypothesis of induction (it's the element in chain, which is before him)). Then the size of chain will 
      decrease and the next guy will also take the present from the current and so on. Every turn the size of chain decreases, so in the
      end the current guy will get what he wants;
*/
#include <bits/stdc++.h>
#include <complex>
#define pb push_back
#define pll pair <ll, ll>
#define MOMI using namespace std;
#define mp make_pair
#define pyshnapyshnakaa ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
//#pragma optimize("TKACHENKO-GORYACHENKO")
#pragma GCC optimize("O3")

//#pragma GCC optimize("unroll-loops")
//#define double long double

typedef long long ll;

typedef long double ld;

using namespace std;

const ll maxn = 20;
const ll mod = 1e9 + 7;

ll n, m, k;

bool used[maxn];

ll CH[maxn];

ll C[maxn];

ll X[maxn];

ll A[maxn];

ll st2[maxn];

class YankeeSwap{
    public : string sequenceOfSwaps(vector <string> S){
        ll q, w;
        string ans = "";
        n = S.size();
        for (q = 0; q < n; q++){
            for (w = 0; w < n; w++){
                S[q][w] -= 'A';
            }
        }
        for (q = 0; q < n; q++){
            A[q] = q;
            C[q] = q;
        }
        for (q = n - 1; q >= 0; q--){
            for (w = 0; w < n; w++){
                if (!used[(ll)S[q][w]]){
                    used[(ll)S[q][w]] = 1;
                    CH[q] = S[q][w];
                    break;
                }
            }
        }
//        for (q = 0; q < n; q++){
//            cout << CH[q] << " ";
//        }
//        cout << endl;
//        cout << endl;
//        ans = ans + '-';
        for (q = 0; q < n; q++){
            ll v = C[CH[q]];
            while (v > q){
                v = C[CH[v]];
            }
            if (v == q){
                ans += '-';
            }
            else{
                swap(C[q], C[A[v]]);
                swap(A[q], A[v]);
                ans += char('a' + v);
            }
//            for (w = 0; w < n; w++){
//                cout << A[w] << " ";
//            }
//            cout << endl;
        }
        return ans;
    }
};
//int main(){
//    YankeeSwap ys;
////    vector <string> S;
////    string s;
////    while (cin >> s){
////        S.pb(s);
////    }
//    cout << ys.sequenceOfSwaps(
//}
