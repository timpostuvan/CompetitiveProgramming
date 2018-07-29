/*
Idea:
- https://codeforces.com/blog/entry/51010 (port facility)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF ((int) 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int ind[2 * maxn], s[maxn], e[maxn], col[maxn];
int n;

struct seg{
	int seg[8 * maxn];

	void build(int x, int l, int d){
		if(l > d)
			return;
		if(l == d){
			seg[x] = -INF;
			return;
		}
		int mid = (l + d) / 2;
		build(2 * x, l, mid);
		build(2 * x + 1, mid + 1, d);
		seg[x] = max(seg[2 * x], seg[2 * x + 1]);
	}

	void update(int x, int l, int d, int i, int j){
		if(l > d)
			return;
		if(l == d && l == i){
			seg[x] = j;
			return;
		}
		int mid = (l + d) / 2;
		if(i <= mid)
			update(2 * x, l, mid, i, j);
		else
			update(2 * x + 1, mid + 1, d, i, j);
		seg[x] = max(seg[2 * x], seg[2 * x + 1]);
	}

	int query(int x, int l, int d, int i, int j){
		if(l > d || d < i || j < l)
			return -INF;
		
		if(i <= l && d <= j)
			return seg[x];

		int mid = (l + d) / 2;
		int ret;
		if(j <= mid)
			return query(2 * x, l, mid, i, j);

		if(mid < i)
			return query(2 * x + 1, mid + 1, d, i, j);

		ret = max(query(2 * x, l, mid, i, j), query(2 * x + 1, mid + 1, d, i, j));
		return ret;
	}
}seg1, seg2;

void DFS(int x, int c){
	col[x] = c;
	while(1){
		int t = seg1.query(1, 1, 2 * n, s[x] + 1, e[x] - 1);
		if(t <= e[x])
			break;

		int v = ind[t];
		seg1.update(1, 1, 2 * n, s[v], -1);
		seg2.update(1, 1, 2 * n, e[v], -INF);
		DFS(v, 3 - c);
	}

	while(1){
		int t = -seg2.query(1, 1, 2 * n, s[x] + 1, e[x] - 1);
		if(t >= s[x])
			break;

		int v = ind[t];
		seg1.update(1, 1, 2 * n, s[v], -1);
		seg2.update(1, 1, 2 * n, e[v], -INF);
		DFS(v, 3 - c);
	}
}

bool check(vector<pii> &v){
	sort(v.begin(), v.end());
	stack<pii> st;
	for(int i = 0; i < v.size(); i++){
		while(!st.empty() && st.top().se < v[i].fi)
			st.pop();

		if(!st.empty() && st.top().se > v[i].fi && st.top().se < v[i].se)
			return 0;

		st.push(v[i]);
	}
	return 1;
}

int main(){
	scanf("%d", &n);
	seg1.build(1, 1, 2 * n);
	seg2.build(1, 1, 2 * n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d", s + i, e + i);
		ind[s[i]] = ind[e[i]] = i;
		seg1.update(1, 1, 2 * n, s[i], e[i]);
		seg2.update(1, 1, 2 * n, e[i], -s[i]);
	}

	ll ans = 1;
	for(int i = 1; i <= 2 * n; i++){
		if(!col[ind[i]]){
			ans = (ans * 2LL) % MOD;
			seg1.update(1, 1, 2 * n, s[ind[i]], -1);
			seg2.update(1, 1, 2 * n, e[ind[i]], -INF);
			DFS(ind[i], 1);
		}
	}

	vector<pii> l, r;
	for(int i = 1; i <= n; i++){
		if(col[i] == 1)
			l.pb(mp(s[i], e[i]));
		else
			r.pb(mp(s[i], e[i]));
	}

	if(!check(l) || !check(r))
		ans = 0;

	printf("%lld\n", ans);

	return 0;
}