#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 200111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

map<string, int> m;

int n;
int par[maxn], in[maxn];
bool used[maxn];
int ans, free_nodes;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int cnt = 0;
	cin >> n;

	if(n % 2 == 1){
		cout << "-1" << endl;
		return 0;
	}

	for(int i = 1; i <= n; i++){
		string a, b;
		cin >> a >> b;
		int x, y;

		if(m.count(a) == 0)
			m[a] = ++cnt;

		if(m.count(b) == 0)
			m[b] = ++cnt;

		x = m[a];
		y = m[b];

		if(x == y)
			continue;

		par[x] = y;
		in[y]++;
	}


	for(int i = 1; i <= n; i++){		// eliminate relationships
		if(used[i])
			continue;

		if(par[par[i]] == i){
			used[i] = 1;
			used[par[i]] = 1;
		}
	}

	queue<int> q;

	used[0] = 1;
	for(int i = 1; i <= n; i++){
		if(!used[i] && in[i] == 0)
			q.push(i);
	}

	while(!q.empty()){
		int x = q.front();
		q.pop();

		if(used[x])
			continue;

		used[x] = 1;

		if(used[par[x]])
			free_nodes++;
		
		else{
			ans++;

			used[par[x]] = 1;
			in[par[x]]--;
			in[par[par[x]]]--;

			if(in[par[par[x]]] == 0)
				q.push(par[par[x]]);
		}
	}

	for(int i = 1; i <= n; i++){
		if(!used[i]){
			int x = i;
			int num = 0;

			while(!used[x]){
				used[x] = 1;
				num++;
				x = par[x];
			}

			ans += num / 2;
			free_nodes += num % 2;
		}
	}

	ans += free_nodes;
	cout << ans << endl;
	
	return 0;
}