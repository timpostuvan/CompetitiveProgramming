/*
Idea:
- https://codeforces.com/blog/entry/51010 (abduction 2)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF ((ll) 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 50111
#define logn 17

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

ll segd[maxn][logn], segu[maxn][logn], segl[maxn][logn], segr[maxn][logn];
ll a[maxn], b[maxn];
ll h, w, q;

map<ll, ll> dp;


ll f(ll x, ll y, ll dir){
	ll id = x * 2 * maxn + 2 * y + dir;
	if(dp[id])
		return dp[id];

	ll cur = 0;
	if(dir == 0){	// left and right
		ll l = y - 1;
		ll r = y + 1;

		for(ll i = logn - 1; i >= 0; i--){
			if(l - (1 << i) + 1 >= 0 && segl[l][i] < a[x])
				l -= (1 << i);

			if(r + (1 << i) - 1 < w && segr[r][i] < a[x])
				r += (1 << i);
		}

		ll left = (l < 0) ? (y) : (abs(l - y) + f(x, l, 1));
		ll right = (r >= w) ? (w - 1 - y) : (abs(r - y) + f(x, r, 1));
		cur = max(left, right);
	}

	if(dir == 1){	// up and down
		ll u = x - 1;
		ll d = x + 1;

		for(ll i = logn - 1; i >= 0; i--){
			if(u - (1 << i) + 1 >= 0 && segu[u][i] < b[y])
				u -= (1 << i);

			if(d + (1 << i) - 1 < h && segd[d][i] < b[y])
				d += (1 << i);
		}

		ll up = (u < 0) ? (x) : (abs(u - x) + f(u, y, 0));
		ll down = (d >= h) ? (h - 1 - x) : (abs(d - x) + f(d, y, 0));
		cur = max(up, down);
	}
	return dp[id] = cur;
}

void precalc(){
	for(ll i = 0; i < h; i++)
		segu[i][0] = segd[i][0] = a[i];

	for(ll j = 1; j < logn; j++){
		for(ll i = 0; i < h; i++){
			if(i + (1 << j) - 1 < h)
				segd[i][j] = max(segd[i][j - 1], segd[i + (1 << (j - 1))][j - 1]);
			
			if(i - (1 << j) + 1 >= 0)
				segu[i][j] = max(segu[i][j - 1], segu[i - (1 << (j - 1))][j - 1]);
		}
	}

	for(ll i = 0; i < w; i++)
		segl[i][0] = segr[i][0] = b[i];

	for(ll j = 1; j < logn; j++){
		for(ll i = 0; i < w; i++){
			if(i + (1 << j) - 1 < w)
				segr[i][j] = max(segr[i][j - 1], segr[i + (1 << (j - 1))][j - 1]);
			
			if(i - (1 << j) + 1 >= 0)
				segl[i][j] = max(segl[i][j - 1], segl[i - (1 << (j - 1))][j - 1]);
		}
	}
}

int main(){
	scanf("%lld%lld%lld", &h, &w, &q);
	for(ll i = 0; i < h; i++)
		scanf("%lld", a + i);

	for(ll i = 0; i < w; i++)
		scanf("%lld", b + i);

	precalc();

	while(q--){
		ll x, y, ans = 0;
		scanf("%lld%lld", &x, &y);
		x--; y--;
		for(ll i = 0; i < 2; i++)
			ans = max(ans, f(x, y, i));

		printf("%lld\n", ans);
	} 
	return 0;
}