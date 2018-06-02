/*
Idea:
- Minimum score cell is the median of tokens in both dimensions (x is the median of tokens' xs and y is the median of tokens' ys) 
- We can find median for each dimension using binary search
- Another optimization required to score 100 points is to do binary searches for both dimensions at once (we query (x, y), (x + 1, y) and (x, y + 1) )
*/

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

int query(int x, int y){
	cout << "? " << x << " " << y << endl;
	int ret;
	cin >> ret;
	return ret;
}

int main(){
	int r, c, k;
	scanf("%d%d%d",&r, &c, &k);
	int l_row = 1, d_row = r, mid_row, l_col = 1, d_col = c, mid_col, ans_row = 1, ans_col = 1;
	bool search_row = 1, search_col = 1;


	while(search_row || search_col){
		if(search_row)
			mid_row = (l_row + d_row) / 2;
		else
			mid_row = ans_row;
		
		if(search_col)
			mid_col = (l_col + d_col) / 2;
		else
			mid_col = ans_col;


		int cur_val = query(mid_row, mid_col);

		if(search_row && mid_row + 1 <= r){
			int top_val = query(mid_row + 1, mid_col);
			if(top_val == cur_val){
				search_row = 0;
				ans_row = mid_row;
			}

			if(top_val < cur_val){
				l_row = mid_row + 1;
				ans_row = mid_row + 1;
			}

			if(top_val > cur_val){
				d_row = mid_row;
				ans_row = mid_row;
			}
		}

		if(search_col && mid_col + 1 <= c){
			int right_val = query(mid_row, mid_col + 1);
			if(right_val == cur_val){
				search_col = 0;
				ans_col = mid_col;
			}

			if(right_val < cur_val){
				l_col = mid_col + 1;
				ans_col = mid_col + 1;
			}

			if(right_val > cur_val){
				d_col = mid_col;
				ans_col = mid_col;
			}
		}

		search_row = min(search_row, (l_row != d_row));
		search_col = min(search_col, (l_col != d_col));
	}


	cout << "! " << query(ans_row, ans_col) << endl;
	return 0;
}