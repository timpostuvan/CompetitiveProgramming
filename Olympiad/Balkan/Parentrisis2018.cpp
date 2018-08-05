#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 1000111

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

char str[maxn];
int col[maxn]; // 0 - red, 1 - blue, 2 - green
int val[3];

void solve(){
	val[0] = val[1] = 1;
	val[2] = 2;

	queue<int> open, close;
	int n; bool can = 1;

	scanf("%s", str);
	n = strlen(str);

	for(int i = 0; i < n; i++)
		col[i] = 0;

	int balance = 0;
	for(int i = 0; i < n; i++){
		if(str[i] == '('){
			balance += val[col[i]];
			open.push(i);
		}

		if(str[i] == ')')
			balance -= val[col[i]];

		if(balance < 0){
			if(open.empty()){
				can = 0;
				break;
			}

			int x = open.front();
			open.pop();

			balance++;
			col[i] = 1;
			col[x] = 2;
		}
	}

	balance = 0;
	for(int i = n - 1; i >= 0; i--){
		if(str[i] == '(')
			balance -= val[col[i]];

		if(str[i] == ')'){
			balance += val[col[i]];
			close.push(i);
		}

		if(balance < 0){
			if(close.empty()){
				can = 0;
				break;
			}

			int x = close.front();
			close.pop();

			balance++;
			col[i] = 1;
			col[x] = 2;
		}
	}

	if(balance != 0 || !can){
		printf("impossible\n");
		return;
	} 

	for(int i = 0; i < n; i++){
		if(col[i] == 0)
			printf("R");
		
		if(col[i] == 1)
			printf("B");

		if(col[i] == 2)
			printf("G");
	}

	printf("\n");
}


int main(){
	int t;
	scanf("%d", &t);
	while(t--)
		solve();

	return 0;
}