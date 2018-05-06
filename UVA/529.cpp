/*
Idea:
- Iterative deepening with heavy pruning
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 20)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

int ans[maxn];
bool finish;
int n;

void DFS(int x, int depth){
	if(finish)
		return;

	if(x == depth){
		if(ans[x] == n)
			finish = 1;

		return;
	}

	for(int i = 0; i <= x; i++){
		for(int j = i; j <= x; j++){
			if(ans[i] + ans[j] > n || ans[i] + ans[j] <= ans[x])
				continue;

			int cur = ans[i] + ans[j];
			for(int k = x + 2; k <= depth; k++)
				cur <<= 1;

			if(cur < n)
				continue;

			ans[x + 1] = ans[i] + ans[j];
			DFS(x + 1, depth);

			if(finish)
				return;
		}
	}
}

int main(){
	scanf("%d", &n);

	while(n != 0){
		ans[0] = 1;
		finish = 0;

		int depth = 0, cur = n;
		while(cur >>= 1)
			depth++;

		while(!finish){
			DFS(0, depth);
			depth++;
		}

		printf("%d", ans[0]);

		for(int i = 1; i < depth; i++)
			printf(" %d", ans[i]);
		printf("\n");

		scanf("%d", &n);
	}

	return 0;
}  