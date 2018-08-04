/*
Idea:
- https://codeforces.com/blog/entry/51010 (city)
*/

#include "Encoder.h"
#include <bits/stdc++.h>

using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxm 1000111
#define maxn 250111
#define maxk 252

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int first_over[maxm], a[maxk];
int l[maxn], len[maxn], cnt;
vector<int> adj[maxn];

void init(){
	cnt = 0;
	for(int i = 0; i < maxn; i++)
		adj[i].clear();

	a[1] = 1;
	for(int i = 2; i < maxk; i++){
		a[i] = (double) a[i - 1] * 1.05;
		a[i] = max(a[i], a[i - 1] + 1);
	}

	int ind = 1;
	for(int i = 1; i <= a[maxk - 1]; i++){
		while(a[ind] < i)
			ind++;

		first_over[i] = ind;
	}
}

void DFS(int x, int p){
	l[x] = ++cnt;
	for(int v : adj[x]){
		if(v == p)
			continue;

		DFS(v, x);
	}
	int num = first_over[cnt - l[x] + 1];
	cnt = l[x] + a[num] - 1;
	len[x] = num; 
}

void Encode(int N, int A[], int B[]){
	init();

	for(int i = 0; i < N - 1; i++){
		adj[A[i]].pb(B[i]);
		adj[B[i]].pb(A[i]);
	}

	DFS(0, -1);

	for(int i = 0; i < N; i++)
		Code(i, 1LL * len[i] * maxm + l[i]);
}