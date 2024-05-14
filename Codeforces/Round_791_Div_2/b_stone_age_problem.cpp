#include <iostream>
#include <vector>

#define ULL static_cast<unsigned long long>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, q;
    std::cin >> n >> q;

    unsigned long long sum = 0;
    std::vector<int> a(n), last_updated(n);
    int op2t = -1, op2val = 0;

    for(int i = 0; i < n; i++) {
        std::cin >> a[i];
        last_updated[i] = 0;
        sum += a[i];
    }

    for(int j = 0; j < q; j++) {
        int t, i ,x;
        std::cin >> t;

        if(t == 1) {
            std::cin >> i >> x;
            i -= 1;
            sum = sum - ULL((last_updated[i] > op2t)? a[i] : op2val) + ULL(x);
            a[i] = x;
            last_updated[i] = j;
        } else {
            std::cin >> op2val;
            op2t = j;
            sum = n * ULL(op2val);
        }

        std::cout << sum << std::endl;
    }

    return 0;
}
