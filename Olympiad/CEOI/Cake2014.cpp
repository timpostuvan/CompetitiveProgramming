/*
Idea:
- http://ceoi2014.informatik-olympiade.de/wp-content/uploads/2014/06/cake-spoiler.pdf (segment tree)
*/

#include <bits/stdc++.h>
  
using namespace std;
  
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define INF (2e9)
#define maxn 250111
 
typedef long long ll;
typedef pair<int, int> pii;

set<pii> s;
int val[maxn], seg[4 * maxn];
int n, a;

struct segtree_right{
	int seg[4 * maxn];

	void update(int x, int l, int d, int i, int y){
		if(l > d || l > i || d < i)
			return;

		if(l == d && l == i){
			seg[x] = y;
			return;
		}

		int mid = (l + d) / 2;
		update(2 * x, l, mid, i, y);
		update(2 * x + 1, mid + 1, d, i, y);
		seg[x] = max(seg[2 * x], seg[2 * x + 1]);
	}

	int find_max(int x, int l, int d, int i, int j){
		if(l > d || l > j || d < i)
			return -1;

		if(i <= l && d <= j)
			return seg[x];

		int mid = (l + d) / 2;
		int ret = find_max(2 * x, l, mid, i, j);
		ret = max(ret, find_max(2 * x + 1, mid + 1, d, i, j));
		return ret;
	}

	int query(int x, int l, int d, int y){
		if(l > d)
			return -1;

		if(l == d){
			if(seg[x] <= y)
				return d + 1;
			else 
				return d;
		}

		int mid = (l + d) / 2;
		if(seg[2 * x] <= y)
			return query(2 * x + 1, mid + 1, d, y);
		
		if(seg[2 * x] > y)
			return query(2 * x, l, mid, y);
	}
} seg_right;

struct segtree_left{
	int seg[4 * maxn];

	void update(int x, int l, int d, int i, int y){
		if(l > d || l > i || d < i)
			return;

		if(l == d && l == i){
			seg[x] = y;
			return;
		}

		int mid = (l + d) / 2;
		update(2 * x, l, mid, i, y);
		update(2 * x + 1, mid + 1, d, i, y);
		seg[x] = max(seg[2 * x], seg[2 * x + 1]);
	}

	int find_max(int x, int l, int d, int i, int j){
		if(l > d || l > j || d < i)
			return -1;

		if(i <= l && d <= j)
			return seg[x];

		int mid = (l + d) / 2;
		int ret = find_max(2 * x, l, mid, i, j);
		ret = max(ret, find_max(2 * x + 1, mid + 1, d, i, j));
		return ret;
	}

	int query(int x, int l, int d, int y){
		if(l > d)
			return -1;

		if(l == d){
			if(seg[x] <= y)
				return d - 1;
			else 
				return d;
		}

		int mid = (l + d) / 2;
		if(seg[2 * x + 1] <= y)
			return query(2 * x, l, mid, y);
		
		if(seg[2 * x + 1] > y)
			return query(2 * x + 1, mid + 1, d, y);
	}
} seg_left;

int find_ans(int x){
	if(x < a){
		int maks = seg_left.find_max(1, 1, a - 1, x, a - 1);
		int pos = seg_right.query(1, a + 1, n, maks);
		int ret = pos - a + (a - x) - 1;
		return ret;
	}

	if(x > a){
		int maks = seg_right.find_max(1, a + 1, n, a + 1, x);
		int pos = seg_left.query(1, 1, a - 1, maks);
		int ret = a - pos + (x - a) - 1;
		return ret;
	}
}

void change(int x, int y){
	s.erase(mp(val[x], x));
	val[x] = y;
	s.insert(mp(val[x], x));
	if(x < a)
		seg_left.update(1, 1, a - 1, x, val[x]);

	if(x > a)
		seg_right.update(1, a + 1, n, x, val[x]);
}

int main(){
	scanf("%d%d", &n, &a);
	for(int i = 1; i <= n; i++){
		scanf("%d", val + i);
		s.insert(mp(val[i], i));
		if(i < a)
			seg_left.update(1, 1, a - 1, i, val[i]);

		if(i > a)
			seg_right.update(1, a + 1, n, i, val[i]);
	}

	int q;
	scanf("%d", &q);
	while(q--){
		char t[2];
		int x, y;
		scanf("%s%d", t, &x);
		
		if(t[0] == 'F'){
			if(x == a){
				printf("0\n");
				continue;
			}

			printf("%d\n", find_ans(x));
		}

		if(t[0] == 'E'){
			scanf("%d", &y);

			auto it = s.end();
			vector<int> cur;
			for(int i = 0; i < y - 1; i++){
				it--;
				cur.pb(it -> se);
			}
			it--;

			change(x, val[it -> se] + 1);

			for(int i : cur)
				change(i, val[i] + 1);
		}
	}
	return 0;
}