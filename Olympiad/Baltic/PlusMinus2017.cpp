#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

int n, m, k;
vector<vector<int> > p;
bool ok;

ll fastpow(ll x, ll y){
    ll ret = 1;
    while(y){
        if(y & 1)
            ret = (ret * x) % MOD;
        x = (x * x) % MOD;
        y /= 2;
    }
    return ret;
}

ll solve(){
    int cnt = 0;
    sort(p.begin(), p.end());
    for(int i = 0; i < k; i++){
        int j = i;

        while(j < k && p[i][0] == p[j][0])
            j++;

        for(int a = i + 1; a < j; a++){
            if((p[i][1] + p[i][2]) % 2 != (p[a][1] + p[a][2]) % 2){     // contradiction
                ok = 0;
                return 0;
            }
        }
        cnt++;
        i = j - 1;
    }
    return fastpow(2LL, n - cnt);
}


int main(){
    ok = 1;

    cin >> n >> m >> k;
    for(int i = 0; i < k; i++){
        string s;
        int a, b;
        cin >> s >> a >> b;
        p.pb({a, b, s[0] == '+'});
    }

    ll ans = solve();

    swap(n, m);
    for(int i = 0; i < k; i++)
        swap(p[i][0], p[i][1]);

    ans += solve();
    if(ok){
        if(k > 0)       // only one chess coloring
            ans = (ans - 1 + MOD) % MOD;
        else            // two different chess colorings
            ans = (ans - 2 + MOD) % MOD;
    }

    cout << ans << endl;
    return 0;
}