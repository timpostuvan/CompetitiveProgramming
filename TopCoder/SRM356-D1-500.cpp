/*
Idea:
- https://community.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm356
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 15

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

class MarriageProblemRevised{ 
	public:

	int can_men[1 << maxn], can_women[1 << maxn];
	int adj[2 * maxn];
	
	int neededMarriages(vector<string> arr){ 
		memset(can_women, 0, sizeof(can_women));
		memset(can_men, 0, sizeof(can_men));
		memset(adj, 0, sizeof(adj));

		int ans = INF;
		int n = arr.size();
		int m = arr[0].size();

		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				if(arr[i][j] == '1'){
					adj[i] |= (1 << j);
					adj[n + j] |= (1 << i);
				}
			}
		}

		for(int i = 0; i < n + m; i++){
			if(adj[i] == 0)
				return -1;
		}

		for(int i = 0; i < (1 << n); i++){
			for(int j = 0; j < n; j++){
				if((i >> j) & 1)
					can_women[i] |= adj[j];
			}
		}

		for(int i = 0; i < (1 << m); i++){
			for(int j = 0; j < m; j++){
				if((i >> j) & 1)
					can_men[i] |= adj[n + j];
			}
		}

		for(int men = 0; men < (1 << n); men++){
			for(int women = 0; women < (1 << m); women++){
				int cur_ans = __builtin_popcount(men) + __builtin_popcount(women);

				if(cur_ans >= ans)
					continue;

				int here_men = can_men[women], here_women = can_women[men];

				here_men |= men;
				here_women |= women;

				if(__builtin_popcount(here_women) == m && __builtin_popcount(here_men) == n)
					ans = min(ans, cur_ans);
			}
		}

		return ans;		
	}
};