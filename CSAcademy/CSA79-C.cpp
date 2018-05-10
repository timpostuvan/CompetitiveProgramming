#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF (1LL << 55)
#define MOD (1000 * 1000 * 1000 + 7)
#define maxn 100111

typedef long long ll;
typedef long double ld;

struct bit{
	int maks;
	int fen[2 * maxn];

	void add(int ind, int val){
		while(ind <= maks){
			fen[ind] += val;
			ind += ind & -ind;
		}
	}

	int lowerbound(int val){
		int p = 0;
		for(int i = maks / 2; i; i >>= 1){
			if(fen[p + i] < val){
				val -= fen[p + i];
				p += i;
			}
		}
		return ++p;
	}
	
	void init(int n){
		memset(fen, 0, sizeof(fen));

		maks = 1;
		while(maks < n)
			maks *= 2;

		for(int i = 1; i <= n; i++)
			add(i, 1);
	}
} bit;

vector<int> ans;

int main(){
	ll n, k;
	scanf("%lld%lld", &n, &k);

	bit.init(n);

	for(int i = 1; i <= n; i++){
		int l = 1, d = n - i + 1, mid, cur_ans = -1;

		while(l <= d){
			int mid = (l + d) / 2;
			int less = mid - 1;

			if(k - less <= 1LL * (n - i) * (n - i - 1) / 2){
				d = mid - 1;
				cur_ans = mid;
			}
			else
				l = mid + 1;
		}

		int cur_num = bit.lowerbound(cur_ans);
		k -= cur_ans - 1;
		bit.add(cur_num, -1);
		ans.pb(cur_num);
	}

	for(auto i : ans)
		printf("%d ", i);

	return 0;
}