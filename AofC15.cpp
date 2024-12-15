/*

Advent of Code day 15
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

vector<string> grid;
vector<int> moves;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

ll n, m;

struct pos {
    ll x = 0, y = 0;
};

pos cat;

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        grid.push_back(line);
        getline(cin, line);
    }
    n = grid.size();
    m = grid[0].size();

    getline(cin, line);
    while (line != "") {
        for (char c : line) {
            if (c == '^') moves.push_back(0);
            if (c == 'v') moves.push_back(1);
            if (c == '>') moves.push_back(3);
            if (c == '<') moves.push_back(2);
        }
        getline(cin, line);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '@') {
                cat.x = i;
                cat.y = j;
            }
        }
    }
}

void solve1() {
    for (int move : moves) {
        // play the moves out
        int nx = dx[move];
        int ny = dy[move];

        //check if move is possible
        if (nx != 0) {
            // check the x line
            int j = cat.x;
            bool possible = true;
            while (j >= 0 && j < n && possible && grid[j][cat.y] != '.') {
                if (grid[j][cat.y] == '#') possible = false;
                j += nx;
            }

            if (possible) {
                while (j != cat.x) {
                    grid[j][cat.y] = 'O';
                    j -= nx;
                }
                grid[cat.x][cat.y] = '.';
                cat.x += nx;
            }
        } else {
            // check the y line
            int j = cat.y;
            bool possible = true;
            while (j >= 0 && j < m && possible && grid[cat.x][j] != '.') {
                if (grid[cat.x][j] == '#') possible = false;
                j += ny;
            }

            if (possible) {
                while (j != cat.y) {
                    grid[cat.x][j] = 'O';
                    j -= ny;
                }
                grid[cat.x][cat.y] = '.';
                cat.y += ny;
            }
        }
        grid[cat.x][cat.y] = '@';
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cout << grid[i] << "\n";
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'O') ans += (100 * i) + j;
        }
    }
    cout << ans << "\n";
}

void solve2() {
    // upscale
    vector<string> new_grid;
    for (string s : grid) {
        string ns = "";
        for (char c : s) {
            if (c == '#') ns += "##";
            if (c == '.') ns += "..";
            if (c == '@') ns += "@.";
            if (c == 'O') ns += "[]";
        }
        new_grid.push_back(ns);
    }
    grid = new_grid;
    m *= 2;
    cat.y *= 2;

    for (int move : moves) {
        // play the moves out
        int nx = dx[move];
        int ny = dy[move];

        if (nx != 0) {
            // vertical movement can sometimes be bad
            bool possible = true;
            int j = cat.x + nx;
            vector<ll> span = {cat.y};  // span of blocks that we are pushing
            vector<vector<ll>> span_his = {};
            while (j >= 0 && j < m && possible) {
                // check the span for possible walls and blocks
                vector<ll> new_span = {};
                set<ll> vis;
                for (ll y : span) {
                    if (vis.find(y) != vis.end()) continue;
                    if (grid[j][y] == '#') possible = false;
                    if (grid[j][y] == ']') {
                        vis.insert(y-1);
                        vis.insert(y);
                        new_span.push_back(y-1);
                        new_span.push_back(y);
                    }
                    if (grid[j][y] == '[') {
                        vis.insert(y);
                        vis.insert(y+1);
                        new_span.push_back(y);
                        new_span.push_back(y+1);
                    }
                }
                span_his.push_back(span);
                if (new_span.size() == 0) break;
                span = new_span;
                j += nx;
            }

            if (possible) {
                //push all the blocks up
                int span_i = span_his.size() - 1;
                while (j != cat.x) {
                    // go through the span history
                    // erase the blocks after moving them :D
                    // alternate between left and right :D
                    int parity = 1;
                    for (int b : span_his[span_i]) {
                        if (parity > 0) grid[j][b] = '[';
                        else grid[j][b] = ']';
                        parity *= -1;
                        grid[j - nx][b] = '.';
                    }

                    span_i--;
                    j -= nx;
                }
                // move cat
                grid[cat.x][cat.y] = '.';
                cat.x += nx;
            }
        } else {
            // horizontal movement is chill
            // check the y line
            int j = cat.y;
            bool possible = true;
            while (j >= 0 && j < m && possible && grid[cat.x][j] != '.') {
                if (grid[cat.x][j] == '#') possible = false;
                j += ny;
            }

            if (possible) {
                while (j != cat.y) {
                    grid[cat.x][j] = grid[cat.x][j-ny];
                    j -= ny;
                }
                grid[cat.x][cat.y] = '.';
                cat.y += ny;
            }
        }

        grid[cat.x][cat.y] = '@';
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cout << grid[i] << "\n";
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '[') ans += (100 * i) + j;
        }
    }
    cout << ans << "\n";
}

int main() {
    input();
    solve2();
    return 0;
}