#include <iostream>
#include <vector>
#include <set>

using std::cin;
using std::cout;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    std::vector<int> input; input.reserve(n);
    std::set<int> unique;

    for(int i = 0; i < n; i++) {
        cin >> input[i];
    }

    for(int i = n - 1; i >= 0; i--) {
        unique.insert(input[i]);
        input[i] = unique.size();
    }

    for(int i = 0, j; i < m; i++) {
        cin >> j;
        cout << input[j - 1] << '\n';
    }


    return 0;
}
