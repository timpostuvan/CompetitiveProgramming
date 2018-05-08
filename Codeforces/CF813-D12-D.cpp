/*
Idea:
- http://codeforces.com/blog/entry/52410
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 20)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 5111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

int best_val[100111], best_mod[10];
int dp[maxn][maxn], arr[maxn];

int main(){
	int n, ans = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", arr + i);

	dp[0][0] = 0;
	for(int j = 0; j <= n; j++){
		for(int i = 1; i <= n; i++)
			best_val[arr[i]] = 0;

		memset(best_mod, 0, sizeof(best_mod));

		for(int i = 0; i <= n; i++){
			if(i < j)
				dp[i][j] = dp[j][i];

			if(i == j)
				dp[i][j] = 0;

			if(i > j){
				int max_val = 0;
				max_val = max(max_val, best_val[arr[i] - 1]);
				max_val = max(max_val, best_val[arr[i] + 1]);
				max_val = max(max_val, best_mod[arr[i] % 7]);
				max_val = max(max_val, dp[j][0]);

				dp[i][j] = max_val + 1;
				ans = max(ans, dp[i][j]);
			}

			if(i > 0){
				best_val[arr[i]] = max(best_val[arr[i]], dp[i][j]);
				best_mod[arr[i] % 7] = max(best_mod[arr[i] % 7], dp[i][j]);
			}
		}
	}

	printf("%d\n", ans);
	return 0;
}  