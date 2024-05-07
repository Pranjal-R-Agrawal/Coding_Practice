#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstdio>

template <typename type>
class Dequeue {
    type *buffer;
    int start;
    int end;
    int size;

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
        int get_num_elements();
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
    start = end = -1;
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
inline bool Dequeue<type>::is_empty() {
    return start == -1;
}

/**
 * @brief Check if the dequeue is full
 * @tparam type data type of the elements
 * @return true if the dequeue is full
 * @return false if the dequeue is not full
 */
template<typename type>
inline bool Dequeue<type>::is_full() {
    return (start == end + 1) || (start == end - 1) || (start == 0 && end == size - 1);
}

/**
 * @brief Get the number of elements in the dequeue
 * @tparam type data type of the elements
 * @return int number of elements in the dequeue
 */
template<typename type>
int Dequeue<type>::get_num_elements() {
    if(is_empty()) {
        return 0;
    }

    return (end >= start)? end - start + 1 : (size - start) + (end + 1);
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
    } else if (!is_empty()) {
        memcpy(new_buffer, buffer + start, sizeof(type) * (end - start + 1));
    }

    free(buffer);
    buffer = nullptr;

    if(!is_empty()) {
        end = get_num_elements() - 1;
        start = 0;
    } else {
        start = end = -1;
    }
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
    if(get_num_elements() == 1) {
        start = end = -1;
    } else {
        start = (start + 1) % size;
    }

    if(get_num_elements() < size / 4) {
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

    if(is_empty()) {
        start = end = 0;
    } else {
        start = (start == 0)? size - 1 : start - 1;
    }

    buffer[start] = *element;
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
    if(get_num_elements() == 1) {
        start = end = -1;
    } else {
        end = (end == 0)? size - 1 : end - 1;
    }

    if(get_num_elements() < size / 4) {
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

    if(is_empty()) {
        start = end = 0;
    } else {
        end = (end + 1) % size;
    }

    buffer[end] = *element;
    return true;
}

int main() {
    bool success;
    Dequeue<int> *dequeue = new Dequeue<int>(10, &success);

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
