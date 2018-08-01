/*
Idea:
- https://codeforces.com/blog/entry/51010 (long mansion)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF ((int) 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 500111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<int> v[maxn];
pii pos[maxn];
int pov[maxn], l[maxn], d[maxn], cur[maxn];
int n;

bool can(int t, int ind, pii x){
	if(ind < 1 || ind > n)
		return 0;

	if(t == 0){
		if(x.fi <= d[ind] && d[ind] <= x.se)
			return 1;
		return 0;
	}

	if(t == 1){
		if(x.fi <= l[ind] && l[ind] <= x.se)
			return 1;
		return 0;
	}
}

pii merge(pii &a, pii &b){
	return mp(min(a.fi, b.fi), max(a.se, b.se));
}

void solve(){
	for(int i = 0; i < maxn; i++)
		cur[i] = -1;

	for(int i = 1; i < n; i++){
		for(int x : v[i])
			cur[x] = i;

		l[i + 1] = cur[pov[i]];
	}

	for(int i = 0; i < maxn; i++)
		cur[i] = 2 * maxn;

	for(int i = n; i > 1; i--){
		for(int x : v[i])
			cur[x] = i;

		d[i - 1] = cur[pov[i - 1]];
	}

	for(int i = 1; i <= n; i++){
		pos[i] = mp(i, i);
		bool ok = 1;

		while(ok){
			bool left = can(0, pos[i].fi - 1, pos[i]);
			if(left)
				pos[i] = merge(pos[i], pos[pos[i].fi - 1]);

			bool right = can(1, pos[i].se + 1, pos[i]);
			if(right)
				pos[i].se++;

			ok = max(left, right);
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
		scanf("%d", pov + i);

	for(int i = 1; i <= n; i++){
		int num, x;
		scanf("%d", &num);
		while(num--){
			scanf("%d", &x);
			v[i].pb(x);
		}
	}

	solve();

	int q;
	scanf("%d", &q);
	while(q--){
		int x, y;
		scanf("%d%d", &x, &y);
		if(pos[x].fi <= y && y <= pos[x].se)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}