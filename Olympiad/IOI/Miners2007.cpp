#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>

using namespace std;

char str[111111];
int n, arr[111111];

int dp[2][4][4][4][4];

int val(int a, int b, int c){
	int tren = 0;
	if(a == 1 || b == 1 || c == 1) tren++;
	if(a == 2 || b == 2 || c == 2) tren++;
	if(a == 3 || b == 3 || c == 3) tren++;
	return tren;
}

int main(){
	scanf("%d%s", &n, str + 1);
	for(int i = 1; i <= n; i++){
		if(str[i] == 'B') arr[i] = 1;
		if(str[i] == 'F') arr[i] = 2;
		if(str[i] == 'M') arr[i] = 3;
	}

	int now = 0;
	int prev = 1;
	for(int i = n; i > 0; i--){
		for(int a1 = 0; a1 < 4; a1++){
			for(int a2 = 0; a2 < 4; a2++){
				for(int b1 = 0; b1 < 4; b1++){
					for(int b2 = 0; b2 < 4; b2++){
						dp[now][a1][a2][b1][b2] = max(dp[prev][arr[i]][a1][b1][b2] + val(a1, a2, arr[i]),
													  dp[prev][a1][a2][arr[i]][b1] + val(b1, b2, arr[i]));	
					}
				}
			}
		}
		swap(now, prev);
	}

	// at the now swaped with prev
	printf("%d\n", dp[prev][0][0][0][0]); 
}