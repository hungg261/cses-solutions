/******************************************************************************
Link: https://cses.fi/problemset/task/1664
Code: 1664
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-22-15.17.02
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

struct Event{
    int t;
    int type;
    int id;

    Event() = default;
    Event(int _t, int _type, int _id): t(_t), type(_type), id(_id){}

    bool operator < (const Event& other){
        return t < other.t || (t == other.t && type == 0);
    }
};

struct Movie{
    int l, r;
    int id;

    void input(int i){
        id = i;
        cin >> l >> r;
    }

    bool operator < (const Movie& other){
        return r < other.r;
    }
};

const int MAXN = 2e5, MAXQ = 2e5, MAXVAL = 1e6;
const int MAXK = __lg(MAXVAL) + 1;
int n, q;
pair<int, int> table[MAXVAL + 5][MAXK + 5];

Movie arr[MAXN + 5];
vector<pair<int, int>> events[MAXVAL + 5];

struct pqCmp{
    operator () (const int& x, const int& y){
        return arr[y] < arr[x];
    }
};

int nxt[MAXVAL + 5];

void compute(){
    priority_queue<int, vector<int>, pqCmp> pq;
    for(int e = MAXVAL; e >= 1; --e){
        for(const pair<int, int>& p: events[e]){
            if(p.first == 0) pq.push(p.second);
        }

        nxt[e] = pq.empty() ? MAXN + 1 : pq.top();
    }

    for(int i = 1; i <= MAXVAL; ++i){
        table[i][0] = {arr[nxt[i]].r, 1};
    }
    for(int j = 1; j <= MAXK; ++j){
        for(int i = 1; i <= MAXVAL; ++i){
            table[i][j] = make_pair(
                arr[table[arr[table[i][j - 1].first].r][j - 1].first].r,
                table[i][j - 1].second + table[arr[table[i][j - 1].first].r][j - 1].second
            );
        }
    }
}

void query(int a, int b){
    int res = 0;
    for(int bit = MAXK; bit >= 0; --bit){
        const pair<int, int>& tb = table[a][bit];
        if(tb.first <= b){
            a = tb.first;
            res += tb.second;
        }
    }

    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("1664.INP","r",stdin);
    //freopen("1664.OUT","w",stdout);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        arr[i].input(i);

//        events.emplace_back(arr[i].l, 0);
//        events.emplace_back(arr[i].r, 1);

        events[arr[i].l].emplace_back(0, i);
        events[arr[i].r].emplace_back(1, i);
    }

    compute();

    while(q--){
        int a, b;
        cin >> a >> b;

        query(a, b);
    }

    return 0;
}
