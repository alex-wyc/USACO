#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    int N, c, card;

    ifstream fin("highcard.in");

    fin >> N;

    int cards[2 * N];

    for (c = 0 ; c < 2 * N ; c++) {
        cards[c] = 0;
    }

    for (c = 0 ; c < N ; c++) {
        fin >> card;
        cards[card - 1] = 1;
    }

    int wins = 0;
    int other_count = 0;
    int my_count = 0;
    int carryover = 0;

    c = 0;
    while (!cards[c]) {
        c++;
    }

    for (; c < 2 * N ; c++) {
        if (my_count && cards[c]) { // my_count > 0 but current card is not 0
            if (other_count >= my_count) {
                wins += my_count;
                carryover += other_count - my_count;
            }
            else {
                wins += other_count;
                if (carryover > (my_count - other_count)) {
                    wins += (my_count - other_count);
                    carryover -= (my_count - other_count);
                }
                else {
                    wins += carryover;
                    carryover = 0;
                }
            }
            other_count = 1;
            my_count = 0;
        }

        else if (my_count) {
            my_count++;
        }

        else if (!cards[c]) {
            my_count++;
        }

        else {
            other_count++;
        }
    }

    if (my_count) {
        wins += my_count;
    }

    ofstream fout("highcard.out");

    fout << wins << "\n";
}
