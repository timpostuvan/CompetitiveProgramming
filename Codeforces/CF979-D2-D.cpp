#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111
#define SQRT 700

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

struct node{
	int let[2], val;
} t[maxn * 20 * 20];

int root[maxn / SQRT + 10][SQRT + 10], cnt;
bool used[maxn / SQRT + 10][SQRT + 10];
bool here[maxn];

void add_tree(int pos, int div, int x){
	used[pos][div] = 1;
	int cur = root[pos][div];
	for(int i = 18; i >= 0; i--){
		int nxt = ((x >> i) & 1);
		if(t[cur].let[nxt] == 0)
			t[cur].let[nxt] = ++cnt;

		cur = t[cur].let[nxt];
	}
	t[cur].val = x;
}


pair<int, int> find_best(int pos, int div, int x){
	int ret = 0;
	int cur = root[pos][div];
	for(int i = 18; i >= 0; i--){
		int nxt = ((x >> i) & 1);
		if(t[cur].let[1 - nxt]){
			ret ^= (1 << i);
			cur = t[cur].let[1 - nxt];
		}
		else
			cur = t[cur].let[nxt];		
	}
	return mp(ret, t[cur].val);
}

void add(int x){
	if(here[x])
		return;

	here[x] = 1;
	for(int i = 1; i < SQRT; i++){
		if(x % i == 0)
			add_tree(x / SQRT, i, x);
	}
}



int query(int x, int k, int s){
	if(x % k != 0)
		return -1;

	if(k >= SQRT){
		int ans = -1, vred = -1;
		for(int v = k; v < maxn && (x + v <= s); v += k){
			if(here[v]){
				if(ans < (v ^ x)){
					vred = v;
					ans = (v ^ x);
				}
			}
		}
		return vred;
	}

	if(k < SQRT){
		int maks = -1, ans = -1, vred = -1;
		for(int i = 0; i < (maxn / SQRT + 10); i++){
			if((i + 1) * SQRT > s - x){
				maks = i;
				break;
			}

			if(used[i][k]){
				pair<int, int> cur = find_best(i, k, x);
				if(ans < cur.fi){
					ans = cur.fi;
					vred = cur.se;
				}
			}
		}

		for(int i = 0; i < SQRT; i++){
			int v = maks * SQRT + i;
			if(v + x > s)
				break;


			if(v > 0 && here[v] && v % k == 0){
				if(ans < (v ^ x)){
					vred = v;
					ans = (v ^ x);
				}
			}
		}
		return vred;
	}
}


int main(){
	for(int i = 0; i < maxn / SQRT + 10; i++)
		for(int j = 0; j < SQRT + 10; j++)
			root[i][j] = ++cnt;

	int q;
	scanf("%d", &q);
	while(q--){
		int t, x, k, s;
		scanf("%d", &t);

		if(t == 1){
			scanf("%d", &x);
			add(x);
		}

		if(t == 2){
			scanf("%d%d%d", &x, &k, &s);
			printf("%d\n", query(x, k, s));
		}
	}
	return 0;
}