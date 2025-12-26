/******************************************************************************
Link: https://cses.fi/problemset/task/1740
Code: 1740
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-26-15.02.15
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int OFFSET = 1e6, MAXVAL = 1e6;
const int MAXN = 1e5;
vector<int> values;
vector<array<int, 4>> inp;

int v(int value){
    return lower_bound(begin(values), end(values), value) - begin(values) + 1;
}

struct FenwickTree{
    int n;
    vector<int> BIT;

    FenwickTree(int sz = 0): n(sz){ BIT.resize(sz + 1, 0); }

    void update(int idx, int val){
        for(int i = idx; i <= n; i += i & -i){
            BIT[i] += val;
        }
    }

    int get(int idx){
        int res = 0;
        for(int i = idx; i > 0; i -= i & -i){
            res += BIT[i];
        }
        return res;
    }

    int get(int l, int r){ return get(r) - get(l - 1); }
};

struct State{
    int x, y1, y2;
    int type;

    State(int _x, int _y1, int _y2, int _type): x(_x), y1(_y1), y2(_y2), type(_type){}

    void output(){
        cerr << x << ' ' << y1 << ' ' << y2 << '\n';
    }

    bool operator < (const State& other){
        return this->x < other.x || (this->x == other.x && this->type == 0);
    }
};
int n;
vector<State> states;

void solve(){
    FenwickTree fwt(MAXVAL + 5);
    int ans = 0;
    for(const State& cur: states){
        if(cur.type == 0){
            ans += fwt.get(cur.y1, cur.y2);
        }
        else if(cur.type == 1){
            fwt.update(cur.y1, 1);
        }
        else if(cur.type == -1){
            fwt.update(cur.y1, -1);
        }
    }

    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if(y1 == y2){
            inp.push_back({x1, y1, y1, 1});
            inp.push_back({x2, y1, y1, -1});

            values.push_back(x1);
            values.push_back(x2);
            values.push_back(y1);
        }
        else{
            if(y1 > y2) swap(y1, y2);
            inp.push_back({x1, y1, y2, 0});

            values.push_back(x1);
            values.push_back(y1);
            values.push_back(y2);
        }
    }

    sort(begin(values), end(values));
    values.erase(unique(begin(values), end(values)), end(values));

    for(const auto& qr: inp){
        if(qr[3] == 0) states.emplace_back(v(qr[0]), v(qr[1]), v(qr[2]), 0);
        else states.emplace_back(v(qr[0]), v(qr[1]), v(qr[2]), qr[3]);
    }
    sort(begin(states), end(states));

    solve();

    return 0;
}
