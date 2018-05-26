#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define n 100

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int best_x, best_y;
int dp[n + 3][n + 3];
vector<vector<int> > a;


int naive_solution(){
	int x = 1, y = 1, sx = 0, sy = 0;
	for(int i = 2; i <= n; i++){
		if(sx + a[x][i] < sy + a[y][i]){
			sx += a[x][i];
			x = i;
		}
		else{
			sy += a[y][i];
			y = i;
		}
	}
	return sx + sy;
}

int fun(int x, int y){
	if(x == n || y == n)
		return 0;

	int &cur = dp[x][y];
	if(cur != -1)
		return cur;

	int nxt = max(x, y) + 1;
	cur = INF;
	cur = min(cur, fun(nxt, y) + a[x][nxt]);
	cur = min(cur, fun(x, nxt) + a[y][nxt]);
	return cur;
}

int optimal_solution(){
	memset(dp, -1, sizeof(dp));
	return fun(1, 1);
}

int main(){
	a.resize(n + 3);
	for(int i = 0; i < n + 3; i++)
		a[i].resize(n + 3);

	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= n; j++)
			a[i][j] = 100;
	}

	a[1][2] = 1;
	a[2][3] = 1;
	a[1][3] = 1;

	for(int i = 1; i <= 100; i += 4){
		if(i + 3 <= n)
			a[i][i + 3] = 1;

		if(i + 4 <= n)
			a[i + 3][i + 4] = 1;
	}

	for(int i = 3; i <= 100; i += 4){
		if(i + 3 <= n)
			a[i][i + 3] = 1;

		if(i + 4 <= n)
			a[i + 3][i + 4] = 1;
	}


	//cout << optimal_solution() << "  " << naive_solution() << endl;  
	printf("%d\n", n);
	for(int i = 1; i <= n - 1; i++){
		for(int j = i + 1; j <= n; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	} 

	return 0;
}