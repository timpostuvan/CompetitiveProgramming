#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000011

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

ll arr[maxn];

ll mod(ll x, ll y){
	return (x >= y) ? (x % y + y) : x;
}

ll fastpow(ll x, ll y, ll m){
	ll ret = mod(1LL, m);
	while(y){
		if(y & 1)
			ret = mod(ret * x, m);
		x = mod(x * x, m);
		y /= 2;
	}
	return ret;
}

unordered_map<ll, ll> myphi;

ll phi(ll x){
	if(myphi.count(x))
		return myphi[x];

	ll p = x;
	ll a = x;
	for(ll i = 2; i * i <= x; i++){
		if(a % i == 0){
			p = p / i * (i - 1);
			while(a % i == 0)
				a /= i;
		}
	}

	if(a > 1)
		p = p / a * (a - 1);

	myphi[x] = p;
	return p;
}

ll solve(ll l, ll d, ll m){
	if(l == d || m == 1)
		return mod(arr[l], m);

	return fastpow(arr[l], solve(l + 1, d, phi(m)), m);
} 

void testcase(ll m){
	ll n;
	scanf("%lld", &n);
	for(ll i = 1; i <= n; i++)
		scanf("%lld", arr + i);

	printf("%lld\n", solve(1, n, m) % m);
}

int main(){
	ll t, m;
	scanf("%lld%lld", &t, &m);
	while(t--)
		testcase(m);
	
	return 0;
}