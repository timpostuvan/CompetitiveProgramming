/*
Idea:
- http://www.boi2011.ro/resurse/tasks/trapezoid-sol.pdf (similar but with segment tree)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (30013)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int a[maxn], b[maxn], c[maxn], d[maxn];
int dp[maxn], num[maxn];
pii seg[4 * maxn];

vector<int> va, vc;
vector<vector<int> > v;

void combine(pii &x, pii &l, pii &d){
	x.fi = max(l.fi, d.fi);
	x.se = 0;

	if(x.fi == l.fi)
		x.se = (x.se + l.se) % MOD;

	if(x.fi == d.fi)
		x.se = (x.se + d.se) % MOD;
	
	if(x.fi == 0)
		x.se = 1;
}

void build(int x, int l, int d){
	if(l > d)
		return;

	if(l == d){
		seg[x] = mp(0, 1);
		return;
	}

	int mid = (l + d) / 2;
	build(2 * x, l, mid);
	build(2 * x + 1, mid + 1, d);
	combine(seg[x], seg[2 * x], seg[2 * x + 1]);
}

void update(int x, int l, int d, int i, int val, int cnt){
	if(l > d || l > i || d < i)
		return;

	if(l == d && l == i){
		if(val == seg[x].fi)
			seg[x].se = (seg[x].se + cnt) % MOD;
		else
			seg[x] = max(seg[x], mp(val, cnt));
		return;
	}

	int mid = (l + d) / 2;
	update(2 * x, l, mid, i, val, cnt);
	update(2 * x + 1, mid + 1, d, i, val, cnt);
	combine(seg[x], seg[2 * x], seg[2 * x + 1]);
}

pii query(int x, int l, int d, int i, int j){
	if(l > d || l > j || d < i)
		return mp(0, 1);

	if(i <= l && d <= j)
		return seg[x];

	int mid = (l + d) / 2;
	pii lft = query(2 * x, l, mid, i, j);
	pii rgt = query(2 * x + 1, mid + 1, d, i, j);
	pii ret;
	combine(ret, lft, rgt);

	return ret;
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d%d%d", a + i, b + i, c + i, d + i);
		va.pb(a[i]);
		va.pb(b[i]);
		vc.pb(c[i]);
		vc.pb(d[i]);
	}

	sort(va.begin(), va.end());
	sort(vc.begin(), vc.end());

	for(int i = 1; i <= n; i++){
		a[i] = lower_bound(va.begin(), va.end(), a[i]) - va.begin() + 1;
		b[i] = lower_bound(va.begin(), va.end(), b[i]) - va.begin() + 1;
		c[i] = lower_bound(vc.begin(), vc.end(), c[i]) - vc.begin() + 1;
		d[i] = lower_bound(vc.begin(), vc.end(), d[i]) - vc.begin() + 1;
		v.pb({a[i], c[i], 0, i});
		v.pb({b[i], d[i], 1, i});
	}
	sort(v.begin(), v.end());

	build(1, 1, 2 * n);
	for(int i = 0; i < v.size(); i++){
		int pos = v[i][1];
		int t = v[i][2]; 
		int ind = v[i][3];

		if(t == 0){
			pii cur = query(1, 1, 2 * n, 1, pos - 1);
			dp[ind] = cur.fi + 1;
			num[ind] = cur.se;
		}

		if(t == 1)
			update(1, 1, 2 * n, pos, dp[ind], num[ind]);
	}

	int max_ans = 0;
	for(int i = 1; i <= n; i++)
		max_ans = max(max_ans, dp[i]);

	int num_ans = 0;
	for(int i = 1; i <= n; i++){
		if(dp[i] == max_ans)
			num_ans = (num_ans + num[i]) % MOD;
	}

	printf("%d %d\n", max_ans, num_ans);
	return 0;
}