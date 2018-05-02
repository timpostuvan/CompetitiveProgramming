//#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 9)
#define maxn 200111

typedef long long ll;
typedef long double ld;

int pre[maxn];

struct BIT{
	int tree[maxn], n;

	void add(int ind, int val){
		while(ind <= n){
			tree[ind] += val;
			ind += (ind & -ind);
		}
	}

	int query(int ind){
		int ret = 0;
		while(ind){
			ret += tree[ind];
			ind -= (ind & -ind);
		}
		return ret;
	}

	int lbnd(int x){
		int p = 0;
		for(int i = n / 2; i; i >>= 1){
			if(tree[p + i] < x){
				x -= tree[p + i];
				p += i;
			}
		}
		return ++p;
	}

	void buildbit(int x){
		for(n = 1; n <= x; n <<= 1)
		memset(tree, 0, sizeof(tree));
		for(int i = 1; i <= x; i++)
			add(i, 1);
	}

	void buildseg(int x, int *k, int r){
		for(n = 1; n <= x; n <<= 1)
		memset(tree, 0, sizeof(tree));
		for(int i = 0; i < x; i++)
			if(k[i] > r)
				add(i + 1, 1);
	}
}bit, seg;

int GetBestPosition(int n, int c, int r, int *k, int *s, int *e){
	for(int i = 0; i < c; i++){
		s[i]++;
		e[i]++;
	}

	bit.buildbit(n);
	seg.buildseg(n - 1, k, r);

	for(int i = 0; i < c; i++){
		int st = bit.lbnd(s[i]);
		int en = bit.lbnd(e[i] + 1) - 1;

		for(int j = e[i]; j > s[i]; j--)
			bit.add(bit.lbnd(j), -1);

		s[i] = st;
		e[i] = min(en, n) - 1;
		if(seg.query(e[i]) - seg.query(s[i] - 1) == 0){
			pre[s[i]]++;
			pre[e[i] + 1]--;
		}
	}

	for(int i = 1; i < n; i++)
		pre[i] += pre[i - 1];


	return (int) (max_element(pre + 1, pre + n) - pre - 1);
}


int arr[maxn], s[maxn], e[maxn];

int main(){
	int n, c, r;
	scanf("%d%d%d", &n, &c, &r);
	for(int i = 0; i < n - 1; i++){
		scanf("%d", arr + i);
	}
	for(int i = 0; i < c; i++){
		scanf("%d%d", s + i, e + i);
	}
	printf("%d\n", GetBestPosition(n, c, r, arr, s, e));
	return 0;
}