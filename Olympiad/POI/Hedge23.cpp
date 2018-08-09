#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1111

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int arr[maxn][maxn];
char ver[maxn][maxn], hor[maxn][maxn];
bool used_ver[maxn][maxn], used_hor[maxn][maxn];
int root[maxn * maxn];

vector<vector<int> > edges;

int rooting(int x){
	if(root[x] == x)
		return x;
	return root[x] = rooting(root[x]);
}


int main(){
	int n, m, ans = 0, cnt = 0;
	scanf("%d%d", &m, &n);

	for(int i = 0; i < m; i++){
		scanf("%s", ver[i]);
		for(int j = 0; j < n - 1; j++){
			vector<int> v(6, 0);
			v[0] = (ver[i][j] == 'C');
			v[1] = 0;
			v[2] = i;
			v[3] = j;
			v[4] = n * i + j;
			v[5] = n * i + j + 1;
			edges.pb(v);

			ans += (ver[i][j] == 'C');
			cnt++;
		}
	}

	for(int i = 0; i < m - 1; i++){
		scanf("%s", hor[i]);
		for(int j = 0; j < n; j++){
			vector<int> v(6, 0);
			v[0] = (hor[i][j] == 'C');
			v[1] = 1;
			v[2] = i;
			v[3] = j;
			v[4] = n * i + j;
			v[5] = n * (i + 1) + j;
			edges.pb(v);

			ans += (hor[i][j] == 'C');
			cnt++;
		}
	}

	for(int i = 0; i < maxn * maxn; i++)
		root[i] = i;

	sort(edges.begin(), edges.end());

	for(vector<int> e : edges){
		int a = e[4];
		int b = e[5];
		int cost = e[0];

		int ra = rooting(a);
		int rb = rooting(b);

		if(ra != rb){
			root[ra] = rb;
			ans -= cost;
			cnt--;

			if(e[1] == 0)
				used_ver[e[2]][e[3]] = 1;

			if(e[1] == 1)
				used_hor[e[2]][e[3]] = 1;
		}
	}

	printf("%d %d\n", cnt, ans);

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n - 1; j++)
			printf("%c", used_ver[i][j] ? '.' : 'Z');
		printf("\n");	
	}

	for(int i = 0; i < m - 1; i++){
		for(int j = 0; j < n; j++)
			printf("%c", used_hor[i][j] ? '.' : 'Z');
		printf("\n");
	}

	return 0;
}