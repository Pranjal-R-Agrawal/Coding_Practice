#include <cstdlib>
#include <cassert>

template <typename type>
class Minheap {
    type *heap;
    int size;
    int num_elements;

    public:
        Minheap(int initial_size, bool *success);
        ~Minheap();
        bool insert(type element);
        bool extract_min(type *element);
        bool is_empty();

    private:
        void heapify_up(int index);
        void heapify_down(int index);
        bool is_full();
};

/**
 * @brief Construct a new Minheap<type>:: Minheap object
 * @tparam type data type of the elements
 * @param initial_size initial size of the heap
 * @param success out parameter to indicate if the object was created successfully
 */
template<typename type>
Minheap<type>::Minheap(int initial_size, bool *success) {
    size = initial_size;
    num_elements = 0;
    heap = (int *) malloc(sizeof(type) * initial_size);
    *success = heap;
}

template<typename type>
Minheap<type>::~Minheap() {
    free(heap);
    heap = nullptr;
}

/**
 * @brief Check if the heap is empty
 * @tparam type data type of the elements
 * @return true if the heap is empty
 * @return false if the heap is not empty
 */
template<typename type>
bool Minheap<type>::is_empty() {
    return num_elements == 0;
}

/**
 * @brief Check if the heap is full
 * @tparam type data type of the elements
 * @return true if the heap is full
 * @return false if the heap is not full
 */
template<typename type>
bool Minheap<type>::is_full() {
    return num_elements == size;
}

/**
 * @brief Heapify the heap upwards
 * @tparam type data type of the elements
 * @param index index to start heapifying from
 */
template<typename type>
void Minheap<type>::heapify_up(int index) {
    while(index > 0 && heap[index] < heap[(index - 1) / 2]) {
        type temp = heap[index];
        heap[index] = heap[(index - 1) / 2];
        heap[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

/**
 * @brief Insert an element into the heap
 * @tparam type data type of the elements
 * @param element element to insert
 * @return true if the element was inserted successfully
 * @return false if the heap is full and the heap could not be resized
 */
template<typename type>
bool Minheap<type>::insert(type element) {
    if(is_full()) {
        type *new_heap = (type *) realloc(heap, sizeof(type) * size * 2);
        if(!new_heap) {
            return false;
        }

        heap = new_heap;
    }

    heap[num_elements++] = element;
    heapify_up(num_elements - 1);
    return true;
}

/**
 * @brief Heapify the heap downwards
 * @tparam type data type of the elements
 * @param index index to start heapifying from
 */
template<typename type>
void Minheap<type>::heapify_down(int index) {
    while(2 * index + 1 < num_elements) {
        int left_child = 2 * index + 1, right_child = 2 * index + 2;
        int smallest_child = left_child;

        if(right_child < num_elements && heap[right_child] < heap[left_child]) {
            smallest_child = right_child;
        }

        if(heap[index] < heap[smallest_child]) {
            break;
        }

        type temp = heap[index];
        heap[index] = heap[smallest_child];
        heap[smallest_child] = temp;
        index = smallest_child;
    }
}

/**
 * @brief Extract the minimum element from the heap
 * @tparam type data type of the elements
 * @param element out parameter to store the minimum element
 * @return true if the element was extracted successfully
 * @return false if the heap is empty
 */
template<typename type>
bool Minheap<type>::extract_min(type *element) {
    if(is_empty()) {
        return false;
    }

    *element = heap[0];
    heap[0] = heap[--num_elements];
    heapify_down(0);
    return true;
}

int main() {
    bool success;
    Minheap<int> *heap = new Minheap<int>(10, &success);
    if(!success) {
        return 1;
    }

    for(int i = 0; i < 10; i++) {
        heap->insert(i);
    }

    int element;
    for(int i = 0; i < 10; i++) {
        heap->extract_min(&element);
        assert(element == i);
    }

    assert(heap->is_empty());

    delete(heap);

    return 0;
}
