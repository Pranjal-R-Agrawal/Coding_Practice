#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    enum activity { NOTHING = 0, CONTEST = 1, GYM = 2, GYM_OR_CONTEST = 3 };
    std::vector<int> possible_activities; possible_activities.reserve(n);

    for(int i = 0; i < n; ++i) {
        std::cin >> possible_activities[i];
    }

    int num_rest_days = 0;
    activity next_activity = NOTHING;

    for(int i = n - 1; i >= 0; i--) {
        if(possible_activities[i] == NOTHING || possible_activities[i] == next_activity) {
            next_activity = NOTHING;
            num_rest_days++;
        } else if(possible_activities[i] == GYM_OR_CONTEST) {

            if(next_activity == CONTEST) {
                next_activity = GYM;
            } else if(next_activity == GYM) {
                next_activity = CONTEST;
            }

        } else {
            next_activity = static_cast<activity>(possible_activities[i]);
        }
    }

    std::cout << num_rest_days << std::endl;

    return 0;
}
