/******************************************************************************
Link: https://cses.fi/problemset/task/2184
Code: 2184
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-31-12.50.12
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

//#define int long long

const int MAXN = 2e5, MAXLG = __lg(MAXN) + 1;
const int MAXVAL = 1e9, LGVAL = __lg(MAXVAL) + 1;
int sum_table[LGVAL + 1][MAXN + 5], min_table[LGVAL + 1][MAXN + 5][MAXLG + 1];
int arr[MAXN + 5], n, q;
int pre[MAXN + 5];

void compute(){
    for(int k = 0; k <= LGVAL; ++k){
        for(int i = 1; i <= n; ++i){
            sum_table[k][i] = sum_table[k][i - 1];
            if(arr[i] < (1LL << k)){
                sum_table[k][i] += arr[i];
            }

            if((1LL << k) <= arr[i] && arr[i] <= (1LL << k + 1) - 1){
                min_table[k][i][0] = arr[i];
            }
            else{
                min_table[k][i][0] = MAXVAL;
            }
        }

        for(int j = 1; j <= MAXLG; ++j){
            for(int i = 1; i + (1 << j) - 1 <= n; ++i){
                min_table[k][i][j] = min(min_table[k][i][j - 1], min_table[k][i + (1 << j - 1)][j - 1]);
            }
        }
    }
}

int query_sum(int k, int l, int r){
    return sum_table[k][r] - sum_table[k][l - 1];
}

int query_min(int k, int l, int r){
    int bit = __lg(r - l + 1);
    return min(min_table[k][l][bit], min_table[k][r - (1 << bit) + 1][bit]);
}

int query(int l, int r){
    for(int k = 0; k <= LGVAL; ++k){
        int C = query_sum(k, l, r);
        if(C >= (1LL << k + 1) - 1 ||
           query_min(k, l, r) <= C + 1){}
        else{
            return C + 1;
        }
    }

    return pre[r] - pre[l - 1] + 1;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
        pre[i] = pre[i - 1] + arr[i];
    }

    compute();

    while(q--){
        int a, b;
        cin >> a >> b;

        cout << query(a, b) << '\n';;
    }

    return 0;
}
