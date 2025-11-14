/******************************************************************************
Link: https://cses.fi/problemset/task/1735
Code: 1735
Time (YYYY-MM-DD-hh.mm.ss): 2025-10-06-22.15.08
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 2e5;
struct Node{
    int value;
    int lazy1, lazy2;

    Node(): value(0), lazy1(0), lazy2(0){}

    Node merge(const Node& other){
        Node res;
        res.value = this->value + other.value;
        res.lazy1 = res.lazy2 = 0;

        return res;
    }
};

int arr[MAXN + 5], n;
Node nodes[MAXN * 4 + 1];

void build(int id, int l, int r){
    if(l == r){
        nodes[id].value = arr[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
}

void push_set(int id){
    int t = nodes[id].lazy2;
    if(t == 0) return;

    nodes[id << 1].value = t;
    nodes[id << 1].lazy2 = t;
    nodes[id << 1].lazy1 = 0;

    nodes[id << 1 | 1].value = t;
    nodes[id << 1 | 1].lazy2= t;
    nodes[id << 1 | 1].lazy1 = 0;

    nodes[id].lazy2 = 0;
}

void push_inc(int id){
    push_set(id);

    int t = nodes[id].lazy1;

    nodes[id << 1].value += t;
    nodes[id << 1].lazy1 += t;
    nodes[id << 1].lazy2 += t;

    nodes[id << 1 | 1].value += t;
    nodes[id << 1 | 1].lazy1 += t;
    nodes[id << 1 | 1].lazy2 += t;

    nodes[id].lazy1 = 0;
}

void increase(int id, int l, int r, int u, int v, int val){
    if(v < l || r < u) return;
    if(u <= l && r <= v){
        nodes[id].value += val;
        nodes[id].lazy1 += val;
        nodes[id].lazy2 += val;
        return;
    }

    push_inc(id);

    int mid = (l + r) >> 1;
    increase(id << 1, l, mid, u, v, val);
    increase(id << 1 | 1, mid + 1, r, u, v, val);
    nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
}

void update(int id, int l, int r, int u, int v, int val){
    if(v < l || r < u) return;
    if(u <= l && r <= v){
        nodes[id].value = val;
        nodes[id].lazy2 = val;
        nodes[id].lazy1 = 0;
        return;
    }

    push_set(id);

    int mid = (l + r) >> 1;
    update(id << 1, l, mid, u, v, val);
    update(id << 1 | 1, mid + 1, r, u, v, val);
    nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
}

Node get(int id, int l, int r, int u, int v){
    if(v < l || r < u) return Node();
    if(u <= l && r <= v) return nodes[id];

    int mid = (l + r) >> 1;
    return get(id << 1, l, mid, u, v).merge(get(id << 1 | 1, mid + 1, r, u, v));
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("1735.INP","r",stdin);
    //freopen("1735.OUT","w",stdout);
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }

    build(1, 1, n);

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int a, b, x;
            cin >> a >> b >> x;

            increase(1, 1, n, a, b, x);
        }
        else if(type == 2){
            int a, b, x;
            cin >> a >> b >> x;

            update(1, 1, n, a, b, x);
        }
        else{
            int a, b;
            cin >> a >> b;

            cout << get(1, 1, n, a, b).value << '\n';
        }
    }


    return 0;
}
