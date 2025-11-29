/******************************************************************************
Link: https://cses.fi/problemset/task/1694
Code: 1694
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-29-20.05.14
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

struct EdgeTo{
    int v, w;

    EdgeTo() = default;
    EdgeTo(int _v, int _w): v(_v), w(_w){}

    void assignTo(int& _v, int& _w) const{ _v = v; _w = w; }

    bool operator == (const EdgeTo& other){
        return this->v == other.v;
    }
};

const int MAXN = 500, MAXM = 1000;

int n, m;
multiset<EdgeTo> adj[MAXN + 5], rev_adj[MAXN + 5];

bool bfs(int S, int T){
    queue<int> que;
    que.push(S);

    vector<int> par(n + 1, -1);
    while(!que.empty()){
        int u = que.front();
        que.pop();

        for(const EdgeTo& p: adj[u]){
            int v, w; p.assignTo(v, w);
            if(w <= 0) continue;

            if(v == T){
                while(v != -1){
                    rev_adj[]
                    v = par[v];
                }
                return true;
            }
            else{
                par[v] = u;
                que.push(v);
            }
        }
    }
}

void solve(int S, int T){
    while(bfs(S, T)){

    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("1694.INP","r",stdin);
    //freopen("1694.OUT","w",stdout);
    cin >> n >> m;

    for(int i = 1; i <= m; ++i){
        int a, b, c;
        cin >> a >> b >> c;

        adj[a].insert({b, c});
        rev_adj[b].insert({a, c});
    }

    solve(1, n);

    return 0;
}
