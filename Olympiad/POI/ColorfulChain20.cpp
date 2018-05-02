#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

ll a[maxn], l[maxn], c[maxn], arr[maxn];
ll cnt[maxn];
ll num_ok;

void add(ll x){
	if(cnt[x] == l[x])
		num_ok--;

	cnt[x]++;

	if(cnt[x] == l[x])
		num_ok++;
}

void remove(ll x){
	if(cnt[x] == l[x])
		num_ok--;

	cnt[x]--;
	
	if(cnt[x] == l[x])
		num_ok++;
}

int main(){
	ll n, m, col_num = 0, sz = 0, ans = 0;
	scanf("%lld%lld", &n, &m);

	for(ll i = 0; i < m; i++){
		scanf("%lld", a + i);
		sz += a[i];
	}

	for(ll i = 0; i < m; i++){
		scanf("%lld", c + i);
		l[c[i]] = a[i];
	}

	for(ll i = 0; i < n; i++){
		scanf("%lld", arr + i);

		if(cnt[arr[i]] == 0)
			col_num++;

		cnt[arr[i]] = 1;
	}

	memset(cnt, 0, sizeof(cnt));

	if(sz > n){
		printf("0\n");
		return 0;
	}

	num_ok = col_num - m;
	for(ll i = 0; i < sz; i++)
		add(arr[i]);

	if(num_ok == col_num)
		ans++;

	for(ll i = sz; i < n; i++){
		remove(arr[i - sz]);
		add(arr[i]);
		if(num_ok == col_num)
			ans++;
	}

	printf("%lld\n", ans);
	return 0;
}