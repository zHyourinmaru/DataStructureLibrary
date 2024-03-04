
namespace lasd {

/* ************************************************************************** */

// Move constructor

template<typename Data>
StackVec<Data>::StackVec(StackVec&& structure) noexcept : Vector<Data>(std::move(structure)) {
    
    std::swap(first, structure.first);
}

/* ************************************************************************** */

// Copy assignment

template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& structure) {
    Vector<Data>::operator=(structure);
    first = structure.first;
    return *this;
}

// Move assignment

template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& structure) noexcept {
    Vector<Data>::operator=(std::move(structure));
    std::swap(first, structure.first);
    return *this;
}


/* ************************************************************************** */

// Comparison operators

template<typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& structure) const noexcept {
    
    if (first == structure.first) {
        
        for (ulong i = 0; i < first; i++) {
            
            if (Array[i] != structure.Array[i]) {
                
                return false;
            }
        }
        
        return true;

    } else {

        return false;
    }
} 


template<typename Data>
inline bool StackVec<Data>::operator!=(const StackVec<Data>& structure) const noexcept {
    return !(*this == structure);
}


/* ************************************************************************** */

// Specific member functions (inherited from Stack)

template<typename Data>
const Data& StackVec<Data>::Top() const {
    
    if (first != 0) {
        return (*this)[first-1];
    } else {
        throw std::length_error("Access to an empty Stack");
    }
}

template<typename Data>
Data& StackVec<Data>::Top() {

    if (first != 0) {
        return (*this)[first-1];
    } else {
        throw std::length_error("Access to an empty Stack");
    }
}

template<typename Data>
void StackVec<Data>::Pop() {

    if (first != 0) {
        
        first--;

        Reduce();

    } else {
        throw std::length_error("Access to an empty Stack");
    }
}

template<typename Data>
Data StackVec<Data>::TopNPop() {
    
    if (first != 0) {

        Data value = (*this)[first - 1];

        first--;

        Reduce();

        return value;

    } else {
        throw std::length_error("Access to an empty Stack");
    }
}

template<typename Data>
void StackVec<Data>::Push(const Data& value) {
    
    Expand();
    (*this)[first] = value;
    first++;
}

template<typename Data>
void StackVec<Data>::Push(Data&& value) {
    
    Expand();
    (*this)[first] = std::move(value);
    first++;
}


/* ************************************************************************** */

// Specific member functions (inherited from Container)

template<typename Data>
inline bool StackVec<Data>::Empty() const noexcept {

    if(first != 0) {
        return false;
    } else {
        return true;
    }
}

template<typename Data>
inline ulong StackVec<Data>::Size() const noexcept {
    return (first);
}

template<typename Data>
void StackVec<Data>::Clear() {
    
    Vector<Data>::Clear();
    first = 0;
    Vector<Data>::Resize(1);
}


/* ************************************************************************** */

// Auxiliary member functions

template<typename Data>
void StackVec<Data>::Expand() {

    if(first == (size - 1)) {
        Vector<Data>::Resize((this->size)*2);
    }
    
}

template<typename Data>
void StackVec<Data>::Reduce() {

    if(first <= (size / 4)) {
        Vector<Data>::Resize((this->size)/2);
    }
    
}

}
