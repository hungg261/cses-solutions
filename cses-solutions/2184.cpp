/******************************************************************************
Link: https://cses.fi/problemset/task/2184
Code: 2184
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-30-02.19.09
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e9;
const int MAXN = 2e5;
int arr[MAXN + 5], pre[MAXN + 5], n, q;

int trau(int l, int r){
    vector<int> temp;
    for(int i = l; i <= r; ++i) temp.push_back(arr[i]);
    sort(begin(temp), end(temp));

    int prefix = 0;
    for(int ele: temp){
        if(ele > prefix + 1){
            return prefix + 1;
        }
        prefix += ele;
    }
    return prefix + 1;
}

struct Node{
    vector<pair<int, int>> arr;
    vector<int> minSuf;
} nodes[MAXN * 4 + 5];

void build(int id, int l, int r){
    if(l == r){
        nodes[id].arr.emplace_back(arr[l] - pre[l - 1], l);
        nodes[id].minSuf.push_back(l);
        return;
    }

    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);

    int sz = r - l + 1;
    nodes[id].arr.resize(sz);
    merge(
        nodes[id << 1].arr.begin(), nodes[id << 1].arr.end(),
        nodes[id << 1 | 1].arr.begin(), nodes[id << 1 | 1].arr.end(),
        nodes[id].arr.begin()
    );

    nodes[id].minSuf.resize(sz);
    nodes[id].minSuf[sz - 1] = nodes[id].arr[sz - 1].second;
    for(int i = sz - 2; i >= 0; --i){
        nodes[id].minSuf[i] = min(nodes[id].minSuf[i + 1], nodes[id].arr[i].second);
    }
}

int get(int id, int l, int r, int u, int v){
    if(v < l || r < u) return INF;
    if(u <= l && r <= v){
        int idx = upper_bound(nodes[id].arr.begin(), nodes[id].arr.end(), make_pair(pre[u - 1] + 1, -INF)) - nodes[id].arr.begin();
        if(idx >= r - l + 1) return INF;

        return idx;
    }

    int mid = (l + r) >> 1;
    return min(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("2184.INP","r",stdin);
    //freopen("2184.OUT","w",stdout);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
        pre[i] = pre[i - 1] + arr[i];
    }

    build(1, 1, n);
    for(auto ele: nodes[1].arr){
        cerr << ele.first << ' ' << ele.second << '\n';
    }

    int idx = get(1, 1, n, 1, 5);
    cout << idx << '\n';

//    while(q--){
//        int l, r;
//        cin >> l >> r;
//
//        cout << get(1, 1, n, l, r) << '\n';
//    }

    return 0;
}
