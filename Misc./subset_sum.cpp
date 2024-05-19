#include <vector>
#include <algorithm>
#include <cassert>

std::vector<int> subset_sum(const std::vector<int>& nums) {
    std::vector<int> sums{0};

    for(int num : nums) {
        size_t num_sums = sums.size();
        for(int j = 0; j < num_sums; ++j) {
            sums.push_back(sums[j] + num);
        }
    }

    return sums;
}

bool check_subset_sum(const std::vector<int>& nums, std::vector<int>& sol) {
    std::vector<int> sums = subset_sum(nums);
    std::sort(sums.begin(), sums.end());
    std::sort(sol.begin(), sol.end());
    return sums == sol;
}

int main() {
    auto nums = std::vector<int>{1};
    auto sol = std::vector<int>{0, 1};
    assert(check_subset_sum(nums, sol));

    nums = std::vector<int>{1, 2, 3};
    sol = std::vector<int>{0, 1, 2, 3, 3, 4, 5, 6};
    assert(check_subset_sum(nums, sol));

    nums = std::vector<int>{1, 5, 7};
    sol = std::vector<int>{0, 1, 5, 6, 7, 8, 12, 13};
    assert(check_subset_sum(nums, sol));

    nums = std::vector<int>{1, 5, 7, 4};
    sol = std::vector<int>{0, 1, 4, 5, 5, 6, 7, 8, 9, 10, 11, 12, 12, 13, 16, 17};
    assert(check_subset_sum(nums, sol));

    return 0;
}
