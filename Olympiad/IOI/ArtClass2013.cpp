#include "grader.h"
#include <bits/stdc++.h>

using namespace std;

#define dist(a, b, c, d) (abs(R[a][b] - R[c][d]) + abs(G[a][b] - G[c][d]) + abs(B[a][b] - B[c][d]))

int val[] = {17, 36, 99, 7};

int style(int H, int W, int R[500][500], int G[500][500], int B[500][500]){
    int ans = 0, cnt = 0;
    for(int i = 0; i < H; i++){
    	for(int j = 0; j < W - 1; j++){
    		ans += dist(i, j, i, j + 1);
    		cnt++;
    	}   
    }
    for(int i = 0; i < H - 1; i++){
    	for(int j = 0; j < W; j++){
    		ans += dist(i, j, i + 1, j);
    		cnt++;
    	}   
    } 

    for(int i = 0; i < H - 1; i++){
    	for(int j = 0; j < W - 1; j++){
    		ans += dist(i, j, i + 1, j + 1);
    		cnt++;
    	}   
    } 
    ans /= cnt;
    int cur, raz = 1e9;
    for(int i = 0; i < 4; i++){
    	if(abs(ans - val[i]) < raz){
    		raz = abs(ans - val[i]);
    		cur = i + 1;
    	}
    }
   	return cur;
}