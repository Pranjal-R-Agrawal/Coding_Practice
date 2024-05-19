#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> coordinates; coordinates.reserve(n);
    std::vector<int> heights; heights.reserve(n);

    for(int i = 0; i < n; ++i) {
        std::cin >> coordinates[i] >> heights[i];
    }

    int count = std::min(2, n);

    for(int i = 1; i < n - 1; ++i) {
        if(coordinates[i] - heights[i] > coordinates[i - 1]) {
            count++;
        } else if(coordinates[i] + heights[i] < coordinates[i + 1]) {
            count++;
            coordinates[i] += heights[i];
        }
    }

    std::cout << count << std::endl;

    return 0;
}
