/******************************************************************************
Link: https://cses.fi/problemset/task/1695
Code: 1695
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-29-22.58.14
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

//#define int long long

struct EdgeTo{
    int v, cap, revIdx;

    EdgeTo() = default;
    EdgeTo(int _v, int _cap, int _revIdx): v(_v), cap(_cap), revIdx(_revIdx){}

    tuple<int, int, int> get(){ return make_tuple(v, cap, revIdx); }
};

const int MAXN = 500;
int n, m;
vector<EdgeTo> adj[MAXN + 5];
vector<int> origin[MAXN + 5];
int level[MAXN + 5], it[MAXN + 5];

void addEdge(int a, int b, int c){
    adj[a].emplace_back(b, c, (int)adj[b].size());
    adj[b].emplace_back(a, c, (int)adj[a].size() - 1);
}

bool bfs_findPath(int S, int T){
    queue<int> que;
    que.push(S);

    fill(level + 1, level + n + 1, -1);
    level[S] = 0;

    while(!que.empty()){
        int u = que.front(); que.pop();
        for(const EdgeTo& e: adj[u]){
            if(e.cap > 0 && level[e.v] == -1){
                level[e.v] = level[u] + 1;
                que.push(e.v);
            }
        }
    }

    return level[T] >= 0;
}

int dfs_sendFlow(int u, int flow, int T){
    if(u == T) return flow;

    for(int &i = it[u]; i < (int)adj[u].size(); ++i){
        EdgeTo& e = adj[u][i];
        if(level[u] + 1 != level[e.v]) continue;

        int pushed = dfs_sendFlow(e.v, min(flow, e.cap), T);
        if(pushed > 0){
            e.cap -= pushed;
            adj[e.v][e.revIdx].cap += pushed;
            return pushed;
        }
    }

    return 0;
}

bool vis[MAXN + 5];
void dfs_findCut(int u){
    vis[u] = true;

    for(const EdgeTo& e: adj[u]){
        if(e.cap > 0 && !vis[e.v]) dfs_findCut(e.v);
    }
}

void Dinic(int S, int T){
    long long ans = 0;
    while(bfs_findPath(S, T)){
        fill(it + 1, it + n + 1, 0);
        while(int pushed = dfs_sendFlow(S, INT_MAX, T)){
            ans += pushed;
        }
    }

    dfs_findCut(S);

    cout << ans << '\n';
    for(int u = 1; u <= n; ++u){
        for(int v: origin[u]){
            if(vis[u] ^ vis[v]){
                cout << u << ' ' << v << '\n';
            }
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("1695.INP","r",stdin);
    //freopen("1695.OUT","w",stdout);
    cin >> n >> m;

    int S = 1, T = n;
    for(int i = 1; i <= m; ++i){
        int a, b;
        cin >> a >> b;

        origin[a].push_back(b);
        addEdge(a, b, 1);
    }

    Dinic(S, T);

    return 0;
}
