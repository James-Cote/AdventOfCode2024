#include <bits\stdc++.h>

using namespace std;
using ll = long long;

vector<string> grid;
vector<vector<int>> vis;
ll n, m;

struct pos {
    ll x = 0, y = 0;
    pos() {}
    pos(ll a, ll b) {
        x = a;
        y = b;
    }
};

struct region {
    ll area = 0, perimeter = 0;
    region() {}
    region(ll a, ll b) {
        area = a;
        perimeter = b;
    }
};

region regions(char c, pos p) {
    //cout << p.x << "," << p.y << " " << c << ":" << grid[p.x][p.y] << "\n";
    region cur(1, 4);
    grid[p.x][p.y] = '_';
    vis[p.x][p.y] = 1;

    for (int i = 0; i < 4; i++) {
        int dx = (i % 2) * (i - 2);
        int dy = ((i + 1) % 2) * (i - 1);

        if (p.x + dx < 0 || p.x + dx >= n || p.y + dy < 0 || p.y + dy >= m) continue;

        if (vis[p.x + dx][p.y + dy]) cur.perimeter--;
        if (grid[p.x + dx][p.y + dy] != c) continue;

        cur.perimeter--;
        
        region local_region = regions(c, pos(p.x + dx, p.y + dy));
        cur.perimeter += local_region.perimeter;
        cur.area += local_region.area;
    }
    return cur;
}

void solve1() {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //cout << i << "," << j << "\n";
            if (grid[i][j] != '_') {
                //cout << grid[i][j] << "\n";
                vis = vector<vector<int>>(n, vector<int>(m));
                region local_ans = regions(grid[i][j], pos(i, j));
                ans += local_ans.perimeter * local_ans.area;
            }
        }
    }
    cout << ans << "\n";
}

vector<vector<vector<int>>> edges;

ll dfs2(char c, pos p) {
    ll ans = 1;
    vis[p.x][p.y] = 1;
    grid[p.x][p.y] = '_';

    for (int i = 0; i < 4; i++) {
        int dx = (i % 2) * (i - 2);
        int dy = ((i+1) % 2) * (i - 1);

        if (p.x + dx < 0 || p.x + dx >= n || p.y + dy < 0 || p.y + dy >= m || (grid[p.x + dx][p.y + dy] != c && !vis[p.x + dx][p.y + dy])) {
            edges[p.x][p.y][i] = 1;
            continue;
        }
        if (vis[p.x + dx][p.y + dy]) continue;

        ans += dfs2(c, pos(p.x + dx, p.y + dy));
    }

    return ans;
}

void solve2() {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '_') {
                edges = vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(4)));
                vis = vector<vector<int>>(n, vector<int>(m));
                char c = grid[i][j];
                ll local_ans = dfs2(c, pos(i, j));

                // get the sides
                ll sides = 0;
                for (int dir = 0; dir < 4; dir++) {
                    if (dir % 2 == 0) {
                        for (int j = 0; j < m; j++) {
                            for (int i = 1; i < n; i++) {
                                sides += (edges[i][j][dir] == 0 && edges[i-1][j][dir] == 1);
                            }
                            sides += edges[n-1][j][dir]++;
                        }
                    } else {
                        for (int i = 0; i < n; i++) {
                            for (int j = 1; j < n; j++) {
                                sides += (edges[i][j][dir] == 0 && edges[i][j-1][dir] == 1);
                            }
                            sides += edges[i][m-1][dir]++;
                        }
                    }
                }

                cout << "REGION: " << c << " : " << sides << "," << local_ans << "\n";
                ans += local_ans * sides;
            }
        }
    }
    cout << ans << "\n";
}

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        grid.push_back(line);
        getline(cin, line);
    }
    n = grid.size();
    m = grid[0].size();
}

int main() {
    input();
    solve2();
    return 0;
}