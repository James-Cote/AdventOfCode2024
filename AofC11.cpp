/*

Advent of Code day 11
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

ll n, m, tt, t, k, q;
string s;

vector<ll> stones;

void solve1() {
    for (int i = 0; i < 25; i++) {
        vector<ll> new_stones;
        for (ll stone : stones) {
            if (stone == 0) {
                new_stones.push_back(1);
            } else if (to_string(stone).size() % 2 == 0) {
                string s = to_string(stone);
                new_stones.push_back(stoll(s.substr(0, s.size() / 2)));
                new_stones.push_back(stoll(s.substr(s.size() / 2, s.size() / 2)));
            } else {
                new_stones.push_back(stone * 2024);
            }
        }
        stones = new_stones;
    }

    // for (ll stone : stones) cout << stone << " ";
    // cout << "\n";
    cout << stones.size() << "\n";
}

map<pair<int, ll>, ll> mp;
ll afterBlink(int i, ll num) {
    if (i == 75) return 1;
    if (mp.find({i, num}) != mp.end()) return mp[{i, num}];

    if (num == 0) {
        ll local = afterBlink(i+1, 1);
        mp[{i, num}] = local;
        return local;
    } else if (to_string(num).size() % 2 == 0) {
        string s = to_string(num);
        ll local = afterBlink(i + 1, stoll(s.substr(0, s.size() / 2)));
        local += afterBlink(i + 1, stoll(s.substr(s.size() / 2, s.size() / 2)));
        mp[{i, num}] = local;
        return local;
    }
    ll local = afterBlink(i + 1, num * 2024);
    mp[{i, num}] = local;
    return local;
}

void solve2() {
    ll ans = 0;
    for (ll i : stones) {
        ans += afterBlink(0, i);
    }

    // for (ll stone : stones) cout << stone << " ";
    // cout << "\n";
    cout << ans << "\n";
}

void input() {
    string line;
    getline(cin, line);
    string s = "";
    for (char c : line) {
        if (c == ' ') {
            stones.push_back(stoll(s));
            s = "";
        } else s += c;
    }
    stones.push_back(stoll(s));
}

int main() {
    input();
    solve2();
    return 0;
}