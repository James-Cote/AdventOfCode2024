/*

Advent of Code day 18
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

ll n = 71;
vector<vector<int>> grid(n, vector<int>(n));
vector<pair<ll, ll>> bits;

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        int i = line.find(',');
        bits.push_back({stoll(line.substr(0, i)), stoll(line.substr(i+1))});
        
        getline(cin, line);
    }   
}

int dirx[4] = {-1, 0, 1, 0};
int diry[4] = {0, -1, 0, 1};

ll solve1() {
    queue<pair<ll, ll>> q;
    queue<ll> tq;
    q.push({0, 0}); tq.push(0);

    ll ans = -1;
    ll vis[n][n];
    memset(vis, 0, sizeof vis);
    while (!q.empty()) {
        pair<ll, ll> p = q.front(); q.pop();
        ll t = tq.front(); tq.pop();

        if (p.first == n - 1 && p.second == n - 1) {
            ans = t;
            break;
        }
        if (vis[p.first][p.second]) continue;
        vis[p.first][p.second] = 1;

        for (int i = 0; i < 4; i++) {
            int dx = dirx[i];
            int dy = diry[i];

            if (p.first + dx < 0 || p.first + dx >= n || p.second + dy < 0 || p.second + dy >= n) continue;
            if (grid[p.first + dx][p.second + dy] == 1 || vis[p.first + dx][p.second + dy] == 1) continue;

            q.push({p.first + dx, p.second + dy});
            tq.push(t + 1);
        }
    }

    return ans;
}

void solve2() {
    pair<ll, ll> ans = {-1, -1};
    for (int i = 0; i < (int)bits.size(); i++) {
        grid[bits[i].first][bits[i].second] = 1;
        ll local_ans = solve1();
        if (local_ans < 0) {
            ans = bits[i];
            break;
        }
    }

    cout << ans.first << "," << ans.second << "\n";
}

int main() {
    input();

    // for (int i = 0; i < 1024; i++) {
    //     grid[bits[i].first][bits[i].second] = 1;
    // }
    // cout << solve1() << "\n";

    solve2();
    for (vector<int> i : grid) {
        for (int j : i) cout << (j == 0 ? '.' : '#');
        cout << "\n";
    }
    return 0;
}