/******************************************************************************
Link: https://cses.fi/problemset/task/1136
Code: 1136
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-23-09.27.02
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;
int n;
vector<int> adj[MAXN + 5];

int sz[MAXN + 5];
int outsz[MAXN + 5];

int sum[2][MAXN + 5];

void dfs1(int u, int prv){
    sz[u] = 1;
    for(int v: adj[u]){
        if(v == prv) continue;

        dfs1(v, u);
        sz[u] += sz[v];

        sum[0][u] += sz[v] * sz[v];
    }
    sum[1][u] = sz[u] * sz[u];
}

void dfs2(int u, int prv){
    outsz[u]++;
    for(int v: adj[u]){
        if(v == prv) continue;

        outsz[v] = outsz[u] + sz[u] - sz[v] - 1;
        dfs2(v, u);
    }
}

int res[MAXN + 5];
void Try(int u, int prv){
    for(int v: adj[u]){
        if(v == prv) continue;

        if(u != 1) res[u] += outsz[prv] * sz[v];
        res[u] += sum[1][u] - sum[0][u] >> 1;

        Try(v, u);
    }

    res[u] += adj[u].size();
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("1136.INP","r",stdin);
    //freopen("1136.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(1, 0);
    dfs2(1, 0);

    for(int u = 1; u <= n; ++u){
        sz[u]--;
        outsz[u]--;
    }

    Try(1, 0);

    for(int u = 1; u <= n; ++u){
        cout << res[u] << ' ';
    }

    return 0;
}
