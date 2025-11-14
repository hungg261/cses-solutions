/******************************************************************************
Link: https://cses.fi/problemset/task/1736
Code: 1736
Time (YYYY-MM-DD-hh.mm.ss): 2025-10-04-17.59.53
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 2e5;
struct Node{
    int value1, value2;
    int lazy1, lazy2;

    Node() = default;
    Node(int _value1, int _value2, int _lazy1, int _lazy2): value1(_value1), value2(_value2), lazy1(_lazy1), lazy2(_lazy2){}

    int get_sum(){
        return value1 + value2;
    }

    Node merge(const Node& other){
        Node res;
        res.value1 = this->value1 + other.value1;
        res.value2 = this->value2 + other.value2;

        res.lazy1 = 0;
        res.lazy2 = 0;

        return res;
    }
} nodes[MAXN * 4 + 5];

void push(int id, int l, int r){
    int t1 = nodes[id].lazy1, t2 = nodes[id].lazy2;
    int mid = (l + r) >> 1;

    nodes[id << 1].value1 += t1 * (mid - l + 1);
    nodes[id << 1].lazy1 += t1;

    nodes[id << 1].value2 += t2 * (mid - l + 1) * (mid - l + 2) / 2;
    nodes[id << 1].lazy2 += t2;

    nodes[id << 1 | 1].value1 += t1 * (r - mid);
    nodes[id << 1 | 1].lazy1 += t1;

    nodes[id << 1 | 1].value2 += t2 * (r - mid) * (r - mid + 1) / 2;
    nodes[id << 1 | 1].lazy2 += t2;

    nodes[id].lazy1 = 0;
    nodes[id].lazy2 = 0;
}

void update(int id, int l, int r, int u, int v){
    if(v < l || r < u) return;
    if(u <= l && r <= v){
        nodes[id].value1 += (l - u) * (r - l + 1);
        nodes[id].lazy1 += l - u;

        nodes[id].value2 += (r - l + 1) * (r - l + 2) / 2;
        nodes[id].lazy2++;

        return;
    }

    push(id, l, r);

    int mid = (l + r) >> 1;
    update(id << 1, l, mid, u, v);
    update(id << 1 | 1, mid + 1, r, u , v);
    nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
}

Node get(int id, int l, int r, int u, int v){
    if(v < l || r < u) return Node(0, 0, 0, 0);
    if(u <= l && r <= v) return nodes[id];

    push(id, l, r);

    int mid = (l + r) >> 1;
    return get(id << 1, l, mid, u, v).merge(get(id << 1 | 1, mid + 1, r, u, v));
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;

    vector<int> pre(n + 1);
    pre[0] = 0;

    for(int i = 1; i <= n; ++i){
        int cur; cin >> cur;
        pre[i] = pre[i - 1] + cur;
    }

    while(q--){
        int type, a, b;
        cin >> type >> a >> b;

        if(type == 1){
            update(1, 1, n, a, b);
        }
        else{
            cout << pre[b] - pre[a - 1] + get(1, 1, n, a, b).get_sum() << '\n';
        }
    }

    return 0;
}
