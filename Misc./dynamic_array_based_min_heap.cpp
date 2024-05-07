#include <cstdlib>
#include <cassert>
#include <vector>

template <typename T>
class Minheap {
    std::vector<T> heap;

    public:
        explicit Minheap(int initial_size);
        bool insert(const T& element);
        bool extract_min(T& element);
        bool empty();

    private:
        void heapify_up(int index);
        void heapify_down(int index);
};

/**
 * @brief Construct a new Minheap<T>:: Minheap object
 * @tparam T data T of the elements
 * @param initial_size initial capacity of the heap
 */
template<typename T>
Minheap<T>::Minheap(int initial_size) {
    heap = std::vector<T>(initial_size);
}

/**
 * @brief Check if the heap is empty
 * @tparam T data T of the elements
 * @return true if the heap is empty
 * @return false if the heap is not empty
 */
template<typename T>
inline bool Minheap<T>::empty() {
    return heap.empty();
}

/**
 * @brief Heapify the heap upwards
 * @tparam T data T of the elements
 * @param index index to head heapifying from
 */
template<typename T>
void Minheap<T>::heapify_up(int index) {
    while(index > 0 && heap[index] < heap[(index - 1) / 2]) {
        T temp = heap[index];
        heap[index] = heap[(index - 1) / 2];
        heap[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

/**
 * @brief Insert an element into the heap
 * @tparam T data T of the elements
 * @param element element to insert
 * @return true if the element was inserted successfully
 * @return false if the heap is full and the heap could not be resized
 */
template<typename T>
bool Minheap<T>::insert(const T& element) {
    heap.push_back(element);
    heapify_up(heap.size() - 1);
    return true;
}

/**
 * @brief Heapify the heap downwards
 * @tparam T data T of the elements
 * @param index index to head heapifying from
 */
template<typename T>
void Minheap<T>::heapify_down(int index) {
    while(2 * index + 1 < heap.size()) {
        int left_child = 2 * index + 1, right_child = 2 * index + 2;
        int smallest_child = left_child;

        if(right_child < heap.size() && heap[right_child] < heap[left_child]) {
            smallest_child = right_child;
        }

        if(heap[index] < heap[smallest_child]) {
            break;
        }

        T temp = heap[index];
        heap[index] = heap[smallest_child];
        heap[smallest_child] = temp;
        index = smallest_child;
    }
}

/**
 * @brief Extract the minimum element from the heap
 * @tparam T data T of the elements
 * @param element out parameter to store the minimum element
 * @return true if the element was extracted successfully
 * @return false if the heap is empty
 */
template<typename T>
bool Minheap<T>::extract_min(T& element) {
    if(empty()) {
        return false;
    }

    element = heap[0];
    heap[0] = heap[heap.size() - 1];
    heapify_down(0);
    heap.erase(heap.begin() + heap.size() - 1);
    return true;
}

int main() {
    Minheap<int> heap(20);
    std::vector<int> test = std::vector<int>(20);

    for(int i = 0; i < 20; i++) {
        test.push_back(i);
    }

    std::random_shuffle(test.begin(), test.end());
    for(int i : test) {
        heap.insert(i);
    }

    int element;
    heap.extract_min(element);
    heap.insert(0);

    for(int i = 0; i < 20; i++) {
        heap.extract_min(element);
        assert(element == i);
    }

    assert(heap.empty());

    return 0;
}
