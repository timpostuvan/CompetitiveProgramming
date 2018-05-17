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


int main(){
	int n;
	string str;
	cin >> n >> str;

	str = "0" + str + "0";

	bool ok = 1;
	for(int i = 1; i <= n; i++){
		if(str[i] == '0' && str[i + 1] == '0' && str[i - 1] == '0')
			ok = 0;

		if(str[i] == '1' && str[i - 1] == '1')
			ok = 0;
	}

	if(ok)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	
	return 0;
}