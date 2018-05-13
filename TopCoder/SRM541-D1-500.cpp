/*
Idea:
- When we are searching for a pattern (with length len) in concatenation of 2 strings, 
we are only interested in first (len - 1) characters and last (len - 1) characters
- After some number of times whole thing becomes constant -> first (len - 1) characters and
last (len - 1) characters don't change anymore
*/

#include <bits/stdc++.h>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1e9)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 80

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

class AkariDaisukiDiv1{ 
	public:

	int b[maxn];
	void KMP_preprocess(string &p){
		int i = 0, j = -1, m = p.length();
		b[0] = -1;
		while(i < m){
			while(j >= 0 && p[i] != p[j])
				j = b[j];

			i++; j++;
			b[i] = j;
		}
	}

	int KMP_search(string &str, string &p){
		int i = 0, j = 0, n = str.length(), m = p.length(), ret = 0;
		while(i < n){
			while(j >= 0 && str[i] != p[j])
				j = b[j];

			i++; j++;
			if(j == m){
				ret++;
				j = b[j];
			}
		}
		return ret;
	}


	int countF(string a, string b, string c, string x, string p, int num){
		KMP_preprocess(p);
		int len = p.length() - 1;

		while(num && x.length() < len){
			x = a + x + b + x + c;
			num--;
		}

		ll ans = KMP_search(x, p);
		string left = x, mid, right = x;

		int till_circular = maxn;
		while(till_circular && num){
			string pre = left.substr(0, len);
			string suf = right.substr(right.length() - len, len);

			left = a + pre;
			mid = suf + b + pre;
			right = suf + c;

			ans = (2 * ans + KMP_search(left, p) + KMP_search(mid, p) + KMP_search(right, p)) % MOD;

			till_circular--; num--;
		}
		
		ll add = (KMP_search(left, p) + KMP_search(mid, p) + KMP_search(right, p)) % MOD;

		while(num--)
			ans = (2LL * ans + add) % MOD;

		return ans;
	}
};
/*

int main(){
	AkariDaisukiDiv1 problem;
	cout << problem.countF("vfsebgjfyfgerkqlr","ezbiwls","kjerx","jbmjvaawoxycfndukrjfg","bgjfyfgerkqlrvfsebgjfyfgerkqlrvfsebgjfyfgerkqlrvfs",0) << endl;
}
*/