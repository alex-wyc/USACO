#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> coor;
typedef vector<coor> pair_vec_t;

int lit_element(int *lit_grid[], pair_vec_t coors) {
    int i;
    coor current;
    for (i = 0 ; i < coors.size() ; i++) {
        current = coors.at(i);
        if (*(lit_grid[current.first] + current.second)) {
            return i;
        }
    }
    return -1;
}

bool in_bounds(int N, int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

int main() {
    int N, M, x, y, x2, y2;

    ifstream fin("lightson.in");
    fin >> N >> M;
    
    int *light_on[N];
    bool can_has_visited[N][N];
    // lawls screw memory, speed ftw!
    // basically holds all the cells that has been visited
    // + cells that are on the frontier right now, is there
    // to keep the frontier unique and short
    
    for (x = 0 ; x < N ; x++) {
        light_on[x] = (int *)(malloc(N * sizeof(int)));
        for (y = 0 ; y < N ; y++) {
            *(light_on[x] + y) = 0;
            can_has_visited[x][y] = false;
        }
    }
    
    pair_vec_t coors[N][N];
    pair_vec_t frontier;

    for (; M > 0 ; M--) {
        fin >> x >> y >> x2 >> y2;
        coors[x - 1][y - 1].push_back(make_pair(x2 - 1, y2 - 1));
    }

    frontier.push_back(make_pair(0, 0));
    *light_on[0] = 1;

    while ((M = lit_element(light_on, frontier)) != -1) {
        // leave your mark
        x = frontier.at(M).first;
        y = frontier.at(M).second;
        frontier.erase(frontier.begin() + M);

        // turn on the lights
        while (!coors[x][y].empty()) {
            x2 = coors[x][y].back().first;
            y2 = coors[x][y].back().second;
            *(light_on[x2] + y2) = 1;
            coors[x][y].pop_back();
        }

        // push neighbors
        if (in_bounds(N , x - 1, y) && !can_has_visited[x - 1][y]) {
            frontier.push_back(make_pair(x - 1, y));
            can_has_visited[x - 1][y] = true;
        }

        if (in_bounds(N , x + 1, y) && !can_has_visited[x + 1][y]) {
            frontier.push_back(make_pair(x + 1, y));
            can_has_visited[x + 1][y] = true;
        }

        if (in_bounds(N , x, y - 1) && !can_has_visited[x][y - 1]) {
            frontier.push_back(make_pair(x, y - 1));
            can_has_visited[x][y - 1] = true;
        }

        if (in_bounds(N , x, y + 1) && !can_has_visited[x][y + 1]) {
            frontier.push_back(make_pair(x, y + 1));
            can_has_visited[x][y + 1] = true;
        }
    }

    int sum = 0;

    for (x = 0 ; x < N ; x++) {
        for (y = 0 ; y < N ; y++) {
            sum += *(light_on[x] + y);
        }
    }

    ofstream fout("lightson.out");

    fout << sum << "\n";

    return 0;
}
