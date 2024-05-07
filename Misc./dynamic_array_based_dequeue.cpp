#include <cassert>
#include <cstring>

template <typename T>
class Dequeue {
    T *buffer;
    int head;
    int tail;
    int capacity;

    public:
        explicit Dequeue(int initial_size);
        ~Dequeue();
        void push_back(const T& element);
        void push_front(const T& element);
        bool pop_back(T& element);
        bool pop_front(T& element);
        bool empty();

    private:
        enum Operation {PUSH, POP};
        enum Direction {FRONT, BACK};

        void resize_if_needed();
        void linearise(T* new_buffer);
        bool full();
        int get_num_elements();
        void update_head_tail(Operation operation, Direction direction);
};

/**
 * @brief Construct a new Dequeue<T>:: Dequeue object
 * @tparam T data T of the elements
 * @param initial_size initial capacity of the dequeue
 * @param success out parameter to indicate if the object was created successfully
 */
template <typename T>
Dequeue<T>::Dequeue(int initial_size) {
    capacity = initial_size;
    head = tail = -1;
    buffer = new T[initial_size];
}

template<typename T>
Dequeue<T>::~Dequeue() {
    delete[] buffer;
    buffer = nullptr;
}

/**
 * @brief Check if the dequeue is empty
 * @tparam T data T of the elements
 * @return true if the dequeue is empty
 * @return false if the dequeue is not empty
 */
template <typename T>
inline bool Dequeue<T>::empty() {
    return head == -1;
}

/**
 * @brief Check if the dequeue is full
 * @tparam T data T of the elements
 * @return true if the dequeue is full
 * @return false if the dequeue is not full
 */
template<typename T>
inline bool Dequeue<T>::full() {
    return (head != 0 && ((head == tail + 1) || (head == tail - 1))) || (head == 0 && tail == capacity - 1);
}

/**
 * @brief Get the number of elements in the dequeue
 * @tparam T data T of the elements
 * @return int number of elements in the dequeue
 */
template<typename T>
int Dequeue<T>::get_num_elements() {
    if(empty()) {
        return 0;
    }

    return (tail >= head)? tail - head + 1 : (capacity - head) + (tail + 1);
}

/**
 * @brief Linearise the circular buffer and store the elements in a new buffer
 * @tparam T data T of the elements
 * @param new_buffer new buffer to store the elements
 */
template<typename T>
void Dequeue<T>::linearise(T *new_buffer) {
    if(head > tail) {
        memcpy(new_buffer, buffer + head, sizeof(T) * (capacity - head));
        memcpy(new_buffer + capacity - head, buffer, sizeof(T) * (tail + 1));
    } else if(!empty()) {
        memcpy(new_buffer, buffer + head, sizeof(T) * (tail - head + 1));
    }

    if(!empty()) {
        tail = get_num_elements() - 1;
        head = 0;
    } else {
        head = tail = -1;
    }
}

/**
 * @brief Resize the buffer if it is either full or less than 1/4th full
 * @tparam T data T of the elements
 * @return true if the buffer was resized successfully
 * @return false if the buffer could not be resized
 */
template<typename T>
void Dequeue<T>::resize_if_needed() {
    int new_capacity = capacity;
    if(full()) {
        new_capacity *= 2;
    } else if(get_num_elements() < capacity / 4) {
        new_capacity = (capacity / 2) + 1;
    } else {
        return;
    }


    T* new_buffer = new T[new_capacity];
    linearise(new_buffer);

    delete[] buffer;
    buffer = new_buffer;
    capacity = new_capacity;
}

template<typename T>
void Dequeue<T>::update_head_tail(Dequeue::Operation operation, Dequeue::Direction direction) {
    if(operation == PUSH) {
        if(empty()) {
            head = tail = 0;
        } else if(direction == FRONT) {
            head = (head == 0)? capacity - 1 : head - 1;
        } else {
            tail = (tail + 1) % capacity;
        }
    } else {
        if(get_num_elements() == 1) {
            head = tail = -1;
        } else if(direction == FRONT) {
            head = (head + 1) % capacity;
        } else {
            tail = (tail == 0)? capacity - 1 : tail - 1;
        }
    }
}

/**
 * @brief Remove the element from the front of the dequeue
 * @tparam T data T of the elements
 * @param element out parameter to store the element
 * @return true if the element was removed successfully
 * @return false if the dequeue is empty
 */
template<typename T>
bool Dequeue<T>::pop_front(T& element) {
    if(empty()) {
        return false;
    }

    element = buffer[head];
    update_head_tail(POP, FRONT);
    resize_if_needed();

    return true;
}

/**
 * @brief Add an element to the front of the dequeue
 * @tparam T data T of the elements
 * @param element element to be added
 * @return true if the element was added successfully
 * @return false if the dequeue is full and the capacity could not be increased
 */
template<typename T>
void Dequeue<T>::push_front(const T& element) {
    resize_if_needed();
    update_head_tail(PUSH, FRONT);
    buffer[head] = element;
}

/**
 * @brief Remove the element from the back of the dequeue
 * @tparam T data T of the elements
 * @param element out parameter to store the element
 * @return true if the element was removed successfully
 * @return false if the dequeue is empty
 */
template<typename T>
bool Dequeue<T>::pop_back(T& element) {
    if(empty()) {
        return false;
    }

    element = buffer[tail];
    update_head_tail(POP, BACK);
    resize_if_needed();

    return true;
}

/**
 * @brief Add an element to the back of the dequeue
 * @tparam T data T of the elements
 * @param element element to be added
 * @return true if the element was added successfully
 * @return false if the dequeue is full and the capacity could not be increased
 */
template<typename T>
void Dequeue<T>::push_back(const T& element) {
    resize_if_needed();
    update_head_tail(PUSH, BACK);
    buffer[tail] = element;
}

int main() {
    Dequeue<int> *dequeue = new Dequeue<int>(10);

    int element;
    assert(dequeue->empty());
    assert(!dequeue->pop_back(element));
    assert(!dequeue->pop_front(element));

    for(element = 0; element < 10; element++) {
        dequeue->push_front(element);
    }

    for(int i = 0; i < 10; i++) {
        assert(dequeue->pop_back(element));
        assert(element == i);
    }

    for(element = 0; element < 10; element++) {
        dequeue->push_back(element);
    }

    for(int i = 0; i < 10; i++) {
        assert(dequeue->pop_front(element));
        assert(element == i);
    }

    delete(dequeue);
}
