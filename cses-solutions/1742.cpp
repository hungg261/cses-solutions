/******************************************************************************
Link: https://cses.fi/problemset/task/1742
Code: 1742
Time (YYYY-MM-DD-hh.mm.ss): 2026-01-01-16.24.51
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

struct Fenwick2DCompressed {
    int n;
    vector<vector<int>> ys;
    vector<vector<long long>> B0, B1, B2, B3;

    Fenwick2DCompressed(int n_) : n(n_) {
        ys.resize(n + 1);
        B0.resize(n + 1);
        B1.resize(n + 1);
        B2.resize(n + 1);
        B3.resize(n + 1);
    }

    static inline int lowbit(int x) {
        return x & -x;
    }

    // -------- OFFLINE PHASE --------
    // register all (x,y) used in updates
    void fake_update(int x, int y) {
        for (int i = x; i <= n; i += lowbit(i))
            ys[i].push_back(y);
    }

    void fake_range_add(int x1, int y1, int x2, int y2) {
        fake_update(x1,     y1);
        fake_update(x1,     y2 + 1);
        fake_update(x2 + 1, y1);
        fake_update(x2 + 1, y2 + 1);
    }

    // must be called once before real updates/queries
    void build() {
        for (int i = 1; i <= n; i++) {
            auto &v = ys[i];
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
            int sz = v.size() + 1;
            B0[i].assign(sz, 0);
            B1[i].assign(sz, 0);
            B2[i].assign(sz, 0);
            B3[i].assign(sz, 0);
        }
    }

    int get_y(int x, int y) const {
        return lower_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin() + 1;
    }

    // -------- INTERNAL BIT UPDATE --------
    void upd(int x, int y, long long v) {
        for (int i = x; i <= n; i += lowbit(i)) {
            int yi = get_y(i, y);
            for (int j = yi; j < (int)B0[i].size(); j += lowbit(j)) {
                B0[i][j] += v;
                B1[i][j] += x * v;
                B2[i][j] += y * v;
                B3[i][j] += x * y * v;
            }
        }
    }

    // prefix sum [1..x][1..y]
    long long qry(int x, int y) const {
        long long res = 0;
        for (int i = x; i > 0; i -= lowbit(i)) {
            int yi = upper_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin();
            for (int j = yi; j > 0; j -= lowbit(j)) {
                res += (x + 1LL) * (y + 1LL) * B0[i][j]
                     - (y + 1LL) * B1[i][j]
                     - (x + 1LL) * B2[i][j]
                     + B3[i][j];
            }
        }
        return res;
    }

    // -------- PUBLIC API --------

    // add v to rectangle (x1,y1) -> (x2,y2)
    void range_add(int x1, int y1, int x2, int y2, long long v) {
        upd(x1,     y1,     v);
        upd(x1,     y2 + 1, -v);
        upd(x2 + 1, y1,     -v);
        upd(x2 + 1, y2 + 1, v);
    }

    // sum of rectangle (x1,y1) -> (x2,y2)
    long long range_sum(int x1, int y1, int x2, int y2) const {
        return qry(x2, y2)
             - qry(x1 - 1, y2)
             - qry(x2, y1 - 1)
             + qry(x1 - 1, y1 - 1);
    }
};

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
const string DIR = "URDL";

int dir(char c){
    return find(begin(DIR), end(DIR), c) - begin(DIR);
}

pair<int, int> shift(int x, int y, int d, int steps){
    return {x + dx[d] * steps, y + dy[d] * steps};
}

const int MAX = 1e12;
void solve(){
    Fenwick2DCompressed fwt(100);

    int n;
    cin >> n;
    vector<pair<char, int>> queries;

    int cx = 0, cy = 0;
    for(int i = 1; i <= n; ++i){
        char dr; int st;
        cin >> dr >> st;

        int nx, ny;
        tie(nx, ny) = shift(cx, cy, dir(dr), st);

        int x = cx, y = cy;
        if(x > nx || y > ny){
            swap(x, nx);
            swap(y, ny);
        }

        fwt.fake_range_add(x, y, nx, ny);
        queries.emplace_back(dr, st);
    }

    fwt.build();

    cx = cy = 0;
    for(const pair<char, int>& p: queries){
        char dr; int st;
        tie(dr, st) = p;

        int nx, ny;
        tie(nx, ny) = shift(cx, cy, dir(dr), st);

        int x = cx, y = cy;
        if(x > nx || y > ny){
            swap(x, nx);
            swap(y, ny);
        }

        fwt.range_add(x, y, nx, ny, 1);
    }

    cout << fwt.range_sum(1, 1, 10, 10) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    solve();

    return 0;
}
