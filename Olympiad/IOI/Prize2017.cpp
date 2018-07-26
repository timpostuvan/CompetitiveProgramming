/*
Idea:
- http://ioi2017.org/tasks/editorial/prize.pdf
*/

#include "prize.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 30)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 201111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

map<int, pii> m[maxn];
int ans;

pii ASK(int x){
	vector<int> v = ask(x);
	return mp(v[0], v[1]);
}

void solve(int l, int d){
	if(ans != -1 || l > d)
		return;

	int mid = (l + d) / 2;
	pii cur = ASK(mid);
	int sum = cur.fi + cur.se;
	if(sum == 0){
		ans = mid;
		return;
	}

	auto it = m[sum].upper_bound(mid);

	bool left = 1, right = 1;
	if(it != m[sum].begin()){
		it--;
		if(cur.se == it -> se.se)
			left = 0;
		it++;
	}

	if(it != m[sum].end()){
		if(cur.se == it -> se.se)
			right = 0;
	}

	m[sum][mid] = cur;
	if(left)
		solve(l, mid - 1);

	if(right)
		solve(mid + 1, d);
}

int find_best(int n){
	ans = -1;
	solve(0, n - 1);
	return ans;
}