/*

Advent of Code day 6
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

ll n, m, p, q, tt, t, k;
string s;

int ydir[4] = {-1, 0, 1, 0};
int xdir[4] = {0, -1, 0, 1};

struct pos {
    ll x = 0, y = 0, dir = 0;
};

void solve1() {
    vector<string> grid;
    string line;
    getline(cin, line);
    while (line != "") {
        grid.push_back(line);
        getline(cin, line);
    }

    // find the guard
    pos guard;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '^') {
                guard.x = i;
                guard.y = j;
                guard.dir = 1;
            }

            if (grid[i][j] == 'v') {
                guard.x = i;
                guard.y = j;
                guard.dir = 3;
            }

            if (grid[i][j] == '>') {
                guard.x = i;
                guard.y = j;
                guard.dir = 2;
            }

            if (grid[i][j] == '<') {
                guard.x = i;
                guard.y = j;
                guard.dir = 0;
            }
        }
    }

    vector<vector<int>> vis(grid.size(), vector<int>(grid[0].size()));
    while (guard.x >= 0 && guard.x < grid.size() && guard.y >= 0 && guard.y < grid[0].size()) {
        // check block
        if (grid[guard.x][guard.y] == '#') {
            guard.x -= xdir[guard.dir];
            guard.y -= ydir[guard.dir];

            guard.dir = (guard.dir + 1) % 4;
        }
        vis[guard.x][guard.y] = 1;

        guard.x += xdir[guard.dir];
        guard.y += ydir[guard.dir];
    }

    int ans = 0;
    for (vector<int> i : vis) {
        for (int j : i) ans += j;
    }
    cout << ans << "\n";
}

vector<string> grid;

bool loop(pos p) {
    int vis[grid.size()][grid[0].size()][4];
    memset(vis, 0, sizeof vis);
    vis[p.x][p.y][p.dir] = 1;
    p.dir = (p.dir + 1) % 4;
    while (p.x >= 0 && p.x < grid.size() && p.y >= 0 && p.y < grid[0].size()) {
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

void solve2() {
    string line;
    getline(cin, line);
    while (line != "") {
        grid.push_back(line);
        getline(cin, line);
    }

    // find the guard
    pos guard;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '^') {
                guard.x = i;
                guard.y = j;
                guard.dir = 1;
            }

            if (grid[i][j] == 'v') {
                guard.x = i;
                guard.y = j;
                guard.dir = 3;
            }

            if (grid[i][j] == '>') {
                guard.x = i;
                guard.y = j;
                guard.dir = 2;
            }

            if (grid[i][j] == '<') {
                guard.x = i;
                guard.y = j;
                guard.dir = 0;
            }
        }
    }

    set<pair<int, int>> ans;
    while (guard.x >= 0 && guard.x < grid.size() && guard.y >= 0 && guard.y < grid[0].size()) {
        // check block
        int newdir = (guard.dir + 1) % 4;
        if (grid[guard.x][guard.y] == '#') {
            guard.x -= xdir[guard.dir];
            guard.y -= ydir[guard.dir];

            guard.dir = newdir;
        } else {
            // check if we changed directions that we could go into a loop
            pos box = guard;
            box.x += xdir[box.dir];
            box.y += ydir[box.dir];
            if (box.x >= 0 && box.x < grid.size() && box.y >= 0 && box.y < grid[0].size() && grid[box.x][box.y] == '.' && loop(guard)) {
                ans.insert({box.x, box.y});
                //cout << box.x << "," << box.y << " " << box.dir << "\n";
            }
        }

        guard.x += xdir[guard.dir];
        guard.y += ydir[guard.dir];
    }

    cout << ans.size() << "\n";
}

int main() {
    ios :: sync_with_stdio(false);
	//cin.tie(nullptr);
    
    solve2();

    return 0;
}