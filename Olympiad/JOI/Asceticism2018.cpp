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
typedef pair<int, int> pii;

ll fakt[maxn], inv[maxn];

ll fastexp(ll x, ll y){
	ll ret = 1LL;
	while(y){
		if(y & 1)
			ret = (ret * x) % MOD;

		x = (x * x) % MOD;
		y >>= 1;
	}
	return ret;
}

ll C(ll x, ll y){
	ll ret = fakt[x] * inv[y] % MOD * inv[x - y] % MOD;
	return ret;
}

ll eulerian_number(ll n, ll k){
	ll ans = 0LL;
	for(int i = 0; i <= k + 1; i++){
		ll cur = fastexp(-1LL, i) * C(n + 1LL, i) % MOD * fastexp(k + 1LL - i, n) % MOD;
		ans = (ans + cur + MOD) % MOD;
	}
	return ans;
}

void preprocess(){
	fakt[0] = inv[0] = 1LL;
	for(ll i = 1; i < maxn; i++){
		fakt[i] = (fakt[i - 1] * i) % MOD; 
		inv[i] = fastexp(fakt[i], MOD - 2);
	}
}

int main(){
	preprocess();

	ll n, k;
	scanf("%lld%lld", &n, &k);
	printf("%lld\n", eulerian_number(n, n - k) );

	return 0;
}