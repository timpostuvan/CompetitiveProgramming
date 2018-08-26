/*
Idea:
- https://ceoi2018.pl/wp-content/uploads/2018/08/solutions_day1.pdf (Lottery)
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 10011
#define maxq 101

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int ans[maxq][maxn];
int arr[maxn];
int pos[maxn];

int ind[maxq];
vector<pii> v;

int main(){
	int n, l;
	scanf("%d%d", &n, &l);
	for(int i = 1; i <= n; i++)
		scanf("%d", arr + i);

	int q;
	scanf("%d", &q);
	for(int i = 0; i < q; i++){
		int a;
		scanf("%d", &a);
		v.pb(mp(a, i));
	}

	sort(v.begin(), v.end());
	for(int i = 0; i < v.size(); i++){
		int a = v[i].fi;
		int b = v[i].se;
		ind[b] = i;	
	}

	int r = 0;
	for(int i = 0; i < maxn; i++){
		while(r < q && v[r].fi < i)
			r++;

		if(r < q)
			pos[i] = r;
		else
			pos[i] = -1;
	}

	for(int raz = 1; 1 + raz + l - 1 <= n; raz++){
		int diff = 0;
		for(int i = 1; i <= l; i++)
			diff += (arr[i] != arr[i + raz]);

		int a = pos[diff];
		if(a != -1){
			ans[a][1]++;
			ans[a][1 + raz]++;
		}

		for(int i = 2; i + raz + l - 1 <= n; i++){
			diff -= (arr[i - 1] != arr[i + raz - 1]);
			diff += (arr[i + l - 1] != arr[i + raz + l - 1]);
			
			int a = pos[diff];
			if(a != -1){
				ans[a][i]++;
				ans[a][i + raz]++;
			}
		}
	}

	int num = n - l + 1;
	for(int i = 1; i < q; i++){
		for(int j = 1; j <= num; j++)
			ans[i][j] += ans[i - 1][j];
	}

	for(int i = 0; i < q; i++){
		for(int j = 1; j <= num; j++)
			printf("%d ", ans[ind[i]][j]);
		printf("\n");
	}

	return 0;
}