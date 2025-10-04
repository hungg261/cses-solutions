/******************************************************************************
Link: https://cses.fi/problemset/task/2189
Code: 2189
Time (YYYY-MM-DD-hh.mm.ss): 2025-10-02-14.50.56
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct Point{
    int x, y;

    void input(){
        cin >> x >> y;
    }
};

struct Triangle{
    Point A, B, C;

    int Direction(){
        return (B.x - A.x) * (B.y + A.y) + (C.x - B.x) * (C.y + B.y) + (A.x - C.x) * (A.y + C.y);
    }

    void input(){
        A.input();
        B.input();
        C.input();
    }
};

string solve(){
    Triangle tri;
    tri.input();

    int dir = tri.Direction();
    if(dir > 0) return "RIGHT";
    else if(dir < 0) return "LEFT";
    return "TOUCH";
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("2189.INP","r",stdin);
    //freopen("2189.OUT","w",stdout);
    int t;
    cin >> t;

    while(t--){
        cout << solve() << '\n';
    }

    return 0;
}
