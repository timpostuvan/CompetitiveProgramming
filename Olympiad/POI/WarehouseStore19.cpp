/*
Idea:
- It is always optimal to try cheapest order and if there are more, we choose the rightmost
- We take order if we can (this can be simulated using binary search and binary indexed tree)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 250111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

ll fen[maxn];
ll a[maxn], b[maxn];

set<int> s; 

bool comp(pll a, pll b){
	if(a.fi != b.fi)
		return a.fi < b.fi;

	return a.se > b.se;
}

void update(int pos, ll val){
	while(pos < maxn){
		fen[pos] += val;
		pos += pos & (-pos);
	}
}

ll get(int pos){
	ll ret = 0;
	while(pos){
		ret += fen[pos];
		pos -= pos & (-pos);
	}
	return ret;
}

ll sum(int l, int d){
	return get(d) - get(l - 1);
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld", a + i);
		update(i, a[i]);
		s.insert(i);
	}

	vector<pll> v;
	for(int i = 1; i <= n; i++){
		scanf("%lld", b + i);
		v.pb(mp(b[i], i));
	}

	sort(v.begin(), v.end(), comp);
	
	vector<int> ans, del;
	for(int i = 0; i < n; i++){
		ll pos = v[i].se;
		ll val = v[i].fi;

		int l = 1, d = pos, mid, ans_pos = -1;
		while(l <= d){
			mid = (l + d) / 2;
			if(sum(mid, pos) >= val){
				ans_pos = mid;
				l = mid + 1; 
			}
			else
				d = mid - 1;
		} 

		if(ans_pos != -1){
			ans.pb(pos);				
			del.clear();

			ll left = val;
			auto it = s.upper_bound(pos);

			while(left > 0){
				it--;

				int cur_pos = *it;
				ll cur = min(a[cur_pos], left);
				left -= cur;
				a[cur_pos] -= cur;
				update(cur_pos, -cur);

				if(a[cur_pos] == 0)
					del.pb(cur_pos);
			}

			for(int x : del)
				s.erase(x);
		}
	}

	sort(ans.begin(), ans.end());

	printf("%d\n", (int) ans.size());
	for(int x : ans)
		printf("%d ", x);

	return 0;
}