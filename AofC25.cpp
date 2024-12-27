/*

Advent of Code day 25
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

vector<vector<int>> keys;
vector<vector<int>> locks;

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        bool lock = line[0] == '#';
        
        vector<int> heights(5);
        for (int i = 0; i < 5; i++) {
            getline(cin, line);
            for (int j = 0; j < line.size(); j++) {
                heights[j] += line[j] == '#';
            }
        }

        if (lock) locks.push_back(heights);
        else keys.push_back(heights);

        for (int i = 0; i < 3; i++) getline(cin, line);
    }
}

void solve1() {
    ll ans = 0;
    for (vector<int> key : keys) {
        for (vector<int> lock : locks) {
            bool valid = true;
            for (int i = 0; i < key.size(); i++) {
                if (key[i] + lock[i] > 5) valid = false;
            }
            ans += valid;
        }
    }
    cout << "Possible Keys: " << ans << '\n';
}

void solve2() {
    
}

int main() {
    input();
    solve1();
    return 0;
}