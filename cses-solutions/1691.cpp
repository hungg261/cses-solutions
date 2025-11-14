/******************************************************************************
Link: https://cses.fi/problemset/task/1691
Code: 1691
Time (YYYY-MM-DD-hh.mm.ss): 2025-10-03-10.06.06
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

struct To{
    int v, id;
};

const int MAXN = 1e5;
vector<To> adj[MAXN + 5];
int n, m;

void dfs(int u){
    for(const To& p: adj[u]){
        sy
    }
}

bool solve(){
    int start = 1;
    for(; start <= n; ++start){
        if(!adj[start].empty()) break;
    }

    if(start == n + 1) return false;


}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("1691.INP","r",stdin);
    //freopen("1691.OUT","w",stdout);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    solve();

    return 0;
}
