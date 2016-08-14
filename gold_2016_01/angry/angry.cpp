#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int partition(int *arr, const int left, const int right) {
    const int mid = left + (right - left) / 2;
    const int pivot = arr[mid];
    // move the mid point value to the front.
    swap(arr[mid],arr[left]);
    int i = left + 1;
    int j = right;
    while (i <= j) {
        while(i <= j && arr[i] <= pivot) {
            i++;
        }

        while(i <= j && arr[j] > pivot) {
            j--;
        }

        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i - 1],arr[left]);
    return i - 1;
}

void quicksort(int *arr, const int left, const int right, const int sz){

    if (left >= right) {
        return;
    }

    int part = partition(arr, left, right);

    quicksort(arr, left, part - 1, sz);
    quicksort(arr, part + 1, right, sz);
}


int main() {
    int N, c, i, Rl, Rr, ml, mr, max_dist = 0;
    c = 0;
    i = 0;
    
    ifstream fin("angry.in");

    fin >> N;

    int locations[N];

    for (c = 0 ; c < N ; c++) {
        fin >> locations[c];
    }

    fin.close();

    quicksort(locations, 0, N - 1, N);

    int dist[N - 1];

    for (i = 0 ; i < N - 1 ; i++) {
        dist[i] = locations[i + 1] - locations[i];
        if (dist[i] > max_dist) {
            max_dist = dist[i];
            ml = i;
            mr = i + 1;
        }
    }

    float Rm = dist[ml] / 2.;

    Rl = dist[0];

    for (i = 1 ; i < ml ; i++) {
        if (Rl + 1 < dist[i]) {
            Rl = dist[i];
        }
        else {
            Rl++;
        }
    }

    if (Rl < Rm) {
        Rl++;
    }

    // cout << Rl;

    Rr = dist[N - 2];

    for (i = N - 3 ; i >= mr ; i--) {
        if (Rr + 1 < dist[i]) {
            Rr = dist[i];
        }
        else {
            Rr++;
        }
    }

    if (Rr < Rm) {
        Rr++;
    }

    // cout << Rr;

    //cout << Rm;

    float real_max;
    if (Rr >= Rm) {
        real_max = Rr;
    }
    else {
        real_max = Rm;
    }

    if (real_max < Rl) {
        real_max = Rl;
    }

    ofstream fout("angry.out");

    fout << setiosflags(ios::fixed) << setprecision(1) << real_max << '\n';

    return 0;
}
