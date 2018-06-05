/*
Idea:
- dp[i] is the best answer if we have already connected first i sockets
- a socket can always be connected to the closest socket of other color
- we can also make a cluster of sockets where we have the same number of sockets of each color
(cost for a cluster can be easily computed using prefix sums)
- using the two methods above we cover all possible transitions of dp
*/

#include "wiring.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 500111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

vector<pll> arr;
vector<ll> b, r;
ll prer[maxn], preb[maxn], dp[maxn];
int prv[maxn], pos[maxn];

ll find_nearest(pll x){
	ll ret = INF;
	if(x.se == -1){
		auto it = lower_bound(b.begin(), b.end(), x.fi);
		if(it != b.end())
			ret = min(ret, *it - x.fi);

		if(it != b.begin()){
			it--;
			ret = min(ret, x.fi - *it);
		}
	}

	if(x.se == 1){
		auto it = lower_bound(r.begin(), r.end(), x.fi);
		if(it != r.end())
			ret = min(ret, *it - x.fi);

		if(it != r.begin()){
			it--;
			ret = min(ret, x.fi - *it);
		}
	}
	return ret;
}

long long min_total_length(vector<int> a, vector<int> c){
	int n = a.size() + c.size();

	arr.pb(mp(-1, 0));
	for(int x : a){
		r.pb(x);
		arr.pb(mp(x, -1));
	}

	for(int x : c){
		b.pb(x);
		arr.pb(mp(x, 1));
	}

	sort(arr.begin(), arr.end());
	memset(prv, -1, sizeof(prv));
	memset(pos, -1, sizeof(pos));

	prv[n] = 0;
	int balance = n;
	for(int i = 1; i <= n; i++){
		prer[i] = prer[i - 1];
		preb[i] = preb[i - 1];

		if(arr[i].se == -1){
			prer[i] += arr[i].fi;
			balance--;
		}

		if(arr[i].se == 1){
			preb[i] += arr[i].fi;
			balance++;
		}

		if(prv[balance] >= 0)
			pos[i] = prv[balance];

		prv[balance] = i;
	}

	dp[0] = 0;
	for(int i = 1; i <= n; i++){
		dp[i] = dp[i - 1] + find_nearest(arr[i]);
		if(pos[i] >= 0)
			dp[i] = min(dp[i], dp[pos[i]] + abs((prer[i] - prer[pos[i]]) - (preb[i] - preb[pos[i]])));
	}
	return dp[n];
}