
namespace lasd {

/* ************************************************************************ */

// Copy assignment


template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst& stack) {

    StackLst<Data>* tmpStack = new StackLst<Data>(stack);
    std::swap(*tmpStack, *this);

    delete tmpStack;
    return *this;
}


// Move assignment

template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst&& stack) noexcept {

    std::swap(head, stack.head);
    std::swap(this->size, stack.size);

    return *this;
}



/* ************************************************************************** */

// Comparison operators

template<typename Data>
bool StackLst<Data>::operator==(const StackLst& stack) const noexcept {

    if (size != stack.Size()) {
        
        return false;

    } else {
        
        for (ulong i = 0; i < size; i++) {

            if ((*this)[i] != stack[i]) {

                return false;
            }
        }

        return true;
    }
}

template<typename Data>
bool StackLst<Data>::operator!=(const StackLst& stack) const noexcept {
    return !(*this == stack);
}


/* ************************************************************************** */

// Specific member functions (inherited from Stack)

template<typename Data>
const Data& StackLst<Data>::Top() const {
    return List<Data>::Front();
}

template<typename Data>
Data& StackLst<Data>::Top() {
    return List<Data>::Front();
}

template<typename Data>
void StackLst<Data>::Pop() {
    List<Data>::RemoveFromFront();
}

template<typename Data>
Data StackLst<Data>::TopNPop() {
    return List<Data>::FrontNRemove();
}

template<typename Data>
void StackLst<Data>::Push(const Data& value) {
    List<Data>::InsertAtFront(value);
}

template<typename Data>
void StackLst<Data>::Push(Data&& value) {
    List<Data>::InsertAtFront(std::move(value));
}

template<typename Data>
void StackLst<Data>::Clear() {
    List<Data>::Clear();
}


/* ************************************************************************** */

}
