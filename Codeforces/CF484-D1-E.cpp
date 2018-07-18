/*
Idea:
- http://codeforces.com/blog/entry/14592
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1 << 20)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

struct node{
	int max_val, pre, suf, len;
	node(){
		max_val = pre = suf = len = 0;
	}
};

struct seg{
	seg *l, *d;
	node data;
	
	seg(){
		l = d = NULL;
		data = node();
	}
};

seg *root[maxn];
node NULL_RET;
int arr[maxn];
vector<pii> v;

seg *copy(seg *x){
	seg *ret = new seg();
	if(x){
		ret -> l = x -> l;
		ret -> d = x -> d;
		ret -> data = x -> data;
	}
	return ret;
}

node combine(node l, node d){
	node x;
	x.len = l.len + d.len;
	x.max_val = max(l.max_val, d.max_val);
	x.pre = l.pre;
	x.suf = d.suf;

	x.max_val = max(x.max_val, l.suf + d.pre);
	if(l.len == l.pre)
		x.pre = max(x.pre, l.pre + d.pre);
	
	if(d.len == d.suf)
		x.suf = max(x.suf, l.suf + d.suf);
	
	return x;
}

void build(seg *x, int l, int d){
	if(l > d)
		return;

	x -> data.len = d - l + 1;

	if(l == d)
		return;

	int mid = (l + d) / 2;
	x -> l = new seg();
	x -> d = new seg();
	build(x -> l, l, mid);
	build(x -> d, mid + 1, d);
}

void update(seg *x, int l, int d, int i){
	if(l > d || l > i || d < i)
		return;

	if(l == d && l == i){
		x -> data.max_val = 1;
		x -> data.pre = 1;
		x -> data.suf = 1;
		return;
	}

	int mid = (l + d) / 2; 
	if(i <= mid){
		x -> l = copy(x -> l);
		update(x -> l, l, mid, i);
	}
	else{
		x -> d = copy(x -> d);
		update(x -> d, mid + 1, d, i);
	}

	x -> data = combine(x -> l -> data, x -> d -> data);
}

node query(seg *x, int l, int d, int i, int j){
	if(l > d || l > j || d < i)
		return NULL_RET;

	if(i <= l && d <= j)
		return x -> data;

	int mid = (l + d) / 2;
	node lft = query(x -> l, l, mid, i, j);
	node rgt = query(x -> d, mid + 1, d, i, j);
	return combine(lft, rgt);
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", arr + i);
		v.pb(mp(arr[i], i));
	}

	sort(v.begin(), v.end());
	v.pb(mp(-1, -1));
	reverse(v.begin(), v.end());

	root[0] = new seg();
	build(root[0], 1, n);

	for(int i = 1; i <= n; i++){
		root[i] = copy(root[i - 1]);
		update(root[i], 1, n, v[i].se);
	}

	int q;
	scanf("%d", &q);
	while(q--){
		int i, j, w;
		scanf("%d%d%d", &i, &j, &w);

		int l = 1, d = n, mid, ans = -1;
		while(l <= d){
			mid = (l + d) / 2;
			node cur = query(root[mid], 1, n, i, j);

			if(cur.max_val >= w){
				ans = mid;
				d = mid - 1;
			}
			else
				l = mid + 1;
		}
		printf("%d\n", v[ans].fi);
	}

	return 0;
}