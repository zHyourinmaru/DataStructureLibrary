#include <iostream>


namespace lasd {

/* ************************************************************************** */

// Specific constructors

template<typename Data>
Vector<Data>::Vector(const ulong newsize) {
   
    Array = new Data[newsize] {};
    size = newsize;
    
}

template<typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& structure) {
    
    size = structure.Size();
    Array = new Data[size];

    for (ulong i = 0; i < size; i++) {
        Array[i] = structure[i];
    }

}

/* ************************************************************************** */


// Copy Constructor

template<typename Data>
Vector<Data>::Vector(const Vector<Data>& structure) {

    Array = new Data[structure.size];

    std::copy(structure.Array, structure.Array + structure.size, Array); 
    size = structure.size;
}

// Move Constructor

template<typename Data>
Vector<Data>::Vector(Vector<Data>&& structure) noexcept {

    std::swap(Array, structure.Array);
    std::swap(size, structure.size);
}



/* ************************************************************************** */


// Destructor

template<typename Data>
Vector<Data>::~Vector() {

    delete[] Array;

}

/* ************************************************************************** */


// Copy Assignment

template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& structure) {

    Vector<Data>* tempVector = new Vector<Data>(structure);
    std::swap(*tempVector, *this);

    delete tempVector;
    return *this;
}

// Move Assignment

template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& structure) noexcept {

    std::swap(Array, structure.Array);
    std::swap(size, structure.size);
    return *this;
}



/* ************************************************************************** */


// Comparison Operators

template<typename Data>
bool Vector<Data>::operator==(const Vector<Data>& structure) const noexcept {
    
    if (size != structure.size) {

        return false;

    } else {

        for (ulong i = 0; i < size; i++) {
            
            if(Array[i] != structure.Array[i]) {

                return false;
            }
        }

        return true;
    }
}

template<typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& structure) const noexcept {

    return !(*this == structure);
}



/* ************************************************************************** */


// Specific Member Functions

template<typename Data>
void Vector<Data>::Resize(const ulong newsize) {

    if (newsize == 0) {
        
        Clear();

    } else if (size != newsize) {

        ulong limit;

        if (size < newsize) {
            limit = size;
        }  else {
            limit = newsize;   
        }

        Data* TempArray = new Data[newsize] {};
        
        for (ulong i = 0; i < limit; i++) {
            std::swap(Array[i], TempArray[i]);
        }

        std::swap(Array, TempArray);
        size = newsize;
        delete[] TempArray;
    }
}


/* ************************************************************************** */


// Specific Member Functions (inherited from Container)

template<typename Data>
void Vector<Data>::Clear() {

    delete[] Array;
    Array = nullptr;
    size = 0;
}


/* ************************************************************************** */


// Specific Member Functions (inherited from LinearContainer)

template<typename Data>
Data& Vector<Data>::Front() const {

    if (size != 0) {

        return Array[0];

    } else {

        throw std::length_error("Access to an empty Vector");

    }
}


template<typename Data>
Data& Vector<Data>::Back() const {
    
    if (size != 0) {

        return Array[size - 1];

    } else {

        throw std::length_error("Access to an empty Vector");

    }
}


template<typename Data>
Data& Vector<Data>::operator[](const ulong value) const {

    if (value < size) {

        return Array[value];

    } else {

        throw std::out_of_range("Access at index " + std::to_string(value) + std::to_string(size));

    }
}


/* ************************************************************************** */


// Specific Member Functions (inherited from MappableContainer)

template<typename Data>
inline void Vector<Data>::Map(MapFunctor function, void* parameter) {
    MapPreOrder(function, parameter);
}


/* ************************************************************************** */


// Specific Member Functions (inherited from PreOrderMappableContainer)

template<typename Data>
void Vector<Data>::MapPreOrder(MapFunctor function, void* parameter) {

    for (ulong i = 0; i < size; ++i) {
        
        function(Array[i], parameter);
    }
}


/* ************************************************************************** */


// Specific Member Functions (inherited from PostOrderMappableContainer)

template<typename Data>
void Vector<Data>::MapPostOrder(MapFunctor function, void* parameter) {

    long i = size - 1;

    while (i >= 0) {
        
        function(Array[i], parameter);
        i--;
    }
}


/* ************************************************************************** */


// Specific Member Functions (inherited from FoldableContainer)

template<typename Data>
inline void Vector<Data>::Fold(FoldFunctor function, const void* parameter, void* accumulator) const {
    FoldPreOrder(function, parameter, accumulator);
}


/* ************************************************************************** */


// Specific Member Functions (inherited from PreOrderFoldableContainer)

template<typename Data>
void Vector<Data>::FoldPreOrder(FoldFunctor function, const void* parameter, void* accumulator) const {
    
    for(ulong i = 0; i < size; ++i) {
        function(Array[i], parameter, accumulator);
    }
}


/* ************************************************************************** */


// Specific Member Functions (inherited from PostOrderFoldableContainer)

template<typename Data>
void Vector<Data>::FoldPostOrder(FoldFunctor function, const void* parameter, void* accumulator) const {
    
    long i = size - 1;

    while (i >= 0) {
        
        function(Array[i], parameter, accumulator);
        i--;
    }
}




}
