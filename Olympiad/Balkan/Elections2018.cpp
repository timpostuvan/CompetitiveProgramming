/*
Idea:
- https://csacademy.com/contest/round-85/task/elections/solution/
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (int) (2 * 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 500111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

char s[maxn];
int arr[maxn], ans[maxn];
vector<int> stk;
vector<pii> query[maxn];

struct node{
	int val, sum;

	node(int a = 0, int b = 0){
		val = min(a, 0);
		sum = b;
	}
};

struct segtree{
	node seg[4 * maxn];

	node combine(node a, node b){
		return node(min(a.val + b.sum, b.val), a.sum + b.sum);
	}

	void build(int x, int l, int d){
		if(l > d)
			return;

		if(l == d){
			seg[x] = node(0, 1);
			return;
		}

		int mid = (l + d) / 2;
		build(2 * x, l, mid);
		build(2 * x + 1, mid + 1, d);
		seg[x] = combine(seg[2 * x], seg[2 * x + 1]);
	}

	void update(int x, int l, int d, int i, int num){
		if(l > d || l > i || d < i)
			return;

		if(l == d && i == l){
			seg[x] = node(num, num);
			return;
		}

		int mid = (l + d) / 2;
		update(2 * x, l, mid, i, num);
		update(2 * x + 1, mid + 1, d, i, num);
		seg[x] = combine(seg[2 * x], seg[2 * x + 1]);
	}

	node query(int x, int l, int d, int i, int j){
		if(l > d || l > j || d < i)
			return node(INF, 0);

		if(i <= l && d <= j)
			return seg[x];

		int mid = (l + d) / 2;
		if(d <= mid)
			return query(2 * x, l, mid, i, j);

		if(mid < l)
			return query(2 * x + 1, mid + 1, d, i, j);

		return combine( query(2 * x, l, mid, i, j),
						query(2 * x + 1, mid + 1, d, i, j) );
	}
}seg;

int main(){
	int n, q;
	scanf("%d", &n);
	scanf("%s", s);
	for(int i = 0; i < n; i++)
		arr[i + 1] = (s[i] == 'C') ? 1 : -1;

	scanf("%d", &q);	
	for(int i = 0; i < q; i++){
		int l, d;
		scanf("%d%d", &l, &d);
		query[l].pb(mp(d, i));
	}

	seg.build(1, 1, n);

	for(int i = n; i >= 1; i--){
		if(arr[i] == 1){
			if(stk.size()){
				seg.update(1, 1, n, stk.back(), -1);
				stk.pop_back();
			}
		}
		else{
			stk.pb(i);
			seg.update(1, 1, n, i, 0);
		}

		for(pii cur : query[i]){
			int d = cur.fi;
			int ind = cur.se;

			ans[ind] = upper_bound(stk.rbegin(), stk.rend(), d) - stk.rbegin();
			ans[ind] += -seg.query(1, 1, n, i, d).val;
		}

	} 

	for(int i = 0; i < q; i++)
		printf("%d\n", ans[i]);
}