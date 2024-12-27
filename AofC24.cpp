/*

Advent of Code day 24
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

map<string, int> wires;
map<string, vector<string>> gates;  // one gate has two operants
map<string, vector<string>> edges; // wires' edges to the operants
map<string, int> degree;

vector<string> str_ops;

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        int i = line.find(':');
        wires[line.substr(0, i)] = stoi(line.substr(i + 1));
        getline(cin, line);
    }
    
    getline(cin, line);
    while (line != "") {
        str_ops.push_back(line);
        vector<string> v;
        while (line != "") {
            int i = line.find(' ');
            if (i < 0) {
                v.push_back(line);
                break;
            }
            v.push_back(line.substr(0, i));
            line = line.substr(i+1);
        }

        // Store the gate information
        gates[v[4]] = {v[1], v[0], v[2]};

        // Store the edge information
        if (edges.find(v[0]) == edges.end()) edges[v[0]] = {v[4]};
        else edges[v[0]].push_back(v[4]);
        if (edges.find(v[2]) == edges.end()) edges[v[2]] = {v[4]};
        else edges[v[2]].push_back(v[4]);

        getline(cin, line);
    }
}

vector<int> solve1() {
    // Go through the wires that we already have to decrease the degree and save to queue
    queue<string> q;
    // auto it = wires.begin();
    // while (it != wires.end()) {
    //     string w = it->first;
    //     for (string s : edges[w]) {
    //         if (degree.find(s) == degree.end()) degree[s] = 2;
    //         degree[s]--;
    //         if (degree[s] == 0) q.push(s);
    //     }
    //     it++;
    // }
    auto it_gates = gates.begin();
    while (it_gates != gates.end()) {
        string s = it_gates->first;
        degree[s] = 2;
        degree[s] -= wires.find(it_gates->second[1]) != wires.end();
        degree[s] -= wires.find(it_gates->second[2]) != wires.end();
        if (degree[s] == 0) q.push(s);

        it_gates++;
    }

    while (!q.empty()) {
        string s = q.front(); q.pop();
        // calculate the string and queue the next wire connections if necessary

        int ans = 0;
        vector<string> op = gates[s];
        if (op[0] == "XOR") {
            ans = wires[op[1]] ^ wires[op[2]];
        } else if (op[0] == "OR") {
            ans = wires[op[1]] | wires[op[2]];
        } else if (op[0] == "AND") {
            ans = wires[op[1]] & wires[op[2]];
        }
        wires[s] = ans;

        // for (string ns : edges[s]) {
        //     if (degree.find(ns) == degree.end()) degree[ns] = 2;
        //     degree[ns]--;
        //     if (degree[ns] == 0) q.push(ns);
        // }

        // change the degree of the connected gates
        it_gates = gates.begin();
        while (it_gates != gates.end()) {
            if (it_gates->second[1] == s || it_gates->second[2] == s) {
                degree[it_gates->first]--;
                if (degree[it_gates->first] == 0) q.push(it_gates->first);
            }

            it_gates++;
        }
    }

    // Get the z numbers
    auto it = wires.begin();
    vector<pair<string, int>> znums;
    while (it != wires.end()) {
        if (it->first[0] == 'z') {
            znums.push_back({it->first, it->second});
        }
        it++;
    }

    // Calculate the total
    sort(znums.begin(), znums.end());
    vector<int> ans;
    for (auto& [s, n] : znums) {
        ans.push_back(n);
    }
    return ans;
}

void swap_gates(string u, string v) {
    vector<string> gateU = gates[u];
    gates[u] = gates[v];
    gates[v] = gateU;
}

void solve2() {
    // brute force the swaps
    // Swaps can never happen between wires that activate the same wires
    // Swaps can never be x00 or y00 or any number of those two
    // 222 available swapings

    // 0 + 0 = 0
    auto it = wires.begin();
    while (it != wires.end()) {
        it->second = 1;
        it++;
    }
    map<string, int> reset_wires = wires;

    ll correct_add = 0;
    ll two = 2;
    for (int i = 0; i < 45; i++) {
        correct_add += two;
        two *= 2LL;
    }
    cout << "ANS:  " << correct_add << "\n";

    // Get all the operators
    vector<string> ops;
    auto op_it = gates.begin();
    while (op_it != gates.end()) {
        ops.push_back(op_it->first);
        op_it++;
    }

    // The adder before the swaps
    for (int i = 0; i < 0; i++) {
        wires = reset_wires;
        string xstr = "x" + string(i < 10 ? "0" : "") + to_string(i);
        string ystr = "y" + string(i < 10 ? "0" : "") + to_string(i);
        cout << xstr << " " << ystr << "\n";
        wires[xstr] = 1;
        wires[ystr] = 1;
        degree = map<string, int>();

        vector<int> a = solve1();
        for (int i : a) cout << i << " ";
        cout << "\n";
    }
    
    // Binary Adder
    // first bit is x00 XOR y00
    // second bit is (x01 XOR y01) XOR (x00 AND y00)
    // third bit is (x02 XOR y02) XOR ((x01 AND x02) OR ((x01 OR y01) AND (x00 AND y00))
    // the rest of the bits follow the third bit
    // Swap Values
    swap_gates("z11", "vkq");
    swap_gates("z24", "mmk");
    swap_gates("z38", "hqh");
    swap_gates("qdq", "pvb");
    {
    wires = reset_wires;
    degree = map<string, int>();
    vector<int> a = solve1();
    ll lans = 0;
    ll two = 1;
    for (int i : a) {
        lans += i * two;
        two *= 2LL;
    }
    cout << lans << "\n";
    }

    vector<string> swap_ans = {"z11", "z24", "z38", "vkq", "mmk", "hqh", "qdq", "pvb"};

    // Find the last swap
    auto gate1 = gates.begin();
    gate1 = gates.end();
    while (gate1 != gates.end()) {
        auto gate2 = gate1;
        gate2++;
        while (gate2 != gates.end()) {
            // Find the gate that makes the addition work
            string s1 = gate1->first, s2 = gate2->first;
            if (gate1->second[1] == s2 || gate1->second[2] == s2 || gate2->second[1] == s1 || gate2->second[2] == s1) {
                gate2++;
                continue;
            }

            // swap and check
            swap(s1, s2);
            wires = reset_wires;
            degree = map<string, int>();
            vector<int> a = solve1();
            ll lans = 0;
            ll two = 1;
            for (int i : a) {
                lans += i * two;
                two *= 2LL;
            }
            if (lans == correct_add) {
                gate1 = gates.end();
                gate2 = gates.end();
                swap_ans.push_back(s1);
                swap_ans.push_back(s2);
            }
            // Swap back
            swap(s1, s2);
            gate2++;
        }
        gate1++;
    }
    sort(swap_ans.begin(), swap_ans.end());
    for (string code : swap_ans) cout << code << ",";
    cout << "\n";
}

/*//////
Findings:
z11 has to swap with vkq
z24 has to swap with mmk
z38 has to swap with hqh

*///////

int main() {
    input();
    solve2();
    return 0;
}