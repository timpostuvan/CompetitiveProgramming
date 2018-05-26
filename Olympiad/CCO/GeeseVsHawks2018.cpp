#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

char str[2][maxn];
int arr[maxn][2];
int dp[maxn][maxn], n;

int fun(int x, int y){
	if(x >= n || y >= n)
		return 0;

	int &cur = dp[x][y];
	if(cur != -1)
		return cur;

	cur = 0;
	cur = max(cur, fun(x + 1, y));
	cur = max(cur, fun(x, y + 1));

	if(str[0][x] == 'W' && str[1][y] == 'L' && arr[x][0] > arr[y][1])
		cur = max(cur, fun(x + 1, y + 1) + arr[x][0] + arr[y][1]);

	if(str[0][x] == 'L' && str[1][y] == 'W' && arr[x][0] < arr[y][1])
		cur = max(cur, fun(x + 1, y + 1) + arr[x][0] + arr[y][1]);

	return cur;
}

int main(){
	memset(dp, -1, sizeof(dp));

	scanf("%d", &n);
	scanf("%s", str[0]);
	for(int i = 0; i < n; i++)
		scanf("%d", &arr[i][0]);

	scanf("%s", str[1]);
	for(int i = 0; i < n; i++)
		scanf("%d", &arr[i][1]);

	printf("%d\n", fun(0, 0));
	return 0;
}