/*

Advent of Code day 17
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = int;

vector<ll> registers;
vector<ll> program;

void input() {
    string line;
    for (int i = 0; i < 3; i++) {
        getline(cin, line);
        int j = line.find(':');
        registers.push_back(stoll(line.substr(j + 2)));
    }

    getline(cin, line);
    getline(cin, line);
    int j = line.find(':');
    line = line.substr(j + 2);

    // split by comma
    while (line != "") {
        j = line.find(',');
        if (j == -1) {
            program.push_back(stoll(line));
            break;
        }
        program.push_back(stoll(line.substr(0, j)));
        line = line.substr(j + 1);
    }
}

void solve1() {
    vector<int> ans;
    int i = 0;
    while (i < program.size() - 1) {
        cout << i << "\n";
        for (int j = 0; j < registers.size(); j++) cout << registers[j] << " ";
        cout << "\n";

        ll opcode = program[i];
        ll n_val = program[i+1];

        if (opcode == 0) {
            //adv
            // performs division (A // (2^>)) -> A
            if (n_val >= 4) n_val = registers[n_val - 4];
            registers[0] = floor(registers[0] / pow(2, n_val));
        } else if (opcode == 1) {
            //bxl
            // Bitwise (XOR of B and >) -> B
            registers[1] = registers[1] ^ n_val;
        } else if (opcode == 2) {
            //bst
            // Modulo 8 -> B
            if (n_val >= 4) n_val = registers[n_val - 4];
            registers[1] = n_val % 8;
        } else if (opcode == 3) {
            //jnz
            // if A is 0 it does nothing
            // however it can also jump to > if not
            if (registers[0] != 0) {
                i = n_val;
                continue;
            }
        } else if (opcode == 4) {
            //bxc
            // bitwise XOR of B and C -> B
            registers[1] = registers[1] ^ registers[2];
        } else if (opcode == 5) {
            //out
            // outputs > mod 8
            if (n_val >= 4) n_val = registers[n_val - 4];
            ans.push_back(n_val % 8);
        } else if (opcode == 6) {
            //bdv
            // performs division (B // (2^>)) -> A
            if (n_val >= 4) n_val = registers[n_val - 4];
            registers[1] = floor(registers[0] / pow(2, n_val));
        } else if (opcode == 7) {
            //cdv
            // performs division (C // (2^>)) -> A
            if (n_val >= 4) n_val = registers[n_val - 4];
            registers[2] = floor(registers[0] / pow(2, n_val));
        }
        i += 2;
    }

    for (int a : ans) cout << a << ",";
    cout << "\n";
}

void solve2() {
    
}

int main() {
    input();
    solve1();
    return 0;
}