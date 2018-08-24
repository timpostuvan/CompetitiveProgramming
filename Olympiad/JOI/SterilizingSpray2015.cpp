#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111
#define logn 35

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

ll K;
ll arr[maxn];

struct segtree{
	ll seg[4 * maxn][logn];
	ll lazy[4 * maxn];

	void push(ll x, ll l, ll d){
		if(lazy[x] == 0 || K == 1)
			return;

		lazy[x] = min(lazy[x], 1LL * logn);

		ll k = lazy[x];
		for(ll i = 0; i + k < logn; i++)
			seg[x][i] = seg[x][i + k];

		for(ll i = logn - k; i < logn; i++)
			seg[x][i] = 0;

		if(l != d){
			lazy[2 * x] += lazy[x];
			lazy[2 * x + 1] += lazy[x];
		}
		lazy[x] = 0;
	}

	void combine(ll x, ll l, ll d){
		for(ll i = 0; i < logn; i++)
			seg[x][i] = seg[l][i] + seg[d][i];
	}

	void setValue(ll x, ll val){
		seg[x][0] = val;
		for(ll i = 1; i < logn; i++)
			seg[x][i] = seg[x][i - 1] / K;
	}

	void build(ll x, ll l, ll d){
		if(l > d)
			return;

		if(l == d){
			setValue(x, arr[l]);
			lazy[x] = 0;
			return;
		}

		ll mid = (l + d) / 2;
		build(2 * x, l, mid);
		build(2 * x + 1, mid + 1, d);
		combine(x, 2 * x, 2 * x + 1);
		lazy[x] = 0;
	}

	void update(ll x, ll l, ll d, ll i, ll val){
		push(x, l, d);
		if(l > d || l > i || d < i)
			return;

		if(l == d && l == i){
			setValue(x, val);
			return;
		}

		ll mid = (l + d) / 2;
		update(2 * x, l, mid, i, val);
		update(2 * x + 1, mid + 1, d, i, val);
		combine(x, 2 * x, 2 * x + 1);
	}

	void reduce(ll x, ll l, ll d, ll i, ll j){
		push(x, l, d);
		if(l > d || l > j || d < i)
			return;

		if(i <= l && d <= j){
			lazy[x] = 1;
			push(x, l, d);
			return;
		}

		ll mid = (l + d) / 2;
		reduce(2 * x, l, mid, i, j);
		reduce(2 * x + 1, mid + 1, d, i, j);
		combine(x, 2 * x, 2 * x + 1);
	}

	ll query(ll x, ll l, ll d, ll i, ll j){
		push(x, l, d);
		if(l > d || l > j || d < i)
			return 0;

		if(i <= l && d <= j)
			return seg[x][0];

		ll mid = (l + d) / 2;
		ll ret = query(2 * x, l, mid, i, j);
		ret += query(2 * x + 1, mid + 1, d, i, j);
		return ret;
	}
}seg;

int main(){
	ll n, q;
	scanf("%lld%lld%lld", &n, &q, &K);
	for(ll i = 1; i <= n; i++)
		scanf("%lld", arr + i);

	seg.build(1, 1, n);

	while(q--){
		ll t, x, y;
		scanf("%lld%lld%lld", &t, &x, &y);

		if(t == 1)
			seg.update(1, 1, n, x, y);
		
		if(t == 2)
			seg.reduce(1, 1, n, x, y);

		if(t == 3)
			printf("%lld\n", seg.query(1, 1, n, x, y));
	}
	
	return 0;
}