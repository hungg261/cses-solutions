/******************************************************************************
Link: https://cses.fi/problemset/task/3411
Code: 3411
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-26-16.33.30
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("3411.INP","r",stdin);
    //freopen("3411.OUT","w",stdout);

    int n;
    cin >> n;

    int sum[4] = {};
    int res = 0;

    for(int i = 1; i <= n; ++i){
        int x, y;
        cin >> x >> y;

        sum[0] += - x - y;
        sum[1] += - x + y;
        sum[2] += + x - y;
        sum[3] += + x + y;

        res = res + x + y + sum[0];
        res = res + x - y + sum[1];
        res = res - x + y + sum[2];
        res = res - x - y + sum[3];
    }

    cerr << sum[0] << ' ' << sum[1] << ' ' << sum[2] << ' ' << sum[3] << '\n';
    cout << res << '\n';

    return 0;
}
