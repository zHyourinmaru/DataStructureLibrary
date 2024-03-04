
namespace lasd {


/* ************************************************************************** */

// Copy assignment


template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst& queue) {

    QueueLst<Data>* tmpQueue = new QueueLst<Data>(queue);
    std::swap(*tmpQueue, *this);

    delete tmpQueue;
    return *this;
}


// Move assignment

template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst&& queue) noexcept {

    std::swap(head, queue.head);
    std::swap(tail, queue.tail);
    std::swap(this->size, queue.size);

    return *this;
}


/* ************************************************************************** */

// Comparison operators

template<typename Data>
bool QueueLst<Data>::operator==(const QueueLst& queue) const noexcept {

    if (size != queue.Size()) {
        
        return false;

    } else {
        
        for (ulong i = 0; i < size; i++) {

            if ((*this)[i] != queue[i]) {

                return false;
            }
        }

        return true;
    }
}

template<typename Data>
bool QueueLst<Data>::operator!=(const QueueLst& queue) const noexcept {
    return !(*this == queue);
}


/* ************************************************************************** */

// Specific member functions (inherited from Stack)

template<typename Data>
const Data& QueueLst<Data>::Head() const {
    return List<Data>::Front();
}

template<typename Data>
Data& QueueLst<Data>::Head() {
    return List<Data>::Front();
}

template<typename Data>
void QueueLst<Data>::Dequeue() {
    List<Data>::RemoveFromFront();
}

template<typename Data>
Data QueueLst<Data>::HeadNDequeue() {
    return List<Data>::FrontNRemove();
}

template<typename Data>
void QueueLst<Data>::Enqueue(const Data& value) {
    List<Data>::InsertAtBack(value);
}

template<typename Data>
void QueueLst<Data>::Enqueue(Data&& value) {
    List<Data>::InsertAtBack(std::move(value));
}

template<typename Data>
void QueueLst<Data>::Clear() {
    List<Data>::Clear();
}


/* ************************************************************************** */



}
