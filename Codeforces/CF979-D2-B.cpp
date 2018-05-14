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

string str[4];
int arr[4][1000], maks[4], val[4];

int main(){
	int n;
	cin >> n;
	cin >> str[0] >> str[1] >> str[2];
	for(int k = 0; k < 3; k++){
		int len = str[k].length();
		for(int i = 0; i < len; i++)
			arr[k][str[k][i] - 'A']++;

		for(int i = 0; i < 1000; i++)
			maks[k] = max(maks[k], arr[k][i]); 

		if(maks[k] == str[k].length() && n == 1)
			maks[k]--;
		else
			maks[k] = min((int) str[k].length(), maks[k] + n);

		val[k] = maks[k];
	}

	sort(val, val + 3);

	if(val[1] == val[2]){
		printf("Draw\n");
		return 0;
	}

	if(maks[0] > maks[1] && maks[0] > maks[2]){
		printf("Kuro\n");
		return 0;
	}

	if(maks[1] > maks[0] && maks[1] > maks[2]){
		printf("Shiro\n");
		return 0;
	}

	if(maks[2] > maks[1] && maks[2] > maks[0]){
		printf("Katie\n");
		return 0;
	}








	return 0;
}