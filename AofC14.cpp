/*

Advent of Code day 14
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

struct Robot {
    ll x, y, dx, dy;
    Robot() {}
    Robot(ll _x, ll _y, ll _dx, ll _dy) {
        x = _x;
        y = _y;
        dx = _dx;
        dy = _dy;
    }
};

vector<Robot> robots;

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        Robot cur;
        int i = 0;

        // Robot Postition
        i = line.find('=');
        line = line.substr(i+1);
        i = line.find(',');
        cur.x = stoi(line.substr(0, i));
        line = line.substr(i+1);
        i = line.find(' ');
        cur.y = stoi(line.substr(0, i));

        // Robot Velocity
        i = line.find('=');
        line = line.substr(i+1);
        i = line.find(',');
        cur.dx = stoi(line.substr(0, i));
        cur.dy = stoi(line.substr(i+1));

        robots.push_back(cur);
        getline(cin, line);
    }
    
}

ll n = 101, m = 103;

void solve1() {
    for (Robot& r : robots) {
        // simulate 100 seconds
        for (int i = 0; i < 100; i++) {
            r.x += r.dx;
            if (r.x < 0) r.x += n;
            else if (r.x >= n) r.x -= n;

            r.y += r.dy;
            if (r.y < 0) r.y += m;
            else if (r.y >= m) r.y -= m;
        }
    }

    // Get ans
    vector<ll> quad(4);
    ll mid_n = (n-1) / 2;
    ll mid_m = (m-1) / 2;
    for (Robot r : robots) {
        //cout << r.x << "," << r.y << "\n";
        if (r.x < mid_n && r.y < mid_m) quad[0]++;
        if (r.x < mid_n && r.y > mid_m) quad[1]++;
        if (r.x > mid_n && r.y < mid_m) quad[2]++;
        if (r.x > mid_n && r.y > mid_m) quad[3]++;
    }
    ll ans = quad[0] * quad[1] * quad[2] * quad[3];
    cout << ans << "\n";
}

void solve2() {
    string line = "";
    getline(cin, line);
    ll seconds = 0;
    while (line != "e") {
        bool valid = true;
        vector<vector<int>> grid(n, vector<int>(m));
        for (Robot& r : robots) {
            // simulate 1
            r.x += r.dx;
            if (r.x < 0) r.x += n;
            else if (r.x >= n) r.x -= n;

            r.y += r.dy;
            if (r.y < 0) r.y += m;
            else if (r.y >= m) r.y -= m;

            // add to display
            grid[r.x][r.y]++;
            if (grid[r.x][r.y] > 1) valid = false;
        }

        seconds++;
        if (!valid) continue;

        // show display
        for (vector<int> row : grid) {
            for (int i : row) {
                cout << (i == 0 ? "." : to_string(i));
            }
            cout << "\n";
        }
        
        cout << seconds;

        getline(cin, line);
    }
}

int main() {
    input();
    solve2();
    return 0;
}