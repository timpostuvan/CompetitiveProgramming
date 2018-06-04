/*
Idea:
- https://codeforces.com/blog/entry/59650
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 300111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

struct circle{
	ll x, y, r;
	int ind;
} c[maxn], a[maxn];

bool used[maxn];
int ans[maxn], order[maxn];
int n, cur_r, next_r;

bool operator<(circle a, circle b){
	if(a.x == b.x)	
		return a.y < b.y;

	return a.x < b.x;
}

bool comp(int x, int y){
	if(a[x].r == a[y].r)
		return a[x].ind < a[y].ind;

	return a[x].r > a[y].r;
}

void rescale(){
	cur_r = next_r;
	next_r = cur_r / 2;

	for(int i = 1; i <= n; i++){
		int cur = c[i].ind;
		c[i].x = a[cur].x / cur_r;
		c[i].y = a[cur].y / cur_r;
	}

	sort(c + 1, c + 1 + n);
}

bool intersection(circle &a, circle &b){
	ll dist_center = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	ll dist_r = (a.r + b.r) * (a.r + b.r);
	return dist_center <= dist_r;
}

void solve(int cur){
	int pos_x = a[cur].x / cur_r;
	int pos_y = a[cur].y / cur_r;

	ans[cur] = cur;
	used[cur] = 1;

	for(int cur_x = pos_x - 2; cur_x <= pos_x + 2; cur_x++){
		int it = lower_bound(c + 1, c + 1 + n, (circle) {cur_x, pos_y - 2, -1, -1}) - c;
		while(it <= n && c[it].x == cur_x && c[it].y <= pos_y + 2){
			if(!used[c[it].ind] && intersection(a[c[it].ind], a[cur])){
				ans[c[it].ind] = cur;
				used[c[it].ind] = 1;
			}
			it++;
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		ll x, y, r;
		scanf("%lld%lld%lld", &x, &y, &r);
		a[i] = c[i] = {x, y, r, i};
		order[i] = i;
	}
	
	sort(order + 1, order + 1 + n, comp);

	next_r = a[order[1]].r; 
	rescale();

	for(int i = 1; i <= n; i++){
		if(used[order[i]])
			continue;

		if(a[order[i]].r <= next_r)
			rescale();

		solve(order[i]);
	}

	for(int i = 1; i <= n; i++)
		printf("%d ", ans[i]);

	return 0;
}