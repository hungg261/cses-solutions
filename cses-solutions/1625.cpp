#include<bits/stdc++.h>
using namespace std;

const int n = 3;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int covered, total = n * n;
bool mark[n + 1][n + 1];
string instruction;

bool inside(int x, int y){
    return (1 <= x && x <= n) && (1 <= y && y <= n);
}

bool on_edge(int x, int y){
    return (x == 1 || x == n) ^ (y == 1 || y == n);
}

int dir_to_idx(char dir){
    switch(dir){
        case 'U': return 0;
        case 'R': return 1;
        case 'D': return 2;
        case 'L': return 3;
    }
    return -1;
}

int dfs(int x, int y, int idx){
    cerr << x << ' ' << y << ' ' << idx << " | " << covered << '\n';
    if(x == n && y == n){
        if(covered < total) return 0;
        return 1;
    }

    int ins = dir_to_idx(instruction[idx]);

    int res = 0;
    for(int d = 0; d < 4; ++d){
        if(ins != -1 && ins != d) continue;

        int nx = x + dx[d], ny = y + dy[d];
        if(inside(nx, ny) && !mark[nx][ny]){
            if(!on_edge(nx, ny)){
                mark[nx][ny] = true; ++covered;
                res += dfs(nx, ny, idx + 1);
                mark[nx][ny] = false; --covered;
            }
            else{
                if(nx == 1 || nx == n){
                    for(int i = 1; i <= n; ++i){
                        for(int j = 1; j <= ny - 1; ++j){

                        }
                    }
                }
            }
        }
    }

    return res;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> instruction;

    mark[1][1] = true; ++covered;
    int ans = dfs(1, 1, 0);
    cout << ans << '\n';

    return 0;
}
