#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

struct BIT{
	ll bit[maxn];

	void update(int pos, int val){
		while(pos < maxn){
			bit[pos] += val;
			pos += (pos & -pos);
		}
	}

	void init(int n){
		for(int i = 1; i <= n; i++)
			update(i, 1);
	}

	ll query(int pos){
		ll ret = 0;
		while(pos){
			ret += bit[pos];
			pos -= (pos & -pos);
		}
		return ret;
	}
} bit;

ll cost[maxn], num[maxn];
int arr[maxn];

ll f(ll x){
	return (x + 1) / 2;
}

void precompute(){
	cost[0] = cost[1] = 0;
	for(ll i = 2; i < maxn; i++)
		cost[i] = f(i);

	num[0] = 0;
	for(ll i = 1; i < maxn; i++)
		num[i] = (num[i - 1] * i % MOD + (cost[i] * (i - 1)) % MOD) % MOD;
}

int main(){
	int len, n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", arr + i);

	len = n;
	precompute();
	bit.init(n);

	ll ans = 0;
	for(int i = 0; i < len; i++){
		ll less = bit.query(arr[i]) - 1;
		ans = (ans + less * ((num[n - 1] + cost[n]) % MOD) % MOD) % MOD;
		bit.update(arr[i], -1LL);
		n--;
	}

	printf("%lld\n", ans);	
	return 0;
}