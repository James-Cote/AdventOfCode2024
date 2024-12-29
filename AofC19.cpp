/*

Advent of Code day 19
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

vector<string> towels;
vector<string> patterns;

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        int i = line.find(',');
        if (i == -1) {
            towels.push_back(line);
            line = "";
        } else {
            towels.push_back(line.substr(0, i));
            line = line.substr(i + 2);
        }
    }

    getline(cin, line);
    while (line != "") {
        patterns.push_back(line);
        getline(cin, line);
    }
}

void solve1() {
    ll ans = 0;
    for (string p : patterns) {
        queue<int> q;
        q.push(0);
        
        bool bang = false;
        while (q.empty()) {
            int i = q.front(); q.pop();
            if (i == p.size()) {
                bang = true;
                break;
            }

            // else try the other towels
            string rest = p.substr(i);
            for (string t : towels) {
                if (t.size() <= rest.size() && t == rest.substr(0, t.size())) {
                    q.push(i + t.size());
                }
            }
        }
        ans += bang;
    }
    cout << ans << "\n";
}

void solve2() {
    
}

int main() {
    input();
    solve1();
    return 0;
}