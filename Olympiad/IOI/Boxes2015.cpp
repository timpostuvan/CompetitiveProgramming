#include "boxes.h"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

long long cw[11111111];
long long acw[11111111];

long long delivery(int N, int K, int L, int p[]) {
    cw[0] = acw[0] = 0LL;
    for(int i = 1; i <= N; i++){
    	long long dod = 0LL;
    	if(i - K > 0) dod = cw[i - K];
    	cw[i] = dod + 2 * p[i - 1]; 
    }

    for(int i = N; i >= 1; i--){
    	long long dod = 0LL;
    	if(i + K <= N) dod = acw[i + K];
    	acw[i] = dod + 2 * (L - p[i - 1]); 
    }

    long long ans = (1LL << 60);
    for(int i = 0; i <= N; i++) ans = min(ans, cw[i] + acw[i + 1]);
    for(int l = 1; l <= N; l++){
    	int d = min(N + 1, l + K + 1);
    	ans = min(ans, cw[l] + L + acw[d]);
    }

    if(K >= N) ans = min(ans, (long long) L);
    return ans;
}