/******************************************************************************
Link: https://cses.fi/problemset/task/2138
Code: 2138
Time (YYYY-MM-DD-hh.mm.ss): 2026-01-17-15.18.18
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e4;
int n, m;
vector<int> adj[MAXN + 5];

int dp[MAXN + 5];

void dfs(int u){
    if(dp[u] != -1) return;
    dp[u] = 1;

    for(int v: adj[u]){
        if(dp[v] == -1) dfs(v);
        dp[u] += dp[v];
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
    }

    memset(dp, -1, sizeof dp);
    for(int u = 1; u <= n; ++u){
        dfs(u);
    }

    for(int u = 1; u <= n; ++u){
        cout << dp[u] << ' ';
    }

    return 0;
}
