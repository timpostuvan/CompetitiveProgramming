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

pair<ll, ll> dog[maxn], cat[maxn];
int cnt[maxn];

ll dist(pair<ll, ll> &a, pair<ll, ll> &b){
	return ((a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se));
}


int main(){
	int n, m;
	scanf("%d%d", &n, &m);

	for(int i = 0; i < n; i++)
		scanf("%lld%lld", &cat[i].fi, &cat[i].se);

	for(int i = 0; i < m; i++){
		scanf("%lld%lld", &dog[i].fi, &dog[i].se);
		ll val = INF;
		int ind = -1;

		for(int j = 0; j < n; j++){
			if(dist(dog[i], cat[j]) < val){
				val = dist(dog[i], cat[j]);
				ind = j;
			}
		}

		cnt[ind]++;
	}

	int ans = 0;
	for(int i = 0; i < n; i++)
		ans += (cnt[i] == 1);

	printf("%d\n", ans);
	return 0;
}