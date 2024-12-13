/*

Advent of Code day 6
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

ll n, m, tt, t, k, q;
string s;

struct pos {
    ll x = 0, y = 0, dir = 0;
};

ll xdir[4] = {-1, 0, 1, 0};
ll ydir[4] = {0, 1, 0, -1};

vector<string> grid;

bool loop(pos p) {
    int vis[n][m][4];
    memset(vis, 0, sizeof vis);

    while (p.x >= 0 && p.x < n && p.y >= 0 && p.y < m) {
        if (vis[p.x][p.y][p.dir]) return 1;
        vis[p.x][p.y][p.dir] = 1;

        if (grid[p.x][p.y] == '#') {
            p.x -= xdir[p.dir];
            p.y -= ydir[p.dir];
            p.dir = (p.dir + 1) % 4;
        }
        p.x += xdir[p.dir];
        p.y += ydir[p.dir];
    }
    return 0;
}

void solve() {
    string line;
    getline(cin, line);
    while (line != "") {
    while (line != "") {
        grid.push_back(line);
        getline(cin, line);
    }
    n = grid.size();
    m = grid[0].size();

    // find the position of the guard
    pos guard;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '^' || grid[i][j] == '>' || grid[i][j] == '<' || grid[i][j] == 'v') {
                guard.x = i;
                guard.y = j;

                if (grid[i][j] == '^') guard.dir = 0;
                if (grid[i][j] == '>') guard.dir = 1;
                if (grid[i][j] == 'V') guard.dir = 2;
                if (grid[i][j] == '<') guard.dir = 3;
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                grid[i][j] = '#';
                cout << i << "," << j << " ";
                ans += loop(guard);
                cout << ans << "\n";
                grid[i][j] = '.';
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    tt = 1;

    //cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}