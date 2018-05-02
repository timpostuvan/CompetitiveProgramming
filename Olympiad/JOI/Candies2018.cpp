#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

ll arr[maxn];
set<pair<ll, int> > s;
set<pair<int, ll> > ind;
vector<ll> ans;

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld", arr + i);
		s.insert(mp(-arr[i], i));
		ind.insert(mp(i, -arr[i]));
	}


	// we mustn't choose the ones at the ends since the number of candies stays the same

	ind.insert(mp(0, INF));		
	ind.insert(mp(n + 1, INF));
	s.insert(mp(INF, 0));
	s.insert(mp(INF, n + 1));

	ll cur = 0;

	for(int k = 0; k < (n + 1) / 2; k++){
		vector<pair<ll, int> > v;

		auto it = s.begin();
		cur = cur + (-it -> fi);
		ans.pb(cur);

		auto it1 = ind.lower_bound(mp(it -> se, -INF));
		it1--;

		auto it2 = ind.lower_bound(mp(it -> se, -INF)); 
		it2++;

		v.pb(*it);
		v.pb(mp(it1 -> se, it1 -> fi));
		v.pb(mp(it2 -> se, it2 -> fi));
		
		int pos = it -> se;
		ll tren = it1 -> se + it2 -> se - it -> fi;

		for(auto i : v){
			s.erase(mp(i.fi, i.se));
			ind.erase(mp(i.se, i.fi));
		}

		s.insert(mp(tren, pos));
		ind.insert(mp(pos, tren));
	}

	for(ll i : ans)
		printf("%lld\n", i);
		
	return 0;
}