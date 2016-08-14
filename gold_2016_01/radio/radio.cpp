#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

typedef pair<int, int> coor;

void parse_direction(char given, coor *fj) {
    switch(given) {
        case 'N':
            fj->second++;
            break;
        case 'S':
            fj->second--;
            break;
        case 'W':
            fj->first--;
            break;
        case 'E':
            fj->first++;
            break;
    }
}

void reverse(char given, coor *fj) {
    switch(given) {
        case 'N':
            fj->second--;
            break;
        case 'S':
            fj->second++;
            break;
        case 'W':
            fj->first++;
            break;
        case 'E':
            fj->first--;
            break;
    }
}

int main() {
    int N, M;
    coor fj, be;

    ifstream fin("radio.in");
    fin >> N >> M;

    fin >> fj.first >> fj.second;
    fin >> be.first >> be.second;

    char fj_steps[N];
    char be_steps[M];

    fin >> fj_steps;

    fin >> be_steps;

    fin.close();

    int i = 0, j = 0;
    int d1, d2, d3; // fj moves, both moves or be moves
    int d = 0;

    for (i = 0 ; i < N ; i++) {
        parse_direction(fj_steps[i], &fj);
    }

    for (i = 0 ; i < M ; i++) {
        parse_direction(be_steps[i], &be);
    }

    N--;
    M--;

    while (N >= 0 && M >= 0) {
        cout << "current dist: " << d << '\n';
        cout << "fj: " << fj.first << ", " << fj.second << '\n';
        cout << "be: " << be.first << ", " << be.second << '\n';
        // first if only fj moves
        reverse(fj_steps[N], &fj);
        d1 = ((fj.first - be.first) * (fj.first - be.first) +
             (fj.second - be.second) * (fj.second - be.second));

        // second if both moves
        reverse(be_steps[M], &be);
        d2 = ((fj.first - be.first) * (fj.first - be.first) +
             (fj.second - be.second) * (fj.second - be.second));

        // third if only be moves
        parse_direction(fj_steps[N], &fj);
        d3 = ((fj.first - be.first) * (fj.first - be.first) +
             (fj.second - be.second) * (fj.second - be.second));

        if (d1 < d2) {
            if (d1 < d3) {
                cout << "fj moves\n";
                d += d1;
                parse_direction(be_steps[M], &be);
                reverse(fj_steps[N], &fj);
                N--;
            }
            else {
                cout << "be moves\n";
                d += d3;
                M--;
            }
        }
        else {
            if (d2 < d3) {
                cout << "both move\n";
                d += d2;
                reverse(fj_steps[N], &fj);
                N--;
                M--;
            }
            else {
                cout << "be moves\n";
                d += d3;
                M--;
            }
        }
    }

    if (N == -1) { // fj's done
        for (; M >= 0 ; M--) {
            reverse(be_steps[M], &be);
            d += ((fj.first - be.first) * (fj.first - be.first) +
                 (fj.second - be.second) * (fj.second - be.second));
        }
    }
    else if (M == -1) {
        for (; N >= 0 ; N++) {
            reverse(fj_steps[N], &fj);
            d += ((fj.first - be.first) * (fj.first - be.first) +
                 (fj.second - be.second) * (fj.second - be.second));
        }
    }

    cout << d;
    return 0;
}
