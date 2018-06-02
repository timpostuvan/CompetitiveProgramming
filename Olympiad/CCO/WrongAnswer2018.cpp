#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (2e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define n 100

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

vector<vector<int> > a;

int main(){
	a.resize(n + 3);
	for(int i = 0; i < n + 3; i++)
		a[i].resize(n + 3);

	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= n; j++)
			a[i][j] = 100;
	}

	a[1][2] = 1;
	a[2][3] = 1;
	a[1][3] = 1;

	for(int i = 1; i <= 100; i += 4){
		if(i + 3 <= n)
			a[i][i + 3] = 1;

		if(i + 4 <= n)
			a[i + 3][i + 4] = 1;
	}

	for(int i = 3; i <= 100; i += 4){
		if(i + 3 <= n)
			a[i][i + 3] = 1;

		if(i + 4 <= n)
			a[i + 3][i + 4] = 1;
	}

	printf("%d\n", n);
	for(int i = 1; i <= n - 1; i++){
		for(int j = i + 1; j <= n; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	} 

	return 0;
}