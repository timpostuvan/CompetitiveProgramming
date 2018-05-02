#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <set>

using namespace std;
	
#define maxn 101111

long long n, k, m;
vector<pair<long long, long long> > adj[maxn];
long long arr[maxn];
long long dp[maxn][2];
bool used[maxn];

long long solve(){
	set<pair<long long, long long> > pq;
	for(long long i = 0; i < n; i++) dp[i][0] = dp[i][1] = (1LL << 55);
	for(long long i = 0; i < k; i++) dp[arr[i]][0] = dp[arr[i]][1] = 0;
	for(int i = 0; i < n; i++) pq.insert({dp[i][1], i});

	while(!pq.empty()){
		long long x = pq.begin() -> second;
		pq.erase(pq.begin());

		if(x == 0) return dp[0][1];


		for(auto v : adj[x]){
			long long val = dp[x][1] + v.second;
			if(val < dp[v.first][0]){
				pq.erase(pq.find({dp[v.first][1], v.first}));
				dp[v.first][1] = dp[v.first][0];
				dp[v.first][0] = val;
				pq.insert({dp[v.first][1], v.first});
			}
			else{
				if(val < dp[v.first][1]){
					pq.erase(pq.find({dp[v.first][1], v.first}));
					dp[v.first][1] = val;
					pq.insert({dp[v.first][1], v.first});
				}

			}
		}
	}
	return 1e9;
}




int main(){
	scanf("%lld%lld%lld", &n, &m, &k);
	for(long long i = 0; i < m; i++){
		long long a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}
	for(long long i = 0; i < k; i++) scanf("%lld", arr + i);
	printf("%lld\n", solve());
}