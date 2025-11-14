/******************************************************************************
Link: https://cses.fi/problemset/task/2190
Code: 2190
Time (YYYY-MM-DD-hh.mm.ss): 2025-10-02-15.28.25
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

struct Point{
    int x, y;

    Point() = default;
    Point(int _x, int _y): x(_x), y(_y){}

    void input(){
        cin >> x >> y;
    }
};

struct Triangle{
    Point A, B, C;

    Triangle() = default;
    Triangle(Point _A, Point _B, Point _C): A(_A), B(_B), C(_C){}
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3){
        A = Point(x1, y1); B = Point(x2, y2); C = Point(x3, y3);
    }

    int Direction(){
        int dir = (B.x - A.x) * (B.y + A.y) + (C.x - B.x) * (C.y + B.y) + (A.x - C.x) * (A.y + C.y);
        return dir > 0 ? 1 : dir < 0 ? -1 : 0;
    }
};

struct Segment{
    Point A, B;

    bool intersect(const Segment& other){
        bool ok1 = Triangle(A, B, other.A).Direction() * Triangle(A, B, other.B).Direction() <= 0;
        bool ok2 = Triangle(other.A, other.B, A).Direction() * Triangle(other.A, other.B, B).Direction() <= 0;
        return ok1 && ok2;
    }

    void input(){
        A.input();
        B.input();
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("2190.INP","r",stdin);
    //freopen("2190.OUT","w",stdout);

    int t;
    cin >> t;

    while(t--){
        Segment S1, S2;
        S1.input();
        S2.input();

        cout << (S1.intersect(S2) ? "YES\n" : "NO\n");
    }

    return 0;
}
