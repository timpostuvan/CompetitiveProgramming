#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1011

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int n, m;
int pos_x, pos_y;
int arr[10][10];
char str[10][10];

bool dist(int i, int j, int l, int r, int u, int d){
	if(abs(j - l) > 2)
		return 0;

	if(abs(r - j) > 2)
		return 0;

	if(abs(i - u) > 2)
		return 0;

	if(abs(d - i) > 2)
		return 0;

	return 1;
}

bool check(int cur){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(i + 2 < n && j + 2 < m){
				if(arr[i][j] == cur && arr[i][j] == arr[i + 1][j + 1] && arr[i][j] == arr[i + 2][j + 2])
					return 1;
			}

			if(i + 2 < n && j - 2 >= 0){
				if(arr[i][j] == cur && arr[i][j] == arr[i + 1][j - 1] && arr[i][j] == arr[i + 2][j - 2])
					return 1;
			}

			if(i + 2 < n){
				if(arr[i][j] == cur && arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j])
					return 1;
			}

			if(j + 2 < m){
				if(arr[i][j] == cur && arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2])
					return 1;
			}
		}
	}
	return 0;
}

int fun(bool is_first, int cur){							// 0 - lose, 1 - draw, 2 - win
	int l = 10, r = -1, u = 10, d = -1, cnt = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(arr[i][j] == 1 || arr[i][j] == 2){
				l = min(l, j);
				r = max(r, j);
				u = min(u, i);
				d = max(d, i);
				cnt++;
			}
		}
	}

	if(cnt == 9)
		return 1;

	int ret = 3;
	for(int i = 0; i < n && ret != 0; i++){
		for(int j = 0; j < m && ret != 0; j++){
			if(arr[i][j] == 0 && str[i][j] == '.' && dist(i, j, l, r, u, d)){
				arr[i][j] = cur;	

				if(check(cur)){
					arr[i][j] = 0;
					ret = 0;
					if(is_first){
						pos_x = i + 1;
						pos_y = j + 1; 
					}
					break;
				}	

			

				int tren = fun(0, 3 - cur);
				if(tren < ret){
					ret = tren;
					if(is_first){
						pos_x = i + 1;
						pos_y = j + 1; 
					}
				}

				arr[i][j] = 0;
			}
		}
	}
	return 2 - ret;
}


int main(){
	scanf("%d%d", &n, &m);

	int num_o = 0, num_x = 0;
	for(int i = 0; i < n; i++){
		scanf("%s", str[i]);
		for(int j = 0; j < m; j++){
			if(str[i][j] == '.'){
				arr[i][j] = 0;
			}


			if(str[i][j] == 'O'){
				arr[i][j] = 1;
				num_o++;
			}

			if(str[i][j] == 'X'){
				arr[i][j] = 2;
				num_x++;
			}
		}
	}

	int start = 2;			// 1 - O, 2 - X
	if(num_o < num_x)
		start = 1;

	cout << fun(1, start) << endl;

	printf("%d %d\n", pos_x, pos_y);
	return 0;
}