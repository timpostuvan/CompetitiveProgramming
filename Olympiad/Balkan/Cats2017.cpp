#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 10111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int dp[2][maxn][3][2][2];

void solve(){
	int n;
	scanf("%d", &n);

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < maxn; j++){
			for(int k = 0; k < 3; k++){
				dp[i][j][k][0][0] = INF; 
				dp[i][j][k][1][0] = INF; 
				dp[i][j][k][0][1] = INF; 
				dp[i][j][k][1][1] = INF; 
			}
		}
	}

	dp[0][n / 2][2][0][0] = 0;

	int has0 = 0, has1 = 0, firstlion = 0;
	for(int i = 1; i <= n; i++){
		int ii = i % 2;
		int c;
		scanf("%d", &c);

		if(i == 1 && c == 2)
			firstlion = 1;
		
		if(c == 1)
			has1 = 1;

		if(c == 0)
			has0 = 1;

		for(int j = 0; j < n + 10; j++){
			for(int k = 0; k < 3; k++){
				dp[ii][j][k][0][0] = INF; 
				dp[ii][j][k][1][0] = INF; 
				dp[ii][j][k][0][1] = INF; 
				dp[ii][j][k][1][1] = INF; 
			}
		}

		for(int j = 1; j < n + 5; j++){
			for(int k = 0; k < 3; k++){
				if(c == 2) dp[ii][j][c][0][0] = min(dp[ii][j][c][0][0], dp[ii ^ 1][j - ((k ^ c) == 1)][k][0][0]);
				if(c != 1) dp[ii][j][c][1][0] = min(dp[ii][j][c][1][0], dp[ii ^ 1][j - ((k ^ c) == 1)][k][1][0]);
				if(c == 0) dp[ii][j][c][1][0] = min(dp[ii][j][c][1][0], dp[ii ^ 1][j - ((k ^ c) == 1)][k][0][0]);
				if(c != 0) dp[ii][j][c][0][1] = min(dp[ii][j][c][0][1], dp[ii ^ 1][j - ((k ^ c) == 1)][k][0][1]);
				if(c == 1) dp[ii][j][c][0][1] = min(dp[ii][j][c][0][1], dp[ii ^ 1][j - ((k ^ c) == 1)][k][0][0]);
				if(c == 0) dp[ii][j][c][1][1] = min(dp[ii][j][c][1][1], dp[ii ^ 1][j - ((k ^ c) == 1)][k][0][1]);
				if(c == 1) dp[ii][j][c][1][1] = min(dp[ii][j][c][1][1], dp[ii ^ 1][j - ((k ^ c) == 1)][k][1][0]);

				dp[ii][j][c][1][1] = min(dp[ii][j][c][1][1], dp[ii ^ 1][j - ((k ^ c) == 1)][k][1][1]);

				dp[ii][j][k][0][0] = min(dp[ii][j][k][0][0], dp[ii ^ 1][j + (c == 2)][k][0][0] + 1);
				dp[ii][j][k][0][1] = min(dp[ii][j][k][0][1], dp[ii ^ 1][j + (c == 2)][k][0][1] + 1);
				dp[ii][j][k][1][0] = min(dp[ii][j][k][1][0], dp[ii ^ 1][j + (c == 2)][k][1][0] + 1);
				dp[ii][j][k][1][1] = min(dp[ii][j][k][1][1], dp[ii ^ 1][j + (c == 2)][k][1][1] + 1);
			}
		}
	}

	if(!has1 || !has0){
		printf("0\n");
		return;
	}

	int ans = INF;
	ans = min(ans, dp[n % 2][n / 2][0][1][1]);
	ans = min(ans, dp[n % 2][n / 2][1][1][1]);
	ans = min(ans, dp[n % 2][n / 2][2][1][1]);

	ans = min(ans, dp[n % 2][n / 2][2][1][0]);
	ans = min(ans, dp[n % 2][n / 2][2][0][1]);	

	if(firstlion){
		ans = min(ans, dp[n % 2][n / 2][0][1][0]);
		ans = min(ans, dp[n % 2][n / 2][1][0][1]);	
	}

	if(ans == INF)
		ans = -1;

	printf("%d\n", ans);
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--)
		solve();
	
	return 0;
}