/*

Advent of Code day 10
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

ll n, m, tt, t, k, q;
string s;

vector<vector<int>> grid;

struct pos {
    ll x = 0, y = 0;

    pos () {}

    pos (ll a, ll b) {
        x = a;
        y = b;
    }
};

ll ans = 0;
set<pair<int, int>> local_ans;

void dfs(pos p) {
    int num = grid[p.x][p.y];
    if (num == 9) {
        //local_ans.insert({p.x, p.y});
        ans++;
        return;
    }

    for (int i = 0; i < 4; i++) {
        int dx = (i % 2) * (i - 2);
        int dy = ((i + 1) % 2) * (i - 1);

        if (p.x + dx < 0 || p.x + dx >= n || p.y + dy < 0 || p.y + dy >= m) continue;
        if (grid[p.x + dx][p.y + dy] == 1 + num) dfs(pos(p.x + dx, p.y + dy));
    }
}

void solve1() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) {
                dfs(pos(i, j));
                ans += local_ans.size();
                local_ans = set<pair<int, int>>();
            }
        }
    }
    cout << ans << "\n";
}

void solve2() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) dfs(pos(i, j));
        }
    }
    cout << ans << "\n";
}

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        grid.push_back(row);
        getline(cin, line);
    }
    n = grid.size();
    m = grid[0].size();
}

int main() {
    input();
    solve1();
    return 0;
}