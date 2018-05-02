#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define maxn 1000011

typedef long long ll;
typedef long double ld;

int n, mod;
char str[maxn];
int arr[maxn];
int dp[2][5][5][5]; // dp[current][maximum][minimum][balance]
int U[maxn], D[maxn], A[maxn];

ll solve(){
	ll ans = 0;
	U[0] = D[0] = A[0] = 2;
	for(int i = 1; i <= n; i++){
		A[i] = A[i - 1] + ((str[i] == 'L') ? -1 : 1);
		U[i] = max(U[i - 1], A[i]);
		D[i] = min(D[i - 1], A[i]);
	}

	for(int u = 0; u < 5; u++){
		for(int d = max(0, u - 2); d <= u; d++){
			for(int x = d; x <= u; x++)
				dp[(n + 1) & 1][u][d][x] = 1;
		}
	}

	for(int i = n; i >= 1; i--){
		int ii = i & 1;
		int last = 1 - ii;
		for(int u = 0; u < 5; u++){
			for(int d = max(0, u - 2); d <= u; d++){
				for(int x = d; x <= u; x++){
					dp[ii][u][d][x] = 0;

					if(x > 0)
						dp[ii][u][d][x] += dp[last][u][min(d, x - 1)][x - 1];
					
					if(x < 4)
						dp[ii][u][d][x] += dp[last][max(u, x + 1)][d][x + 1];

					dp[ii][u][d][x] %= mod;
				}
			}
		}

		if(str[i] == 'P'){
			int a = A[i - 1] - 1;
			int u = max(U[i - 1], a);
			int d = min(D[i - 1], a);

			if(a >= 0 && a < 5 && d >= 0 && u < 5 && u - d <= 2)
				ans = (ans + dp[last][u][d][a]) % mod;
		}
	}

	ans = (ans + 1) % mod;
	return ans;
} 


int main(){
	scanf("%d%d", &n, &mod);
	scanf("%s", str + 1);
	printf("%lld\n", solve());
	return 0;
}