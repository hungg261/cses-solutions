/******************************************************************************
Link: https://cses.fi/problemset/task/1751
Code: 1751
Time (YYYY-MM-DD-hh.mm.ss): 2025-09-28-13.01.32
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5, MAXK = __lg(MAXN) + 1;
int table[MAXN + 5][MAXK + 5], n;

void compute(){
    for(int k = 1; k <= MAXK; ++k){
        for(int i = 1; i <= n; ++i){
            table[i][k] = table[table[i][k - 1]][k - 1];
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // freopen("1751.INP","r",stdin);
    // freopen("1751.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> table[i][0];
    }
    compute();

    for(int i = 1; i <= n; ++i){
        for(int bit = MAXK; bit >= 0; --bit){
            if()
        }
    }

    return 0;
}
