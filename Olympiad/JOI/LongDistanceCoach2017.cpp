/*
Idea:
- https://codeforces.com/blog/entry/51010 (coach)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF ((int) 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 2111

typedef long long ll;

// WORKS ONLY FOR 71 POINTS

ll dp[maxn], s[maxn], c[maxn], d[maxn];
pair<ll, ll> p[maxn];
vector<int> v[maxn];

 
int main(){
	ll x, n, m, w, t;
	scanf("%lld%lld%lld%lld%lld", &x, &n, &m, &w, &t);
	for(int i = 1; i <= n; i++)
		scanf("%lld", s + i);

	s[n + 1] = x;

	for(int i = 1; i <= m; i++)
		scanf("%lld%lld", &p[i].fi, &p[i].se);

	sort(p + 1, p + 1 + m);
	for(int i = 1; i <= m; i++){
		d[i] = p[i].fi;
		c[i] = p[i].se;
	}

	for(int i = 1; i <= n + 1; i++){
		int pos = lower_bound(d + 1, d + 1 + m, s[i] % t) - d - 1;
		v[pos].pb(i);
	}

	dp[0] = s[n + 1] / t * w + w;
	for(int i = 1; i <= m; i++){
		dp[i] = dp[i - 1] + (s[n + 1] - d[i]) / t * w + w;
		for(int pos : v[i]){
			ll cur = s[pos] / t;
			ll cost = 0;
			for(int j = i; j >= 1; j--){
				cost += c[j];
				dp[i] = min(dp[i], dp[j - 1] + cost + (i - j + 1) * cur * w);
			}	
		}
	}

	printf("%lld\n", dp[m]);
	return 0;
}