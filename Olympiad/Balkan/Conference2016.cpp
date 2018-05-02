#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define maxn 1000011

typedef long long ll;
typedef long double ld;

int meet[maxn][2];
int jour[maxn], disc[maxn];
int first[maxn], fjour[maxn];
pair<int, int> last[maxn];

int main(){
	memset(first, -1, sizeof(first));
	memset(fjour, -1, sizeof(fjour));
	
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i++)
		scanf("%d%d", meet[i] + 0, meet[i] + 1);

	for(int i = k + 1; i <= n; i++)
		jour[i] = 1;

	for(int i = m; i >= 1; i--){
		int a = meet[i][0];
		int b = meet[i][1];
		int maks = max(jour[a], jour[b]);
		jour[a] = jour[b] = maks;

		if(a <= k && jour[a] == 1 && first[a] == -1)
			first[a] = i;

		if(b <= k && jour[b] == 1 && first[b] == -1)
			first[b] = i;
	}

	for(int i = 1; i <= m; i++){
		int a = meet[i][0];
		int b = meet[i][1];
		if(a <= k && first[a] <= i)
			disc[a] = 1;

		if(b <= k && first[b] <= i)
			disc[b] = 1;

		int maks = max(disc[a], disc[b]);
		disc[a] = disc[b] = maks;
	}

	for(int i = 1; i <= n; i++){
		if(i <= k)
			last[i] = mp(-1, 1e9);
		else 
			last[i] = mp(i, -1);
	}


	for(int i = m; i >= 1; i--){
		int a = meet[i][0];
		int b = meet[i][1];

		if(a <= k && b > k)
			last[a] = mp(b, i);

		if(b <= k && a > k)
			last[b] = mp(a, i);

		if(a <= k && b <= k && last[b].se < last[a].se)
			last[a] = last[b];

		if(a <= k && b <= k && last[a].se < last[b].se)
			last[b] = last[a];

		if(a <= k && first[a] <= i)
			fjour[a] = last[a].fi;

		if(b <= k && first[b] <= i)
			fjour[b] = last[b].fi;
	}

	for(int i = 1; i <= k; i++)
		printf("%d ", first[i]);
	printf("\n");

	vector<int> v;
	for(int i = k + 1; i <= n; i++){
		if(disc[i])
			v.pb(i);
	}
	printf("%d ", (int) v.size());
	for(int i : v)
		printf("%d ", i);

	printf("\n");

 	for(int i = 1; i <= k; i++){
		printf("%d ", fjour[i]);
	}
	printf("\n");
	return 0;
}