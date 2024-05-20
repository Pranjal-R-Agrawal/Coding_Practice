#include <iostream>
#include <vector>

using std::cin;
using std::cout;

typedef struct { int v; int w; } item;

int main() {
    std::ios_base::sync_with_stdio(false);

    int n, w;
    cin >> n >> w;

    std::vector<item> in; in.resize(n);

    for(int i = 0; i < n; i++) {
        cin >> in[i].v;
    }

    for(int i = 0; i < n; i++) {
        cin >> in[i].w;
    }

    std::vector<std::vector<int>> vals(n + 1, std::vector<int>(w + 1));
    int max_value = 0;
    for(int i = 1; i < n + 1; i++) {
        for(int j = 1; j < w + 1; j++) {
            vals[i][j] = std::max(vals[i-1][j], (j >= in[i-1].w)? vals[i-1][j-in[i-1].w] + in[i-1].v : 0);
            max_value = std::max(max_value, vals[i][j]);
        }
    }

    cout << max_value << std::endl;

    return 0;
}
