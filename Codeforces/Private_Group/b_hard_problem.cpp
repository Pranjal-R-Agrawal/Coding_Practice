#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using std::cin; using std::cout; using std::string;

constexpr unsigned long long int_max = std::numeric_limits<unsigned long long>::max();

bool smaller(const string& a, bool reverse_a, const string& b, bool reverse_b) {
    if(reverse_a && reverse_b) {
        return !std::lexicographical_compare(b.rbegin(), b.rend(), a.rbegin(), a.rend());
    } else if(!reverse_a && !reverse_b) {
        return !std::lexicographical_compare(b.begin(), b.end(), a.begin(), a.end());
    } else if(reverse_a) {
        return !std::lexicographical_compare(b.begin(), b.end(), a.rbegin(), a.rend());
    } else {
        return !std::lexicographical_compare(b.rbegin(), b.rend(), a.begin(), a.end());
    }
}

int main() {
    int n; cin >> n;

    unsigned long long* energies = new unsigned long long [n];
    unsigned long long total_energy = 0;

    for(int i = 0; i < n; i++) {
        cin >> energies[i];
        total_energy += energies[i];
    }

    string prev_string, curr_string;
    unsigned long long prev_standard_energy = 0, prev_reverse_energy = 0, curr_standard_energy = int_max, curr_reverse_energy = int_max;

    for(int i = 0; i < n; i++) {
        cin >> curr_string;
        curr_standard_energy = curr_reverse_energy = int_max;

        if(smaller(prev_string, false, curr_string, false)) {
            curr_standard_energy = std::min(prev_standard_energy, curr_standard_energy);
        }

        if(smaller(prev_string, true, curr_string, false)) {
            curr_standard_energy = std::min(prev_reverse_energy, curr_standard_energy);
        }

        if(prev_standard_energy != int_max && smaller(prev_string, false, curr_string, true)) {
            curr_reverse_energy = std::min(prev_standard_energy + energies[i], curr_reverse_energy);
        }

        if(prev_reverse_energy != int_max && smaller(prev_string, true, curr_string, true)) {
            curr_reverse_energy = std::min(prev_reverse_energy + energies[i], curr_reverse_energy);
        }

        prev_string = curr_string;
        prev_standard_energy = curr_standard_energy; prev_reverse_energy = curr_reverse_energy;
    }

    unsigned long long min_energy = std::min(curr_standard_energy, curr_reverse_energy);

    if(min_energy != int_max) {
        cout << min_energy << '\n';
    } else {
        cout << -1 << '\n';
    }

    delete[] energies;

    return 0;
}
