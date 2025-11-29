/******************************************************************************
Link: https://cses.fi/problemset/task/1694
Code: 1694
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-29-20.05.14
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

struct EdgeTo{
    int v, w, rev;

    EdgeTo() = default;
    EdgeTo(int _v, int _w, int _rev): v(_v), w(_w), rev(_rev){}

    void assignTo(int& _v, int& _w) const{ _v = v; _w = w; }

    bool operator == (const EdgeTo& other){
        return this->v == other.v;
    }
};

const int MAXN = 500, MAXM = 1000;

int n, m;
vector<EdgeTo> adj[MAXN + 5];
int level[MAXN + 5], it[MAXN + 5];

void addEdge(int u, int v, int w){
    adj[u].push_back({v, w, (int)adj[v].size()});
    adj[v].push_back({u, 0, (int)adj[u].size() - 1});
}

bool bfs(int S, int T){
    fill(level + 1, level + n + 1, -1);
    queue<int> que;
    que.push(S);
    level[S] = 0;

    while(!que.empty()){
        int u = que.front(); que.pop();
        for(const EdgeTo& e: adj[u]){
            if(e.w > 0 && level[e.v] < 0){
                level[e.v] = level[u] + 1;
                que.push(e.v);
            }
        }
    }

    return level[T] >= 0;
}

int dfs(int u, int flow, int T){
    if(u == T){
        return flow;
    }

    for(int &i = it[u]; i < (int)adj[u].size(); ++i){
        EdgeTo& e = adj[u][i];
        if(e.w > 0 && level[u] + 1 == level[e.v]){
            int pushed = dfs(e.v, min(flow, e.w), T);
            if(pushed > 0){
                e.w -= pushed;
                adj[e.v][e.rev].w += pushed;
                return pushed;
            }
        }
    }

    return 0;
}

void solve(int S, int T){
    int ans = 0;
    while(bfs(S, T)){
        fill(it + 1, it + n + 1, 0);
        while(int pushed = dfs(S, INT_MAX, T)){
            ans += pushed;
        }
    }

    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("1694.INP","r",stdin);
    //freopen("1694.OUT","w",stdout);
    cin >> n >> m;

    for(int i = 1; i <= m; ++i){
        int a, b, c;
        cin >> a >> b >> c;

        addEdge(a, b, c);
    }

    solve(1, n);

    return 0;
}
