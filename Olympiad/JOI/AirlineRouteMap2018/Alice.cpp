#include "Alicelib.h"
#include <cassert>
#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

bool nxt[maxn];

vector<pii> v;

void Alice(int N, int M, int A[], int B[]){
	for(int i = 0; i < M; i++){
		if(A[i] > B[i])
			swap(A[i], B[i]);

		v.pb(mp(A[i], B[i]));
		if(A[i] + 1 == B[i])
			nxt[A[i]] = 1;
	}

	for(int i = 0; i < N; i++){
		if(!nxt[i]){
			v.pb(mp(i, i + 1));
			if(i != N - 1)
				v.pb(mp(i, N));
		}
	}

	InitG(N + 1, v.size());
	int cnt = 0;
	for(pii i : v){
		MakeG(cnt++, i.fi, i.se);
	//	printf("%d %d\n", i.fi, i.se);
	}
}