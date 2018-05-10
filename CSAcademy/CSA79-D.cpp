#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;


vector<int> cur_group, adj[maxn];
int leader[maxn], cur[maxn];
int group_leader[maxn];
bool here[maxn];


int main(){
	int n, k, q;
	scanf("%d%d%d", &n, &k, &q);

	for(int i = 1; i <= k; i++){
		int num;
		scanf("%d", &num);
		for(int j = 1; j <= num; j++){
			int x;
			scanf("%d", &x);
			if(j == 1){
				leader[i] = x;
				group_leader[x] = 1;
			}
			else{
				adj[x].pb(leader[i]);
				adj[leader[i]].pb(x);
			}
		}
	}

	while(q--){
		cur_group.clear();
		
		int num;
		scanf("%d", &num);
		for(int i = 0; i < num; i++){
			scanf("%d", cur + i);
			here[cur[i]] = 1;
			if(group_leader[cur[i]] != 0)
				cur_group.pb(cur[i]);
		}

		int ans = 0;
		for(int a : cur_group){
			if(num < adj[a].size())
				continue;

			bool ok = 1;
			for(int j : adj[a]){
				if(!here[j]){
					ok = 0;
					break;
				}
			}
			ans += ok;
		}


		for(int i = 0; i < num; i++)
			here[cur[i]] = 0;

		printf("%d\n", ans);
	}
	return 0;
}