/*
Idea:
- http://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2016/2016-open-selling_rna-sol-en.pdf
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF ((int) 1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100011
#define maxch 2000111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int point[maxn][2], ans[maxn];
int adj[2][maxch][4], cnt[2], in[2][maxch], out[2][maxch];
int bit[maxch];
vector<int> leaf[2][maxch];
vector<vector<int> > q;

int val(char c){
	if(c == 'A')
		return 0;
	if(c == 'G')
		return 1;
	if(c == 'C')
		return 2;
	if(c == 'U')
		return 3;
}

void addTrie(int pos, int ind, string &s){
	int len = s.length();
	int x = 0;
	for(int i = 0; i < len; i++){
		int ch = val(s[i]);
		if(adj[pos][x][ch] == 0)
			adj[pos][x][ch] = ++cnt[pos];
		
		x = adj[pos][x][ch];
	}
	leaf[pos][x].pb(ind);
}

int findTrie(int pos, string &s){
	int len = s.length();
	int x = 0;
	for(int i = 0; i < len; i++){
		int ch = val(s[i]);
		if(adj[pos][x][ch] == 0)
			return -1;

		x = adj[pos][x][ch];
	}
	return x;
}

void DFS(int pos, int x){
	in[pos][x] = ++cnt[pos];
	for(int v : leaf[pos][x])
		point[v][pos] = cnt[pos];

	for(int i = 0; i < 4; i++){
		if(adj[pos][x][i])
			DFS(pos, adj[pos][x][i]);
	}
	out[pos][x] = cnt[pos];
}

void updateBIT(int x, int val){
	while(x < maxch){
		bit[x] += val;
		x += (x & -x);
	}
}

int sumBIT(int x){
	int ret = 0;
	while(x){
		ret += bit[x];
		x -= (x & -x);
	}
	return ret;
}

int main(){
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		string str;
		cin >> str;

		addTrie(0, i, str);
		reverse(str.begin(), str.end());
		addTrie(1, i, str);
	}

	cnt[0] = cnt[1] = 0;
	DFS(0, 0);
	DFS(1, 0);

	for(int i = 1; i <= n; i++)
		q.pb({point[i][0], point[i][1], -INF});

	for(int i = 1; i <= m; i++){
		string pre, suf;
		cin >> pre >> suf;
		reverse(suf.begin(), suf.end());
		
		int a = findTrie(0, pre);
		int b = findTrie(1, suf);

		if(a == -1 || b == -1)
			continue;

		q.pb({in[0][a] - 1, in[1][b] - 1, i});
		q.pb({in[0][a] - 1, out[1][b], -i});
		q.pb({out[0][a], in[1][b] - 1 , -i});
		q.pb({out[0][a], out[1][b] , i});
	}

	sort(q.begin(), q.end());

	for(vector<int> v : q){
		int pos = v[1];
		int ind = v[2];

		if(ind == -INF)
			updateBIT(pos, 1);
		
		else{
			int val = sumBIT(pos);
			if(ind > 0)
				ans[ind] += val;
			else
				ans[-ind] -= val;
		}
	}

	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);

	return 0;
}