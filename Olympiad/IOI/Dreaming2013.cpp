#include "grader.h"
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>

using namespace std;

vector<pair<int, int> > adj[111111];
vector<int> tree, cur;
bool used[111111];
int n, m, l, solution;
int w[111111], prej[111111];
pair<int, int> naj;

void DFS(int x){
	cur.push_back(x);
	used[x] = 1;
	for(pair<int, int> i : adj[x]){
		if(w[i.first] == -1){
			w[i.first] = w[x] + i.second;
			prej[i.first] = x;
			DFS(i.first);
		}
	}

	if(w[x] >= naj.first){
		naj.first = w[x];
		naj.second = x;
	}
}

void COMPONENT(int x){
	naj = {-1, -1};
	w[x] = 0;
	DFS(x);
	for(int i = 0; i < cur.size(); i++) w[cur[i]] = -1;
	cur.clear();
	prej[naj.second] = -1;
	w[naj.second] = 0;
	DFS(naj.second);
	cur.clear();
	int tren = naj.second;
	int ans = (1 << 29);
	while(tren != -1){
		ans = min(ans, max(abs(naj.first - w[tren]), w[tren]));
		tren = prej[tren];
	}
	tree.push_back(ans);
	solution = max(solution, naj.first);
}

int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
	solution = -1;
	memset(w, -1, sizeof(w));
	n = N; m = M; l = L;
	for(int i = 0; i < M; i++){
		adj[A[i]].push_back({B[i], T[i]});
		adj[B[i]].push_back({A[i], T[i]});
	}

	for(int i = 0; i < N; i++){
		if(!used[i]) COMPONENT(i);
	}

	sort(tree.begin(), tree.end());
	reverse(tree.begin(), tree.end());
	if(tree.size() == 1) solution = max(solution, tree[0]);
	if(tree.size() == 2) solution = max(solution, tree[0] + tree[1] + l);
	if(tree.size() >= 3) solution = max(solution, max(tree[0] + tree[1] + l, tree[1] + tree[2] + 2 * l));
	return solution;
}