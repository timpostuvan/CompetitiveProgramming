#include <bits/stdc++.h>
 
using namespace std;
 
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define INF (1LL << 55)
#define maxn 1000111
#define p 43LL
 
typedef long long ll;
 
int n;
string s;
ll pra[maxn], dp[maxn];
 
ll fun(int l){
    int d = n - 1 - l;
     
 
    if(l > d)
        return 0;
     
    if(dp[l] != -1)
        return dp[l];    
    dp[l] = 1;
     
    int dol = d - l + 1;
    ll h1 = 0, h2 = 0;
    for(int i = 0; i < dol / 2; i++){
        h1 = h1 + (pra[i] * (s[l + i] - 'a'));   
        h2 = (h2 * p) + (s[d - i] - 'a');
        if(h1 == h2){
            dp[l] = max(dp[l], fun(l + i + 1) + 2);
            break;
        }
    }
    return dp[l];
}
 
void solve(){
    memset(dp, -1, sizeof(dp));
    cin >> s;
    n = s.length();
    cout << fun(0) << endl;
}
 
int main(){
    pra[0] = 1;
    for(int i = 1; i < maxn; i++)
        pra[i] = pra[i - 1] * p;
     
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}