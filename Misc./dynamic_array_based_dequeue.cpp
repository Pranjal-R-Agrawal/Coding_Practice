#include <cstdlib>
#include <cstring>
#include <cassert>

template <typename type>
class Dequeue {
    type *buffer;
    int start;
    int end;
    int size;
    int num_elements;

    public:
        Dequeue(int initial_size, bool *success);
        ~Dequeue();
        bool push_back(type *element);
        bool push_front(type *element);
        bool pop_back(type *element);
        bool pop_front(type *element);
        bool is_empty();

    private:
        bool increase_size();
        bool decrease_size();
        void linearise(type *new_buffer);
        bool is_full();
};

/**
 * @brief Construct a new Dequeue<type>:: Dequeue object
 * @tparam type data type of the elements
 * @param initial_size initial size of the dequeue
 * @param success out parameter to indicate if the object was created successfully
 */
template <typename type>
Dequeue<type>::Dequeue(int initial_size, bool *success) {
    size = initial_size;
    start = end = num_elements = 0;
    buffer = (type *) malloc(sizeof(type) * initial_size);
    *success = buffer;
}

template<typename type>
Dequeue<type>::~Dequeue() {
    free(buffer);
    buffer = nullptr;
}

/**
 * @brief Check if the dequeue is empty
 * @tparam type data type of the elements
 * @return true if the dequeue is empty
 * @return false if the dequeue is not empty
 */
template <typename type>
bool Dequeue<type>::is_empty() {
    return num_elements == 0;
}

/**
 * @brief Check if the dequeue is full
 * @tparam type data type of the elements
 * @return true if the dequeue is full
 * @return false if the dequeue is not full
 */
template<typename type>
bool Dequeue<type>::is_full() {
    return num_elements == size;
}

/**
 * @brief Linearise the circular buffer and store the elements in a new buffer
 * @tparam type data type of the elements
 * @param new_buffer new buffer to store the elements
 */
template<typename type>
void Dequeue<type>::linearise(type *new_buffer) {
    if(start > end) {
        memcpy(new_buffer, buffer + start, sizeof(type) * (size - start));
        memcpy(new_buffer + size - start, buffer, sizeof(type) * (end + 1));
    } else {
        memcpy(new_buffer, buffer + start, sizeof(type) * (end - start + 1));
    }

    free(buffer);
    buffer = nullptr;

    end = num_elements - 1;
    start = 0;
}

/**
 * @brief Double the size of the buffer
 * @tparam type data type of the elements
 * @return true if the size was increased successfully
 * @return false if the size could not be increased
 */
template<typename type>
bool Dequeue<type>::increase_size() {
    type *new_buffer = (type *) malloc(sizeof(type) * size * 2);
    if(!new_buffer) {
        return false;
    }

    linearise(new_buffer);
    buffer = new_buffer;
    size *= 2;

    return true;
}

/**
 * @brief Halve the size of the buffer
 * @tparam type data type of the elements
 * @return true if the size was decreased successfully
 * @return false if the size could not be decreased
 */
template<typename type>
bool Dequeue<type>::decrease_size() {
    type *new_buffer = (type *) malloc(sizeof(type) * ((size / 2) + 1));
    if(!new_buffer) {
        return false;
    }

    linearise(new_buffer);
    buffer = new_buffer;
    size = (size / 2) + 1;

    return true;
}

/**
 * @brief Remove the element from the front of the dequeue
 * @tparam type data type of the elements
 * @param element out parameter to store the element
 * @return true if the element was removed successfully
 * @return false if the dequeue is empty
 */
template<typename type>
bool Dequeue<type>::pop_front(type *element) {
    if(is_empty()) {
        return false;
    }

    *element = buffer[start];
    start = (start + 1) % size;
    num_elements -= 1;

    if(num_elements < size / 4) {
        decrease_size();
    }

    return true;
}

/**
 * @brief Add an element to the front of the dequeue
 * @tparam type data type of the elements
 * @param element element to be added
 * @return true if the element was added successfully
 * @return false if the dequeue is full and the size could not be increased
 */
template<typename type>
bool Dequeue<type>::push_front(type *element) {
    if(is_full() && !increase_size()) {
        return false;
    }

    start = (start == 0)? size - 1 : start - 1;
    buffer[start] = *element;
    num_elements += 1;
    return true;
}

/**
 * @brief Remove the element from the back of the dequeue
 * @tparam type data type of the elements
 * @param element out parameter to store the element
 * @return true if the element was removed successfully
 * @return false if the dequeue is empty
 */
template<typename type>
bool Dequeue<type>::pop_back(type *element) {
    if(is_empty()) {
        return false;
    }

    *element = buffer[end];
    end = (end == 0)? size - 1 : end - 1;
    num_elements -= 1;

    if(num_elements < size / 4) {
        decrease_size();
    }

    return true;
}

/**
 * @brief Add an element to the back of the dequeue
 * @tparam type data type of the elements
 * @param element element to be added
 * @return true if the element was added successfully
 * @return false if the dequeue is full and the size could not be increased
 */
template<typename type>
bool Dequeue<type>::push_back(type *element) {
    if(is_full() && !increase_size()) {
        return false;
    }

    end = (end + 1) % size;
    buffer[end] = *element;
    num_elements += 1;
    return true;
}

int main() {
    bool success;
    Dequeue<int> *dequeue = new Dequeue<int>(1, &success);

    int element;
    assert(dequeue->is_empty());
    assert(!dequeue->pop_back(&element));
    assert(!dequeue->pop_front(&element));

    for(element = 0; element < 10; element++) {
        assert(dequeue->push_front(&element));
    }

    for(int i = 0; i < 10; i++) {
        assert(dequeue->pop_back(&element));
        assert(element == i);
    }

    for(element = 0; element < 10; element++) {
        assert(dequeue->push_back(&element));
    }

    for(int i = 0; i < 10; i++) {
        assert(dequeue->pop_front(&element));
        assert(element == i);
    }

    delete(dequeue);
}
