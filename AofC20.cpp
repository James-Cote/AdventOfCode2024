/*

Advent of Code day 20
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

vector<string> grid;
ll n, m;

struct pos {
    ll x = 0, y = 0;
    pos () {}
    pos (ll a, ll b) {
        x = a; y = b;
    }
};

pos st, ed;

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        grid.push_back(line);
        getline(cin, line);
    }
    n = grid.size();
    m = grid[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'E') ed = pos(i, j);
            if (grid[i][j] == 'S') st = pos(i, j);
        }
    }
}

void solve1() {
    // SOLVED ON DIFFERENT COMPUTER
}

// Set of all the cheats (x1, y1, x2, y2)
set<vector<ll>> ans;
map<pair<ll, ll>, ll> dfs_vis;  // no point for back tracking when cheating
vector<vector<ll>> path;  // the shortest path to the goal from any non-wall point
ll shortest_path = 0;

void dfs_cheat(pos p, int t, int cheat, pos sp) {
    //cout << p.x << "," << p.y << " " << grid[p.x][p.y] << "\n";
    if (dfs_vis.find({p.x, p.y}) != dfs_vis.end() && t >= dfs_vis[{p.x, p.y}]) return;
    dfs_vis[{p.x, p.y}] = t;

    if (grid[p.x][p.y] != '#') {
        // found land
        //cout << "LAND : " << p.x << "," << p.y << " -> " << (t + path[p.x][p.y] + 50) << "\n";
        if (t + path[p.x][p.y] + 100 <= shortest_path) {
            //cout << start_p.first << "," << start_p.second << " : " << p.x << "," << p.y << "\n";
            ans.insert({sp.x, sp.y, p.x, p.y});
        }
    }
    if (cheat == 0) return;

    for (int i = 0; i < 4; i++) {
        ll dx = p.x + (i % 2) * (i - 2);
        ll dy = p.y + ((i+1) % 2) * (i - 1);

        if (dx < 0 || dx >= n || dy < 0 || dy >= m) continue;
        dfs_cheat(pos(dx, dy), t + 1, cheat - 1, sp);
    }
}

void solve2() {
    // Get the grid of the longest path to the end
    path = vector<vector<ll>>(n, vector<ll>(m));
    queue<pos> q;
    queue<int> tq;
    q.push(ed); tq.push(1);

    while (!q.empty()) {
        pos p = q.front(); q.pop();
        int t = tq.front(); tq.pop();

        if (path[p.x][p.y] != 0) continue;
        path[p.x][p.y] = t;

        for (int i = 0; i < 4; i++) {
            ll dx = p.x + (i % 2) * (i - 2);
            ll dy = p.y + ((i+1) % 2) * (i - 1);

            if (dx < 0 || dx >= n || dy < 0 || dy >= m) continue;
            if (grid[dx][dy] == '#' || path[dx][dy] != 0) continue;

            q.push(pos(dx, dy));
            tq.push(t + 1);
        }
    }

    // print the best path
    for (vector<ll> i : path) {
        for (ll j : i) {
            cout << (j < 10 ? " " : "") << j << " ";
        }
        cout << "\n";
    }
    shortest_path = path[st.x][st.y];

    // // Go through the maze while trying to cheat at every chance
    // q.push(st);
    // tq.push(0);
    // vector<vector<int>> vis(n, vector<int>(m));
    // while (!q.empty()) {
    //     pos p = q.front(); q.pop();
    //     int t = tq.front(); tq.pop();

    //     if (vis[p.x][p.y] == 1) continue;
    //     vis[p.x][p.y] = 1;

    //     for (int i = 0; i < 4; i++) {
    //         ll dx = p.x + (i % 2) * (i - 2);
    //         ll dy = p.y + ((i+1) % 2) * (i - 1);

    //         if (dx < 0 || dx >= n || dy < 0 || dy >= m || vis[dx][dy] == 1) continue;
    //         if (grid[dx][dy] == '#') {
    //             // CHEAT
    //             dfs_vis = map<pair<ll, ll>, ll>();
    //             dfs_cheat(pos(dx, dy), t + 1, 19, p);
    //             continue;
    //         }

    //         q.push(pos(dx, dy));
    //         tq.push(t + 1);
    //     }
    // }

    ll cheats = 0;
    int dist = 20;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') continue;
            for (int x = -dist; x <= dist; x++) {
                for (int y = -dist; y <= dist; y++) {
                    int t = abs(x) + abs(y);
                    if (t > dist || i + x < 0 || i + x >= n || j + y < 0 || j + y >= m || grid[i+x][j+y] == '#') continue;
                    if (t + path[i+x][j+y] + 100 <= path[i][j]) cheats++;
                }
            }
        }
    }

    cout << "CHEATS : " << cheats << "\n";
}

int main() {
    input();
    solve2();
    return 0;
}