/*

Advent of Code day 16
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

vector<string> grid;
ll n, m;

int xdir[4] = {-1, 0, 1, 0};
int ydir[4] = {0, -1, 0, 1};

struct pos {
    ll x = 0, y = 0, dir = 3;

    pos () {}

    pos (ll _x, ll _y, ll _dir) {
        x = _x;
        y = _y;
        dir = _dir;
    }
};

priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
vector<pos> moves;

pos start;

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        grid.push_back(line);
        getline(cin, line);
    }
    n = grid.size();
    m = grid[0].size();

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (grid[i][j] == 'S') {
                start.x = i;
                start.y = j;
                moves.push_back(start);
                pq.push({0, 0});
            }
        }
    }
}

ll solve1() {
    ll ans = 0;
    int vis[n][m][4];
    memset(vis, 0, sizeof vis);

    while (!pq.empty()) {
        pair<ll, ll> tp = pq.top(); pq.pop();
        //cout << tp.first << " " << tp.second << "\n";
        pos p = moves[tp.second];
        //cout << p.x << " " << p.y << "\n";
        
        if (vis[p.x][p.y][p.dir] == 1) continue;
        vis[p.x][p.y][p.dir] = 1;
        if (grid[p.x][p.y] == 'E') {
            ans = tp.first;
            break;
        }

        for (int i = -1; i <= 1; i++) {
            ll dx = (1 - abs(i)) * xdir[p.dir];
            ll dy = (1 - abs(i)) * ydir[p.dir];
            ll ndir = (p.dir + i) % 4;
            if (ndir < 0) ndir += 4;

            if (p.x + dx < 0 || p.x + dx >= n || p.y + dy < 0 || p.y + dy >= m) continue;
            if (grid[p.x + dx][p.y + dy] == '#' || vis[p.x + dx][p.y + dy][ndir] == 1) continue;

            moves.push_back(pos(p.x + dx, p.y + dy, ndir));
            pq.push({tp.first + 1 + (999 * (i != 0)), moves.size() - 1});
        }
    }
    cout << ans << "\n";
    return ans;
}

set<pair<ll, ll>> seats;
ll min_path = 0;
vector<vector<vector<int>>> vis2;

bool dfs(pos p, ll price) {
    if (grid[p.x][p.y] == 'E') return true;
    if (price >= min_path) return false;

    if (vis2[p.x][p.y][p.dir] < price) return false;
    vis2[p.x][p.y][p.dir] = price;

    bool valid_seat = false;
    for (int i = -1; i <= 1; i++) {
        ll dx = (1 - abs(i)) * xdir[p.dir];
        ll dy = (1 - abs(i)) * ydir[p.dir];
        ll ndir = (p.dir + i) % 4;
        if (ndir < 0) ndir += 4;

        if (p.x + dx < 0 || p.x + dx >= n || p.y + dy < 0 || p.y + dy >= m) continue;
        if (grid[p.x + dx][p.y + dy] == '#') continue;

        valid_seat = valid_seat | dfs(pos(p.x + dx, p.y + dy, ndir), price + 1 + (999 * (i != 0)));
    }
    if (valid_seat) seats.insert({p.x, p.y});
    return valid_seat;
}

void solve2() {
    min_path = solve1();
    vis2 = vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(4, INT_MAX)));

    dfs(start, 0);
    cout << seats.size() + 1 << "\n";
}

int main() {
    input();
    solve2();
    return 0;
}