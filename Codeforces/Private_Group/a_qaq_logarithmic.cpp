#include <iostream>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);

    int character; int relative_pos = 0;
    std::map<int, int> q_locs; int count_q = 0;
    std::map<int, int> a_locs; int count_a = 0;

    while(character = std::getchar(), character != '\n') {
        if(character == 'Q') {
            q_locs[relative_pos--] = ++count_q;
        } else if(character == 'A') {
            a_locs[relative_pos--] = ++count_a;
        }
    }

    int count_qaq = 0, num_a_seen = 0;
    for(auto q_loc : q_locs) {
        auto a_loc_itr = a_locs.find(q_loc.first - 1);
        if(a_loc_itr == a_locs.end()) {
            continue;
        }

        count_qaq += q_loc.second * (count_q - q_loc.second) * (count_a - a_loc_itr->second + 1 - num_a_seen);
        num_a_seen = count_a - a_loc_itr->second + 1;
    }

    std::cout << count_qaq << std::endl;

    return 0;
}
