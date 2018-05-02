#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define INF (1LL << 55)
#define maxn 50111

typedef long long ll;

struct segtree{
	int adj[5][5];

	void init(){
		memset(adj, 0x3f, sizeof(adj));
	}	
	void set(int a, int b, int c){
		adj[a][b] = min(adj[a][b], c);
	}
};

segtree seg[4 * maxn];
int k, n, m, o;

segtree merge(segtree a, segtree b){
	segtree c;
	c.init();
	for(int i = 0; i < k; i++){
		for(int j = 0; j < k; j++){
			for(int l = 0; l < k; l++){
				c.adj[i][j] = min(c.adj[i][j], a.adj[i][l] + b.adj[l][j]);
			}
		}
	}
	return c;
}

void update(int x, int l, int d, int ll, int a, int b, int val){
	if(l == d && l == ll){
		seg[x].set(a, b, val);
		return;
	}
	int mid = (l + d) / 2;
	if(ll <= mid)
		update(2 * x, l, mid, ll, a, b, val);
	else
		update(2 * x + 1, mid + 1, d, ll, a, b, val);
}

void build(int x, int l, int d){
	if(l == d){ 		 // create tree from second level up (second level from bottom)
	/*	printf("%d %d\n", x, l);
		for(int i = 0; i < k; i++){
			for(int j = 0; j < k; j++)
				printf("%d ", seg[x].adj[i][j]);
			printf("\n");
		}
		printf("\n\n\n");		*/
		return;
	} 
	int mid = (l + d) / 2;
	build(2 * x, l, mid);
	build(2 * x + 1, mid + 1, d);
	seg[x] = merge(seg[2 * x], seg[2 * x + 1]);
}

segtree query(int x, int l, int d, int ll, int dd){
	if(ll <= l && d <= dd)
		return seg[x];

	int mid = (l + d) / 2;
	if(dd <= mid)
		return query(2 * x, l, mid, ll, dd);

	if(mid < ll){
		return query(2 * x + 1, mid + 1, d, ll, dd);
	}

	segtree leva = query(2 * x, l, mid, ll, dd);
	segtree desna = query(2 * x + 1, mid + 1, d, ll, dd);
	return merge(leva, desna);
}

int main(){
	for(int i = 0; i < 4 * maxn; i++)
		seg[i].init();

	scanf("%d%d%d%d", &k, &n, &m, &o);
	n = n / k + 1;
	for(int i = 0; i < m; i++){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		update(1, 1, n, a / k + 1, a % k, b % k, c);
	}	

	build(1, 1, n);

	while(o--){
		int a, b;
		scanf("%d%d", &a, &b);
		if(a / k >= b / k)
			printf("-1\n");
		else{
			segtree cur = query(1, 1, n, a / k + 1, b / k);
			int x = cur.adj[a % k][b % k];
			if(x > 1e9)
				x = -1;
			printf("%d\n", x);

		}
	}
	return 0;
}