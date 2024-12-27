/*

Advent of Code day 22
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

ll mod = 16777216;
vector<ll> codes;

void new_secret_code(ll& code) {
    ll val = code * 64;
    code = (val ^ code) % mod;
    val = code / 32;
    code = (val ^ code) % mod;
    val = code * 2048;
    code = (val ^ code) % mod;
}

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        codes.push_back(stoll(line));
        getline(cin, line);
    }
}

void solve1() {
    ll ans = 0;
    for (ll code : codes) {
        cout << code << " : ";
        for (int i = 0; i < 2000; i++) {
            new_secret_code(code);
        }
        ans += code;
        cout << code << "\n";
    }
    cout << "SUM: " << ans << "\n";
}

// Changes can happen from -9 to +9, making 19 (20 just to be safe)
ll sequences[20][20][20][20];

void solve2() {
    memset(sequences, 0, sizeof sequences);
    for (ll code : codes) {
        vector<int> diffs;
        vector<int> p;
        int last = code % 10;
        for (int i = 0; i < 2000; i++) {
            new_secret_code(code);
            int price = code % 10;
            p.push_back(price);
            diffs.push_back(10 + price - last);
            last = price;
        }

        // go through the diffs
        int vis[20][20][20][20];
        memset(vis, 0, sizeof vis);
        for (int i = 3; i < diffs.size(); i++) {
            int a = diffs[i-3], b = diffs[i-2], c = diffs[i-1], d = diffs[i];
            if (vis[a][b][c][d]) continue;
            vis[a][b][c][d] = 1;
            sequences[a][b][c][d] += p[i];
        }
    }

    // get the answer
    ll ans = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            for (int k = 0; k < 20; k++) {
                for (int l = 0; l < 20; l++) ans = max(ans, sequences[i][j][k][l]);
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    input();
    solve2();
    return 0;
}