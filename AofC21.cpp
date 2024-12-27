/*

Advent of Code day 21
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

struct keypad {
    vector<vector<char>> keys = {};
    int aimX = 0, aimY = 0;
    pair<int, int> e;

    keypad() {}

    keypad(vector<vector<char>> _keys, int _ax, int _ay, pair<int, int> _e) {
        keys = _keys;
        aimX = _ax;
        aimY = _ay;
        e = _e;
    }
};

keypad numberKey({{'7', '8', '9'}, {'4', '5', '6'}, {'1', '2', '3'}, {'E', '0', 'A'}}, 3, 2, {3, 0});
keypad robotKey({{'E', '^', 'A'}, {'<', 'v', '>'}}, 0, 2, {0, 0});

vector<string> codes;

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        codes.push_back(line);
        getline(cin, line);
    }
}

// Get the minimum sequence needed (sequence being a string of <>v^A)
string get_sequence(keypad kp, string seq) {
    string move_seq = "";
    pair<int, int> empty = kp.e;
    for (char c : seq) {
        // Get the position to go to
        pair<int, int> p;
        for (int i = 0; i < (int)kp.keys.size(); i++) {
            for (int j = 0; j < (int)kp.keys[i].size(); j++) {
                if (kp.keys[i][j] == c) {
                    p.first = i;
                    p.second = j;
                }
            }
        }

        // Move optimally (aka move in the same direction for the most amount of time)
        // If you are in the same x as the Empty, move in the y first and vice versa
        int dirX = 0, dirY = 0;
        if (p.first - kp.aimX != 0) dirX = (p.first - kp.aimX) / abs(p.first - kp.aimX);
        if (p.second - kp.aimY != 0) dirY = (p.second - kp.aimY) / abs(p.second - kp.aimY);

        bool yfirst = dirY < 0;

        // Check collision with empty
        if (kp.aimX == empty.first && p.second == empty.second) yfirst = false;
        if (kp.aimY == empty.second && p.first == empty.first) yfirst = true;

        if (yfirst) {
            if (dirY > 0) move_seq += string(abs(kp.aimY - p.second), '>');
            else if (dirY < 0) move_seq += string(abs(kp.aimY - p.second), '<');

            if (dirX > 0) move_seq += string(abs(kp.aimX - p.first), 'v');
            else if (dirX < 0) move_seq += string(abs(kp.aimX - p.first), '^');
        } else {
            if (dirX > 0) move_seq += string(abs(kp.aimX - p.first), 'v');
            else if (dirX < 0) move_seq += string(abs(kp.aimX - p.first), '^');

            if (dirY > 0) move_seq += string(abs(kp.aimY - p.second), '>');
            else if (dirY < 0) move_seq += string(abs(kp.aimY - p.second), '<');
        }

        kp.aimX = p.first;
        kp.aimY = p.second;
        
        move_seq += "A";
    }

    return move_seq;
}

void solve1() {
    ll ans = 0;
    for (string s : codes) {
        cout << s << "\n";
        string rb1 = get_sequence(numberKey, s);
        string rb2 = get_sequence(robotKey, rb1);
        string rb3 = get_sequence(robotKey, rb2);

        cout << rb1 << "\n";
        cout << rb2 << "\n";
        cout << rb3 << "\n";
        cout << rb3.size() << "\n";
        cout << "\n";

        ans += ((ll)rb3.size()) * stoll(s.substr(0, 3));
    }
    cout << "Complexity: " << ans << "\n";
}

ll vis[200][200][10][10];

ll string_dfs(string s, int d);

ll dfs(char c, ll d, int x, int y) {
    if (vis[(int)c][d][x][y] != 0) return vis[(int)c][d][x][y];
    
    // move :D
    int nx, ny;
    if (c == '<') {nx = 1; ny = 0;}
    if (c == '^') {nx = 0; ny = 1;}
    if (c == 'v') {nx = 1; ny = 1;}
    if (c == '>') {nx = 1; ny = 2;}
    if (c == 'A') {nx = 0; ny = 2;}

    int dx = 0, dy = 0;
    if (x != nx) dx = (nx - x) / abs(x - nx); 
    if (y != ny) dy = (ny - y) / abs(y - ny);

    bool firstY = dy < 0;
    
    //collision with square (0,0) aka the empty
    if (x == 0 && ny == 0) firstY = false;
    if (y == 0 && nx == 0) firstY = true;

    string moves = "";
    //cout << c << ": " << x << "," << y << " to " << nx << "," << ny << "  d(" << dx << "," << dy << ")  Y-first: " << firstY << "\n";
    if (firstY) {
        if (dy > 0) moves += string(abs(y - ny), '>');
        else if (dy < 0) moves += string(abs(y - ny), '<');

        if (dx > 0) moves += string(abs(x - nx), 'v');
        else if (dx < 0) moves += string(abs(x - nx), '^');
    } else {
        if (dx > 0) moves += string(abs(x - nx), 'v');
        else if (dx < 0) moves += string(abs(x - nx), '^');

        if (dy > 0) moves += string(abs(y - ny), '>');
        else if (dy < 0) moves += string(abs(y - ny), '<');
    }
    moves += "A";
    //cout << moves << "\n";
    ll ans = string_dfs(moves, d);
    vis[(int)c][d][x][y] = ans;

    return ans;
}

ll string_dfs(string s, int d) {
    if (d == 0) return s.size();
    // keep track of the position
    int x = 0, y = 2;
    ll ans = 0;
    for (char c : s) {
        ans += dfs(c, d - 1, x, y);

        // Move
        if (c == '<') {x = 1; y = 0;}
        if (c == '^') {x = 0; y = 1;}
        if (c == 'v') {x = 1; y = 1;}
        if (c == '>') {x = 1; y = 2;}
        if (c == 'A') {x = 0; y = 2;}
    }
    return ans;
}

void solve2() {
    memset(vis, 0, sizeof vis);
    ll ans = 0;
    for (string s : codes) {
        string rb = get_sequence(numberKey, s);
        ll s25 = string_dfs(rb, 25);

        ans += s25 * stoll(s.substr(0, 3));
    }
    cout << "Complexity: " << ans << "\n";
}

int main() {
    input();
    solve2();
    return 0;
}