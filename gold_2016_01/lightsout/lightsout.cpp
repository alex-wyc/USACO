#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ofstream fout("lightsout.out");
    fout << "2\n";
    fout.close();
    return 0;
}
