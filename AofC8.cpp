#include <bits\stdc++.h>

using namespace std;
using ll = long long;

ll n, m, tt, t, k, q;
string s;

struct pos {
    ll x = 0, y = 0;

    pos() {}

    pos(ll a, ll b) {
        x = a;
        y = b;
    }
};

void solve1() {
    vector<string> grid;
    string line;
    getline(cin, line);
    while (line != "") {
        grid.push_back(line);
        getline(cin, line);
    }

    n = grid.size();
    m = grid[0].size();

    vector<vector<pos>> poles(150);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '.') {
                poles[grid[i][j]].push_back(pos(i, j));
            }
        }
    }

    set<pair<int, int>> nodes;
    for (vector<pos> pole : poles) {
        for (int i = 0; i < pole.size(); i++) {
            for (int j = i + 1; j < pole.size(); j++) {
                // go both ways
                int xdif = pole[j].x - pole[i].x;
                int ydif = pole[j].y - pole[i].y;

                pos one;
                one.x = pole[i].x - xdif;
                one.y = pole[i].y - ydif;

                pos two;
                two.x = pole[j].x + xdif;
                two.y = pole[j].y + ydif;

                if (one.x >= 0 && one.x < n && one.y >= 0 && one.y < m) {
                    nodes.insert({one.x, one.y});
                    if (grid[one.x][one.y] == '.') grid[one.x][one.y] = '#';
                }
                if (two.x >= 0 && two.x < n && two.y >= 0 && two.y < m) {
                    nodes.insert({two.x, two.y});
                    if (grid[two.x][two.y] == '.') grid[two.x][two.y] = '#';
                }
            }
        }
    }

    for (string l : grid) {
        cout << l << "\n";
    }

    cout << nodes.size() << "\n";
}

void solve2() {
    vector<string> grid;
    string line;
    getline(cin, line);
    while (line != "") {
        grid.push_back(line);
        getline(cin, line);
    }

    n = grid.size();
    m = grid[0].size();

    vector<vector<pos>> poles(150);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '.') {
                poles[grid[i][j]].push_back(pos(i, j));
            }
        }
    }

    set<pair<int, int>> nodes;
    for (vector<pos> pole : poles) {
        for (int i = 0; i < pole.size(); i++) {
            for (int j = i + 1; j < pole.size(); j++) {
                // get smallest increment
                int xdif = pole[j].x - pole[i].x;
                int ydif = pole[j].y - pole[i].y;

                int x = 2;
                while (x <= xdif && x <= ydif) {
                    if (x % xdif == 0 && x % ydif == 0) {
                        xdif /= x;
                        ydif /= x;
                    } else x++;
                }

                // place all the nodes
                pos k = pole[i];
                while (k.x >= 0 && k.y >= 0 && k.x < n && k.y < m) {
                    nodes.insert({k.x, k.y});
                    if (grid[k.x][k.y] == '.') grid[k.x][k.y] = '#';

                    k.x -= xdif;
                    k.y -= ydif;
                }

                k = pole[i];
                while (k.x >= 0 && k.y >= 0 && k.x < n && k.y < m) {
                    nodes.insert({k.x, k.y});
                    if (grid[k.x][k.y] == '.') grid[k.x][k.y] = '#';

                    k.x += xdif;
                    k.y += ydif;
                }
            }
        }
    }

    for (string l : grid) {
        cout << l << "\n";
    }

    cout << nodes.size() << "\n";
}

int main() {
    solve2();
    return 0;
}