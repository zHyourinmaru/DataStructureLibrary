
namespace lasd {

/* ************************************************************************** */

// Specific Constructor

template<typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& structure) : head(0) {
    
    size = structure.Size() + 1;

    Array = new Data[size];

    for (ulong i = 0; i < structure.Size(); ++i) {

        Array[i] = structure[i];
    
    }

    tail = structure.Size();

    Expand();
}

/* ************************************************************************** */

// Move constructor

template<typename Data>
QueueVec<Data>::QueueVec(QueueVec&& structure) noexcept : Vector<Data>(std::move(structure)) {
    
    std::swap(tail, structure.tail);
    std::swap(head, structure.head);
}

/* ************************************************************************** */

// Copy assignment

template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& structure) {
    Vector<Data>::operator=(structure);
    tail = structure.tail;
    head = structure.head;
    return *this;
}

// Move assignment

template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& structure) noexcept {
    Vector<Data>::operator=(std::move(structure));
    std::swap(tail, structure.tail);
    std::swap(head, structure.head);
    return *this;
}

/* ************************************************************************** */

// Comparison operators

template<typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& structure) const noexcept {
    
    if (Size() == structure.Size()) {

        ulong i = head;
        ulong j = structure.head;

        while (i != tail) {

            if (Array[i] != structure.Array[j]) {

                return false;
            }
            
            if (i != (size-1))
                i++;
            else
                i = 0;
                            
            if (j != (structure.size - 1))
                j++;
            else
                j = 0;
        }

        return true;

    } else {

        return false;
    }
} 


template<typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& structure) const noexcept {
    return !(*this == structure);
}


/* ************************************************************************** */

// Specific member functions (inherited from Queue)

template<typename Data>
const Data& QueueVec<Data>::Head() const {
    
    if (head != tail) {
        return (*this)[head];
    } else {
        throw std::length_error("The queue is empty.");
    }
}

template<typename Data>
Data& QueueVec<Data>::Head() {

    if (head != tail) {
        return (*this)[head];
    } else {
        throw std::length_error("The queue is empty.");
    }
}

template<typename Data>
void QueueVec<Data>::Dequeue() {

    if (head != tail) {
        
        if(head != (size - 1)) {
            head++;
        } else {
            head = 0;
        }
        
        Reduce();

    } else {
        throw std::length_error("The queue is empty.");
    }
}

template<typename Data>
Data QueueVec<Data>::HeadNDequeue() {
    
    if (head != tail) {

        Data value = (*this)[head];

        if(head != (size - 1)) {
            head++;
        } else {
            head = 0;
        }

        Reduce();

        return value;

    } else {
        throw std::length_error("The queue is empty.");
    }
}

template<typename Data>
void QueueVec<Data>::Enqueue(const Data& value) {
    
    Expand();
    (*this)[tail] = value;

    if(tail != (size - 1)) {
        tail++;
    } else {
        tail = 0;
    }
}

template<typename Data>
void QueueVec<Data>::Enqueue(Data&& value) {
    
    Expand();
    (*this)[tail] = std::move(value);
    
    if(tail != (size - 1)) {
        tail++;
    } else {
        tail = 0;
    }
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)

template<typename Data>
inline bool QueueVec<Data>::Empty() const noexcept {

    if(head == tail) {
        return true;
    } else {
        return false;
    }
}

template<typename Data>
inline ulong QueueVec<Data>::Size() const noexcept {

    if (head > tail) {
        return ((size - head) + tail);
    } else {
        return (tail-head);
    }
}

template<typename Data>
void QueueVec<Data>::Clear() {
    
    Vector<Data>::Clear();
    head = 0;
    tail = 0;
    SwapVectors(1);
}

/* ************************************************************************** */

// Auxiliary member functions

template<typename Data>
void QueueVec<Data>::Expand() {

    if(Size() == (size - 1)) {
        SwapVectors((this->size)*2);
    }
    
}

template<typename Data>
void QueueVec<Data>::Reduce() {

    if(Size() <= (size / 4)) {
        SwapVectors((this->size)/2);
    }
    
}

template<typename Data>
void QueueVec<Data>::SwapVectors(ulong newSize) {

    Data* TempArray = new Data[newSize] {};
    
    ulong i = head;
    ulong j = 0;

    while (i != tail) {

        std::swap(Array[i], TempArray[j]);
        
        if (i != (size-1))
            i++;
        else
            i = 0;
                        
       j++;
    }

    std::swap(Array, TempArray);
    size = newSize;

    head = 0;
    tail = j;
    delete[] TempArray;
}

}
