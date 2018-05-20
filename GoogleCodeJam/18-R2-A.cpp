#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

char grid[maxn][maxn];
int arr[maxn];
vector<int> v;

void solve(){
	v.clear();
	for(int i = 0; i < maxn; i++){
		for(int j = 0; j < maxn; j++)
			grid[i][j] = '.';
	}

	int c;
	scanf("%d", &c);
	for(int i = 0; i < c; i++){
		scanf("%d", arr + i);
		if(arr[i] > 0)
			v.pb(i);
	}

	if(arr[0] == 0 || arr[c - 1] == 0){
		printf("IMPOSSIBLE\n");
		return;
	}

	int ind = 0, max_ans = 0;
	for(int i = 0; i < c; i++){
		while(ind < v.size() && arr[v[ind]] == 0)
			ind++;

		arr[v[ind]]--;
		int pos = v[ind];
		max_ans = max(max_ans, abs(v[ind] - i));
		if(pos == i)
			continue;

		int x = 0, y = i;

		if(pos < i){
			int num = i - pos;
			while(num--){
				grid[x][y] = '/';
				x++; y--;
			}
		}

		if(pos > i){
			int num = pos - i;
			while(num--){
				grid[x][y] = '\\';
				x++; y++;
			}
		}
	}

	printf("%d\n", max_ans + 1);
	for(int i = 0; i < max_ans + 1; i++){
		for(int j = 0; j < c; j++){
			printf("%c", grid[i][j]);
		}
		printf("\n");
	}
}

int main(){
	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; i++){
		printf("Case #%d: ", i);
		solve();
	}

	return 0;
}