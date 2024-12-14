/*

Advent of Code day 13
- James Cote

*/

#include <bits\stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

struct Button {
    ld dx = 0, dy = 0;
    Button() {}
    Button(ld a, ld b) {
        dx = a;
        dy = b;
    }
};

struct Game {
    Button A, B;
    ld x = 0, y = 0;
    Game () {}
    Game (Button a, Button b, ld c, ld d) {
        A = a;
        B = b;
        x = c;
        y = d;
    }
};

vector<Game> machines;

void input() {
    string line;
    getline(cin, line);
    while (line != "") {
        Game cur;
        int i = 0;

        // Button A
        i = line.find('+');
        line = line.substr(i+1);
        i = line.find(' ');
        cur.A.dx = stoi(line.substr(0, i));
        i = line.find('+');
        cur.A.dy = stoi(line.substr(i+1));
        getline(cin, line);

        // Button B
        i = line.find('+');
        line = line.substr(i+1);
        i = line.find(' ');
        cur.B.dx = stoi(line.substr(0, i));
        i = line.find('+');
        cur.B.dy = stoi(line.substr(i+1));
        getline(cin, line);

        // Prize
        i = line.find('=');
        line = line.substr(i+1);
        i = line.find(',');
        cur.x = stoi(line.substr(0, i));
        i = line.find('=');
        cur.y = stoi(line.substr(i+1));
        getline(cin, line);

        machines.push_back(cur);

        getline(cin, line);
    }
}

void solve1() {
    ll ans = 0;
    for (Game g : machines) {
        ll local_ans = 500;

        int ia = min(g.x / g.A.dx, g.y / g.A.dy);
        ia = min(ia, 100);
        ll price = ia * 3;
        ll cur_x = g.A.dx * ia;
        ll cur_y = g.A.dy * ia;
        int ib = 0;

        while (ia >= 0) {
            while (ib < 100 && cur_x + g.B.dx <= g.x && cur_y + g.B.dy <= g.y) {
                ib++;
                price++;
                cur_x += g.B.dx;
                cur_y += g.B.dy;
            }

            if (cur_x == g.x && cur_y == g.y) {
                local_ans = min(local_ans, price);
            }

            ia--;
            price -= 3;
            cur_x -= g.A.dx;
            cur_y -= g.A.dy;
        }

        if (local_ans < 500) ans += local_ans;
    }

    cout << ans << "\n";
}

void solve2() {
    ll ans = 0;
    int i = 0;
    for (Game g : machines) {
        i++;
        g.x += 10000000000000;
        g.y += 10000000000000;

        ld nbd = (g.y - (g.x * g.A.dy / g.A.dx)) / (g.B.dy - (g.B.dx * g.A.dy / g.A.dx));
        ll nb = nbd;

        ld nad = (g.x - (g.B.dx * nb)) / g.A.dx;
        ll na = nad;

        bool found = false;
        na += 50;
        ll cur_x = na * g.A.dx + nb * g.B.dx;
        ll cur_y = na * g.A.dy + nb * g.B.dy;
        for (int i = 0; i < 100; i++) {
            while (cur_x + g.B.dx <= g.x && cur_y + g.B.dy <= g.y) {
                nb++;
                cur_x += g.B.dx;
                cur_y += g.B.dy;
            }
            if (cur_x == g.x && cur_y == g.y) {
                found = true;
                break;
            }
            na--;
            cur_x -= g.A.dx;
            cur_y -= g.A.dy;
        }

        //cout << i << '\n';
        //cout << na << "  " << nb << "\n";

        if (found) ans += na * 3LL + nb;
    }

    cout << ans << "\n";
}

int main() {
    input();
    solve2();
    return 0;
}