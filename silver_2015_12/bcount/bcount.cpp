#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

int main(void) {
    int N, Q, c, b;
    ifstream fin("bcount.in");
    fin >> N >> Q;

    int breed1[N + 1];
    int breed2[N + 1];
    int breed3[N + 1];

    breed1[0] = breed2[0] = breed3[0] = 0;

    for (c = 1 ; c <= N ; c++) {
        breed1[c] = breed1[c - 1];
        breed2[c] = breed2[c - 1];
        breed3[c] = breed3[c - 1];

        fin >> b;

        switch(b) {
            case 1:
                breed1[c]++;
                break;
            case 2:
                breed2[c]++;
                break;
            case 3:
                breed3[c]++;
                break;
        }
    }

    ofstream fout("bcount.out");

    for (; Q > 0 ; Q--) {
        fin >> c >> b;
        fout << breed1[b] - breed1[c - 1] << " ";
        fout << breed2[b] - breed2[c - 1] << " ";
        fout << breed3[b] - breed3[c - 1] << "\n";
    }

    fin.close();
    fout.close();
    
    return 0;
}
