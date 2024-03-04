
namespace lasd {

/* ************************************************************************** */

//Comparison Operators (LinearContainer)

template <typename Data>
inline bool LinearContainer<Data>::operator==(const LinearContainer<Data>& structure) const noexcept {
    
    if (size != structure.size) {

        return false;
    
    } else {

           for (ulong i = 0; i < size; ++i) {

            if ((*this)[i] != structure[i]) {

                return false;
            }
        }

        return true;
    }
}

template <typename Data>
inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& structure) const noexcept {
    
    return !(*this == structure); 
}



/* ************************************************************************** */

//Specific Member Function (DictionaryContainer)

template <typename Data>
void DictionaryContainer<Data>::Insert(const LinearContainer<Data>& structure) {

    for (ulong i = 0; i < structure.Size(); i++) {

        Insert(structure[i]);

    }

}

template <typename Data>
void DictionaryContainer<Data>::Insert(LinearContainer<Data>&& structure) {

    for (ulong i = 0; i < structure.Size(); i++) {

        Insert(std::move(structure[i]));

    }

}

template <typename Data>
void DictionaryContainer<Data>::Remove(const LinearContainer<Data>& structure) {

    for (ulong i = 0; i < structure.Size(); i++) {

        Remove(structure[i]);

    }

}


/* ************************************************************************** */

// Specific member functions (LinearContainer)

template <typename Data>
inline Data& LinearContainer<Data>:: Front() const {

    if (size != 0) {
        
        return (*this)[0];

    } else {

        throw std::length_error("Access to an empty linear container.");
    }
}

template <typename Data>
inline Data& LinearContainer<Data>::Back() const {

    if (size != 0) {

        return (*this)[size - 1];

    } else {

        throw std::length_error("Access to an empty linear container");
    }
}

/* ************************************************************************** */

//Specific Member Function (FoldableContainer)

template <typename Data>
void SupportFoldExists(const Data& dat, const void* value, void* exists) noexcept {

    if (dat == *((Data*) value)) {

        *((bool*) exists) = true;
    }
}

template <typename Data>
inline bool FoldableContainer<Data>::Exists(const Data& value) const noexcept {
    
    bool exists = false;

    Fold(&SupportFoldExists<Data>, &value, &exists);

    return exists;
}

/* ************************************************************************** */

//Specific Member Function (PreOrderMappableContainer)

template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFunctor function, void* parameter) {
    MapPreOrder(function, parameter);
}

/* ************************************************************************** */

//Specific Member Function (PreOrderFoldableContainer)

template <typename Data>
inline void PreOrderFoldableContainer<Data>::Fold(FoldFunctor function, const void* parameter, void* accumulator) const {
    FoldPreOrder(function, parameter, accumulator);
}

/* ************************************************************************** */

//Specific Member Function (PostOrderMappableContainer)

template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFunctor function, void* parameter) {
    MapPostOrder(function, parameter);
}

/* ************************************************************************** */

//Specific Member Function (PostOrderFoldableContainer)

template <typename Data>
inline void PostOrderFoldableContainer<Data>::Fold(FoldFunctor function, const void* parameter, void* accumulator) const {
    FoldPostOrder(function, parameter, accumulator);
}

/* ************************************************************************** */

//Specific Member Function (InOrderMappableContainer)

template <typename Data>
inline void InOrderMappableContainer<Data>::Map(MapFunctor function, void* parameter) {
    MapInOrder(function, parameter);
}

/* ************************************************************************** */

//Specific Member Function (InOrderFoldableContainer)

template <typename Data>
inline void InOrderFoldableContainer<Data>::Fold(FoldFunctor function, const void* parameter, void* accumulator) const {
    FoldInOrder(function, parameter, accumulator);
}

/* ************************************************************************** */

//Specific Member Function (BreadthMappableContainer)

template <typename Data>
inline void BreadthMappableContainer<Data>::Map(MapFunctor function, void* parameter) {
    MapBreadth(function, parameter);
}

/* ************************************************************************** */

//Specific Member Function (BreadthFoldableContainer)

template <typename Data>
inline void BreadthFoldableContainer<Data>::Fold(FoldFunctor function, const void* parameter, void* accumulator) const {
    FoldBreadth(function, parameter, accumulator);
}


}

