/*
Idea:
- http://codeforces.com/blog/entry/60701?#comment-446462 (Coin Denominations)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 60)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 111
#define maxq 1111111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

ll min_val[maxq + maxn], w[maxn];

int main(){
	int n, c, m;
	scanf("%d%d%d", &c, &n, &m);

	w[0] = 0;
	for(int i = 1; i <= n; i++)
		w[i] = INF;

	for(int i = 0; i < c; i++){
		ll a, b;
		scanf("%lld%lld", &a, &b);
		w[a] = b;
	}

	for(int i = 1; i <= maxq; i++){
		min_val[i] = INF;
		for(int j = 1; j <= min(n, i); j++)
			min_val[i] = min(min_val[i], min_val[i - j] + w[j]);
	}

	while(m--){
		ll x;
		scanf("%lld", &x);

		if(x <= maxq){
			ll ans = min_val[x];
			if(ans >= INF)
				ans = -1;
			else
				ans %= MOD;

			printf("%lld\n", ans);
		}

		else{
			__int128 ans = (__int128) INF * INF;
			for(int i = 1; i <= n; i++){
				if(w[i] >= INF)
					continue;

				ll cur = ((x - maxq) / i + 1) * i; 
				ll left = x - cur;

				if(min_val[left] >= INF)
					continue;

				ans = min(ans, (__int128) cur / i * w[i] + min_val[left]);
			}

			if(ans >= (__int128) INF * INF)
				ans = -1;
			else
				ans %= MOD;
			printf("%lld\n", (ll) ans);
		}
	}
	return 0;
}