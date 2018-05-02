#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 500111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

ll d[maxn], f[maxn];

ll CEIL(ll a, ll b){
	return (a + b - 1) / b;
}

ll find(ll t, ll mid){
	if(mid == 0){
		return -1234;
	}

	ll x = f[mid];
	ll cnt = t / x;
	ll pos = cnt * x - mid;
	return pos;
}

int main(){
	int n, q;
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i++)
		scanf("%lld", d + i);

	f[1] = d[1];
	for(int i = 2; i <= n; i++)
		f[i] = f[i - 1] * CEIL(d[i], f[i - 1]);

	while(q--){
		ll t, i, j;
		scanf("%lld%lld%lld", &t, &i, &j);

		ll dod = 0;
		if(i <= t && t <= j)
			dod = 1;

		ll l = 1, d = n, mid, ans1 = 0, ans2 = 0;
		while(l <= d){
			mid = (l + d) / 2;
			ll pos = find(t, mid);
			if(pos >= i){
				l = mid + 1;
				ans1 = mid; 
			}
			else
				d = mid - 1;
		}

		l = 1; d = n;
		while(l <= d){
			mid = (l + d) / 2;
			ll pos = find(t, mid);
			if(pos <= j){
				d = mid - 1;
				ans2 = mid; 
			}
			else
				l = mid + 1;
		}
		
		ll all = 0;
		if(find(t, ans2) < i || find(t, ans1) > j || ans1 < ans2)
			all = 0;
		else
			all = ans1 - ans2 + 1;

		printf("%lld\n", all + dod);
	} 
	return 0;
}