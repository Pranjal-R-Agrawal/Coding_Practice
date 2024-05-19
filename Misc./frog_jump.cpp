#include <unordered_map>
#include <set>
#include <cassert>

int frog_jump(std::unordered_map<int, int>& num_paths, const std::set<int>& jumps, int pos, int dest) {
    for(int jump : jumps) {
        if(pos + jump > dest) {
            break;
        }

        if(pos + jump == dest) {
            num_paths[pos]++;
            break;
        }

        if(num_paths.find(pos + jump) == num_paths.end()) {
            num_paths[pos + jump] = frog_jump(num_paths, jumps, pos + jump, dest);
        }

        num_paths[pos] += num_paths[pos + jump];
    }

    return num_paths[pos];
}

bool run_test(const std::set<int>& jumps, int dest, int sol) {
    std::unordered_map<int, int> num_paths;
    return frog_jump(num_paths, jumps, 0, dest) == sol;
}

int main() {
    assert(run_test(std::set<int>{}, 5, 0));
    assert(run_test(std::set<int>{1}, 5, 1));
    assert(run_test(std::set<int>{2}, 5, 0));
    assert(run_test(std::set<int>{1, 2}, 5, 8));
    assert(run_test(std::set<int>{1, 2, 5}, 5, 9));
    assert(run_test(std::set<int>{1, 2, 5, 3}, 5, 14));
    return 0;
}
