#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdlib>

using namespace std;

int pre[55][55];
int arr[55][55];
int dp[51][51][51][51];

int f(int x1, int y1, int x2, int y2){
	int tren = 99999999;
	if(dp[x1][y1][x2][y2] > -1) return dp[x1][y1][x2][y2];
	if(x2 == x1 && y2 == y1){
		dp[x1][y1][x2][y2] = 0;
		return 0;
	} 

	for(int i = x1 + 1; i <= x2; i++){
		int l = f(x1, y1, i - 1, y2);
		int d = f(i, y1, x2, y2);
		tren = min(tren, l + d);
	}

	for(int i = y1 + 1; i <= y2; i++){
		int l = f(x1, y1, x2, i - 1);
		int d = f(x1, i, x2, y2);
		tren = min(tren, l + d);
	}

	int val = pre[x2][y2] + pre[x1 - 1][y1 - 1] - pre[x2][y1 - 1] - pre[x1 - 1][y2];
	dp[x1][y1][x2][y2] = tren + val;
	return dp[x1][y1][x2][y2];
}

int main(){
	memset(dp, -1, sizeof(dp));
	memset(pre, 0, sizeof(pre));
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%d", arr[i] + j);
			pre[i][j] = arr[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
		}
	}

	printf("%d", f(1, 1, n, m));
	return 0;
}