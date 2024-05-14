#include <iostream>
#include <set>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, q;
    std::cin >> n >> q;

    auto x = std::vector<int>(n + 1);
    auto y = std::vector<int>(n + 1);

    std::set<int> a, b;
    for(int i = 1; i < n + 1; ++i) {
        x[i] = y[i] = 0;
        a.insert(i);
        b.insert(i);
    }

    while (q--) {
        int t0, t1, t2;
        std::cin >> t0 >> t1 >> t2;

        if (t0 == 1) {

            if (x[t1] == 0) {
                a.erase(t1);
            }

            if (y[t2] == 0) {
                b.erase(t2);
            }

            x[t1]++;
            y[t2]++;

        } else if (t0 == 2) {

            x[t1]--;
            y[t2]--;

            if (x[t1] == 0) {
                a.insert(t1);
            }

            if (y[t2] == 0) {
                b.insert(t2);
            }

        } else {

            int t3, t4;
            std::cin >> t3 >> t4;
            int min_range_a = *a.lower_bound(t1);
            int min_range_b = *b.lower_bound(t2);
            std::cout << ( t1 <= min_range_a && min_range_a <= t3 && t2 <= min_range_b && min_range_b <= t4 ? "No" : "Yes") << std::endl;

        }
    }

    return 0;
}
