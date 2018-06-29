/*
Idea:
- http://apio-olympiad.org/2009/apio2009-solutions.pdf
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF ((int) 2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111
#define logn 19

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;


pii p[maxn];
vector<pii> best;
set<pii> s;

int l[maxn], r[maxn];
int par[maxn][logn];
int n;

vector<int> ans;

bool comp(pii a, pii b){
	if(a.se == b.se)
		return a.fi > b.fi;

	return a.se < b.se;
}

int find_val(int l, int d){
	if(l > d)
		return 0;

	int pos = upper_bound(best.begin(), best.end(), mp(l, -1)) -> se;
	if(pos == n || p[pos].se > d)
		return 0;

	int ret = 1;
	for(int i = logn - 1; i >= 0; i--){
		if(par[pos][i] != n && p[par[pos][i]].se <= d){
			ret += (1 << i);
			pos = par[pos][i];
		}
	}
	return ret;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d%d", l + i, r + i);
		p[i] = mp(l[i], r[i]);
	}

	sort(p, p + n, comp);
	for(int i = 0; i < n; i++){
		if(best.size() && best.back().fi >= p[i].fi)
			continue;

		best.pb(mp(p[i].fi, i));
	}
	best.pb(mp(INF, n));

	int ind = 0;
	for(int i = 0; i < n; i++){
		while(ind < n && p[i].se >= p[ind].fi)
			ind++;

		par[i][0] = ind;
	}

	par[n][0] = n;
	for(int j = 1; j < logn; j++){
		par[n][j] = n;
		for(int i = 0; i < n; i++)
			par[i][j] = par[par[i][j - 1]][j - 1];
	}

	s.insert(mp(-1, 1e9));
	for(int i = 0; i < n; i++){
		auto it = s.upper_bound(mp(l[i], INF));
		it--;
		pii cur = *it;

		if(cur.se < r[i])
			continue;

		int val1 = find_val(cur.fi, cur.se);
		int val2 = find_val(cur.fi, l[i] - 1) + find_val(r[i] + 1, cur.se) + 1;
		if(val1 != val2)
			continue;

		s.erase(it);
		if(cur.fi <= l[i] - 1)
			s.insert(mp(cur.fi, l[i] - 1));

		if(r[i] + 1 <= cur.se)
			s.insert(mp(r[i] + 1, cur.se));

		ans.pb(i + 1);
	}

	printf("%d\n", (int) ans.size());
	for(int v : ans)
		printf("%d ", v);

	return 0;
}