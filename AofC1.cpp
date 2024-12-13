/*

Advent of Code day 1
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;

ll n, m, p, q, tt, t, k;
string s;

void solve1() {
    vector<ll> a;
    vector<ll> b;

    ll c, d;
    cin >> c >> d;
    while (c != 0 && d != 0) {
        a.push_back(c);
        b.push_back(d);
        cin >> c >> d;
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll ans = 0;
    for (ll i = 0; i < a.size(); i++) {
        ans += abs(a[i] - b[i]);
    }
    cout << ans << "\n";
}

void solve2() {
    vector<ll> a;
    map<ll, ll> mp;

    ll c, d;
    cin >> c >> d;
    while (c != 0 && d != 0) {
        a.push_back(c);
        if (mp.find(c) == mp.end()) mp[c] = 0;

        if (mp.find(d) == mp.end()) mp[d] = 1;
        else mp[d]++;

        cin >> c >> d;
    }

    ll ans = 0;
    for (ll i = 0; i < a.size(); i++) {
        ans += a[i] * mp[a[i]];
    }
    cout << ans << "\n";
}

int main() {
    ios :: sync_with_stdio(false);
	cin.tie(nullptr);
    
    solve2();

    return 0;
}