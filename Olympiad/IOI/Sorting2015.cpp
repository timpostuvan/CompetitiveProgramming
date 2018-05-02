#include "sorting.h"
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <iostream>

using namespace std;

#define maxn 600011

int p[maxn], q[maxn], y[maxn], x[maxn], s[maxn], zac[maxn], kon[maxn], go[maxn], igo[maxn];
int cur1[maxn], cur2[maxn];

int n, m;

bool check(int mid){
	for(int i = 0; i < n; i++) {
		cur1[i] = s[i];
		cur2[i] = s[i];
	}
	for(int i = 0; i < mid; i++) swap(cur2[x[i]], cur2[y[i]]);
	for(int i = 0; i < n; i++){
		zac[cur1[i]] = i;
		kon[cur2[i]] = i;
	}
	
	for(int i = 0; i < n; i++) go[zac[i]] = kon[i];
	for(int i = 0; i < n; i++) igo[go[i]] = i;

	int a = 0;

	for(int i = 0; i < mid; i++){
		swap(cur1[x[i]], cur1[y[i]]);
		swap(go[x[i]], go[y[i]]);

		zac[cur1[x[i]]] = x[i];
		zac[cur1[y[i]]] = y[i];
		igo[go[x[i]]] = x[i];
		igo[go[y[i]]] = y[i];

		bool find = 0;

		while(!find && a < n){
			int val1, val2;
			val1 = zac[a];
			val2 = igo[a];

			if(val1 != val2){
				find = 1;
				p[i] = val1;
				q[i] = val2;

				swap(cur1[val1], cur1[val2]);
				zac[cur1[val1]] = val1;
				zac[cur1[val2]] = val2;
			}
			a++;
		} 
		if(!find){
			p[i] = 0;
			q[i] = 0;
		}
	}
	for(int i = 0; i < n; i++) if(cur1[i] != i) return 0;
	return 1; 
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
	n = N; m = M;
	for(int i = 0; i < n; i++) s[i] = S[i];
	for(int i = 0; i < m; i++){x[i] = X[i]; y[i] = Y[i];}

	int mid, l, d, ans = -1;
	l = 0; d = m;

	while(l <= d){
		mid = (l + d) / 2;
		if(check(mid)){
			ans = mid;
			d = mid - 1;
		}
		else l = mid + 1;
	}

	check(ans);
	for(int i = 0; i < ans; i++) {P[i] = p[i]; Q[i] = q[i];}
	return ans;
}