/*

Advent of Code day 9
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

ll n, m, tt, t, k, q;
string s;

void solve1() {
    vector<int> lfile;
    string line;
    cin >> line;

    for (int i = 0; i < line.size(); i++) {
        int num = line[i] - '0';
        vector<int> spots;
        if (i % 2 == 0) {
            int j = i / 2;
            spots = vector<int>(num, j);
        } else {
            spots = vector<int>(num, -1);
        }
        lfile.insert(lfile.end(), spots.begin(), spots.end());
    }

    int l = 0, r = lfile.size() - 1;
    while (l < r) {
        while (lfile[r] == -1) r--;
        while (lfile[l] != -1) l++;
        if (l >= r) break;
        lfile[l] = lfile[r];
        lfile[r] = -1;
    }

    ll ans = 0;

    for (int i = 0; i < lfile.size(); i++) {
        int num = lfile[i];
        if (num != -1) {
            ans += i * num;
        }
        string s = to_string(num);
        cout << (num == -1 ? "." : s);
    }
    cout << "\n";
    cout << ans << "\n";
}

void solve2() {
    vector<int> lfile;
    string line;
    cin >> line;

    for (int i = 0; i < line.size(); i++) {
        int num = line[i] - '0';
        vector<int> spots;
        if (i % 2 == 0) {
            int j = i / 2;
            spots = vector<int>(num, j);
        } else {
            spots = vector<int>(num, -1);
        }
        lfile.insert(lfile.end(), spots.begin(), spots.end());
    }

    int id_on = (line.size() + 1) / 2;
    while (id_on > 0) {
        int r = lfile.size() - 1;
        while (r >= 0 && lfile[r] != id_on) r--;
        int end = r;
        while (r >= 0 && lfile[r] == id_on) r--;
        r++;
        if (r <= 0) {
            id_on--;
            continue;
        }
        int size = end - r + 1;
        // find a spot
        int l = 0;
        for (int i = 0; i < r; i++) {
            if (lfile[i] != -1) l = i + 1;
            if (i - l + 1 >= size) {
                for (int j = l; j <= i; j++) lfile[j] = id_on;
                for (int j = r; j <= end; j++) lfile[j] = -1;
                break;
            }
        }
        id_on--;
    }

    ll ans = 0;

    for (int i = 0; i < lfile.size(); i++) {
        int num = lfile[i];
        if (num != -1) {
            ans += i * num;
        }
        string s = to_string(num);
        cout << (num == -1 ? "." : s);
    }
    cout << "\n";
    cout << ans << "\n";
}

int main() {
    solve2();
    return 0;
}