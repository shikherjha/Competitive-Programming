#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S;
    cin >> S;

    vector<vector<string>> grid(S, vector<string>(S));
    for (int z = 0; z < S; ++z) {
        for (int x = 0; x < S; ++x) {
            cin >> grid[z][x];
        }
    }

    int Sz, Sx, Sy, Gz, Gx, Gy;
    cin >> Sz >> Sx >> Sy;
    cin >> Gz >> Gx >> Gy;

    if (grid[Sz][Sx][Sy] == 'E' || grid[Gz][Gx][Gy] == 'E') {
        cout << -1 << '\n';
        return 0;
    }

    vector<vector<vector<int>>> dist(S, vector<vector<int>>(S, vector<int>(S, -1)));
    queue<tuple<int, int, int>> q;
    dist[Sz][Sx][Sy] = 0;
    q.push(make_tuple(Sz, Sx, Sy));

    const int wireless_dirs[4][3] = {
        {1, 0, 0},
        {-1, 0, 0},
        {0, 0, 1},
        {0, 0, -1}
    };

    while (!q.empty()) {
        tuple<int, int, int> curr = q.front();
        q.pop();
        int z = get<0>(curr);
        int x = get<1>(curr);
        int y = get<2>(curr);

        if (z == Gz && x == Gx && y == Gy) {
            cout << dist[z][x][y] << '\n';
            return 0;
        }

        // A. Wireless moves
        for (int i = 0; i < 4; ++i) {
            int dz = wireless_dirs[i][0];
            int dx = wireless_dirs[i][1];
            int dy = wireless_dirs[i][2];
            int nz = z + dz;
            int nx = x + dx;
            int ny = y + dy;
            if (nz >= 0 && nz < S && nx >= 0 && nx < S && ny >= 0 && ny < S) {
                if (grid[nz][nx][ny] != 'E' && dist[nz][nx][ny] == -1) {
                    dist[nz][nx][ny] = dist[z][x][y] + 1;
                    q.push(make_tuple(nz, nx, ny));
                }
            }
        }

        char cur = grid[z][x][y];

        // B. Forward hardline moves
        vector<tuple<int, int, int>> forward;
        if (cur == 'L') {
            forward.push_back(make_tuple(z, x - 1, y - 1));
        } else if (cur == 'R') {
            forward.push_back(make_tuple(z, x - 1, y + 1));
        } else if (cur == 'F') {
            forward.push_back(make_tuple(z + 1, x + 1, y));
            forward.push_back(make_tuple(z - 1, x - 1, y));
        } else if (cur == 'B') {
            forward.push_back(make_tuple(z + 1, x - 1, y));
            forward.push_back(make_tuple(z - 1, x + 1, y));
        }

        for (size_t i = 0; i < forward.size(); ++i) {
            int nz = get<0>(forward[i]);
            int nx = get<1>(forward[i]);
            int ny = get<2>(forward[i]);
            if (nz >= 0 && nz < S && nx >= 0 && nx < S && ny >= 0 && ny < S) {
                if (grid[nz][nx][ny] != 'E' && dist[nz][nx][ny] == -1) {
                    dist[nz][nx][ny] = dist[z][x][y] + 1;
                    q.push(make_tuple(nz, nx, ny));
                }
            }
        }

        // C. Reverse hardline moves: define a simple struct for clarity in C++11
        struct ReverseCheck {
            int nz, nx, ny;
            char req_type;
            ReverseCheck(int a, int b, int c, char d) : nz(a), nx(b), ny(c), req_type(d) {}
        };

        ReverseCheck reverse_checks[] = {
            ReverseCheck(z, x + 1, y + 1, 'L'),
            ReverseCheck(z, x + 1, y - 1, 'R'),
            ReverseCheck(z - 1, x - 1, y, 'F'),
            ReverseCheck(z + 1, x + 1, y, 'F'),
            ReverseCheck(z - 1, x + 1, y, 'B'),
            ReverseCheck(z + 1, x - 1, y, 'B')
        };

        for (int i = 0; i < 6; ++i) {
            int nz = reverse_checks[i].nz;
            int nx = reverse_checks[i].nx;
            int ny = reverse_checks[i].ny;
            char req_type = reverse_checks[i].req_type;

            if (nz >= 0 && nz < S && nx >= 0 && nx < S && ny >= 0 && ny < S) {
                if (grid[nz][nx][ny] == req_type && dist[nz][nx][ny] == -1) {
                    dist[nz][nx][ny] = dist[z][x][y] + 1;
                    q.push(make_tuple(nz, nx, ny));
                }
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}