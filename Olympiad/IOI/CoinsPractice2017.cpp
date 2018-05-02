#include "coins.h"
#include <bits/stdc++.h>

using namespace std;

vector<int> coin_flips(vector<int> b, int c) {
    vector<int> flips;
    int all = 0;
    for(int i = 0; i < b.size(); i++){
        if(b[i])
            all ^= i;
    }

    int pos = all ^ c;
    flips.push_back(pos);
    return flips;
}

int find_coin(vector<int> b) {
    int ans = 0;
     for(int i = 0; i < b.size(); i++){
        if(b[i])
            ans ^= i;
    }
    return ans;
}