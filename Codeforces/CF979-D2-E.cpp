#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 55

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int col[maxn];
ll dp[maxn][maxn][maxn][maxn];
ll inv[maxn], fact[maxn], pw[maxn], odd[maxn], even[maxn];


ll fastpow(ll x, ll y){
	ll ret = 1;
	while(y){
		if(y & 1)
			ret = (ret * x) % MOD;

		x = (x * x) % MOD;
		y >>= 1;
	}
	return ret;
}

ll C(int x, int y){
	return fact[x] * inv[y] % MOD * inv[x - y] % MOD;
}

void preprocess(){
	pw[0] = inv[0] = fact[0] = 1;
	for(int i = 1; i < maxn; i++){
		pw[i] = (pw[i - 1] * 2LL) % MOD;
		fact[i] = (fact[i - 1] * i) % MOD;
		inv[i] = fastpow(fact[i], MOD - 2);
	}

	for(int i = 0; i < maxn; i++){
		for(int j = 0; j <= i; j += 2)
			even[i] = (even[i] + C(i, j)) % MOD;

		for(int j = 1; j <= i; j += 2)
			odd[i] = (odd[i] + C(i, j)) % MOD;
	}
}

void find_ans(int i, int ow, int ew, int eb, int ob, ll &ret){
	if(col[i] != 0 && ow != 0)		// odd-white
		ret = (ret + dp[i - 1][ow - 1][ew][eb] * pw[ow - 1 + ew + eb] % MOD * even[ob] % MOD) % MOD;

	if(col[i] != 0 && ew != 0)		// even-white
		ret = (ret + dp[i - 1][ow][ew - 1][eb] * pw[ow + ew - 1 + eb] % MOD * odd[ob] % MOD) % MOD;

	if(col[i] != 1 && ob != 0)		// odd-black
		ret = (ret + dp[i - 1][ow][ew][eb] * pw[ob - 1 + eb + ew] % MOD * even[ow] % MOD) % MOD;

	if(col[i] != 1 && eb != 0)		// even-black
		ret = (ret + dp[i - 1][ow][ew][eb - 1] * pw[ob + eb - 1 + ew] % MOD * odd[ow] % MOD) % MOD;
}



int main(){
	int n, p;
	scanf("%d%d", &n, &p);
	for(int i = 1; i <= n; i++)
		scanf("%d", col + i);

	preprocess();

	ll ans = 0;
	dp[0][0][0][0] = 1;
	for(int i = 1; i <= n; i++){
		for(int ow = 0; ow <= n; ow++){
			for(int ew = 0; ew <= n; ew++){
				for(int eb = 0; eb <= n; eb++){
					int ob = i - ow - ew - eb;

					find_ans(i, ow, ew, eb, ob, dp[i][ow][ew][eb]);
					if(n == i && (ow + ob) % 2 == p)
						ans = (ans + dp[i][ow][ew][eb]) % MOD;
				}
			}
		}
	}

	printf("%lld\n", ans);
	return 0;
}