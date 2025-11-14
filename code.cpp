#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int C     =   1000;
const int BIG   =   ((sqrt(5)-1) / 2 * C);
const int SMALL =   (C - BIG);
#define prv(v)      { \
        cout << v.size() << " "; \
        for (auto it = v.begin(); it != v.end(); ) \
            cout << *it << " \n"[++it == v.end()]; \
    }
#define TAKE(s)     {cout << s << "TAKE" << endl;}
#define IGNORE(s)   {cout << s << "IGNORE" << endl;}

int items[10005];

void solve() {
    bool neglect = false;
    int n;
    vector<int> small_idx;
    int small_sum = 0;
    int medium = -1;
    cin >> n;
    int w;
    for (int t = 1; t <= n; ++t) {
        cin >> w;
        items[t] = w;
        if (neglect || w > C) {
            IGNORE("0\n");
        } else if (w >= BIG) {
            neglect = true;
            if (medium != -1) small_idx.push_back(medium);
            prv(small_idx);
            TAKE("\n");
        } else if (w <= SMALL) {
            TAKE("0\n");
            small_idx.push_back(t);
            small_sum += w;
            neglect = small_sum + items[medium] >= BIG;
        } else if (medium != -1) { // SMALL < w < BIG
            int wm = items[medium];
            if (wm + w <= 1000) {
                prv(small_idx);
                TAKE("\n");
                neglect = true;
            } else { // w + wm > 1000
                if (wm >= w) {
                    TAKE("1 " + to_string(medium) + "\n");
                    medium = t;
                } else {
                    IGNORE("0\n");
                }
            }
        } else if (small_sum + w <= C) { // no medium yet
            TAKE("0\n");
            medium = t;
            neglect = small_sum + w >= BIG;
        } else { // small_sum + w > 1000
            vector<int> drop;
            while (small_sum + w > 1000 && !small_idx.empty()) {
                int top = small_idx.back();
                drop.push_back(top);
                small_idx.pop_back();
                small_sum -= items[top];
            }
            prv(drop);
            TAKE("");
            neglect = true;
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
