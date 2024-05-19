#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);

    int squeezed_a[100], count_a = 0, count = 0;

    for(int character; (character = std::getchar()) != '\n';) {
        if(character == 'Q') {
            squeezed_a[count++] = count_a;
            count_a = 0;
        } else if(character == 'A') {
            count_a++;
        }
    }

    int count_qaq = 0;
    for(int i = 1; i < count; i++) {
        count_qaq += i * squeezed_a[i] * (count - i);
    }

    std::cout << count_qaq << std::endl;

    return 0;
}
