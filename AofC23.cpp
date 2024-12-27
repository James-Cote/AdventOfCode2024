/*

Advent of Code day 23
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

map<string, vector<string>> edges;
set<string> nodes;

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        int i = line.find('-');
        string u = line.substr(0, i);
        string v = line.substr(i+1);

        nodes.insert(u); nodes.insert(v);
        if (edges.find(u) == edges.end()) edges[u] = {v};
        else edges[u].push_back(v);

        if (edges.find(v) == edges.end()) edges[v] = {u};
        else edges[v].push_back(u);
        getline(cin, line);
    }
}

void solve1() {
    set<string> vis;
    auto i = nodes.begin();
    vector<vector<string>> groups;
    while (i != nodes.end()) {
        string s = *i;
        vis.insert(s);
        vector<string> e = edges[s];
        for (int i = 0; i < (int)e.size(); i++) {
            for (int j = i + 1; j < (int)e.size(); j++) {
                string a = e[i], b = e[j];
                if (vis.find(a) != vis.end() || vis.find(b) != vis.end()) continue;
                // check the third connection
                bool found = false;
                for (string c : edges[a]) {
                    if (c == b) {
                        found = true;
                        break;
                    }
                }
                if (found) groups.push_back({s, a, b});
            }
        }
        i++;
    }

    ll ans = 0;
    for (vector<string> group : groups) {
        cout << group[0] << "," << group[1] << "," <<  group[2] << "\n";
        if (group[0][0] == 't' || group[1][0] == 't' || group[2][0] == 't') ans++;

    }
    cout << ans << "\n";
}

vector<vector<string>> getPossibleEdges(vector<string>& e, int m, int i = 0) {
    if (m == 0) return {{}};
    if (i == e.size()) return {};

    vector<vector<string>> ans = getPossibleEdges(e, m - 1, i + 1);
    for (vector<string>& v : ans) {
        v.push_back(e[i]);
    }
    vector<vector<string>> lans = getPossibleEdges(e, m, i + 1);
    ans.insert(ans.end(), lans.begin(), lans.end());
    return ans;
}

void solve2() {
    // find the biggest lobby of nerds
    // binary search the answer
    int l = 2;
    int r = 20;
    vector<string> group;  //store the group
    while (r - l > 1) {
        int m = (r + l) / 2;
        cout << "M: " << m << '\n';

        set<string> vis;
        bool found = false;
        auto it = nodes.begin();
        while (it != nodes.end() && !found) {
            string s = *it;
            vis.insert(s);
            // get edges
            vector<string> e = edges[s];
            // strip the edges that are not VALID
            for (int i = 0; i < (int)e.size(); i++) {
                if ((int)edges[e[i]].size() < m || vis.find(e[i]) != vis.end()) {
                    e.erase(e.begin() + i);
                    i--;
                }
            }

            if ((int)e.size() >= m) {
                // test the edges
                vector<vector<string>> combs = getPossibleEdges(e, m);
                for (vector<string>& v : combs) {
                    set<string> mp(v.begin(), v.end());
                    
                    bool valid = true;
                    for (string u : v) {
                        int count = 0;
                        for (string ne : edges[u]) {
                            count += (mp.find(ne) != mp.end());
                        }
                        if (count != m - 1) {
                            valid = false;
                            break;
                        }
                    }

                    if (valid) {
                        found = true;
                        group = v;
                        group.push_back(s);
                    }
                }
            }
            it++;
        }

        if (found) l = m;
        else r = m;
    }

    cout << "Group of " << r << "\n";

    sort(group.begin(), group.end());
    for (int i = 0; i < (int)group.size(); i++) {
        cout << group[i] << (i == (int)group.size() - 1 ? "\n" : ",");
    }
}

int main() {
    input();
    solve2();
    return 0;
}