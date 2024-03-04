
namespace lasd {

/* ************************************************************************** */

// Default constructor

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() : HashTable<Data>() {

    vector = Vector<BST<Data>>(tableSize);

}


/* ************************************************************************** */

// Specific constructor

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(ulong value) : HashTable<Data>() {
    
    if (value != 0) {

        tableSize = HashTable<Data>::RoundTableSize(value);

    }
    
    vector = Vector<BST<Data>>(tableSize);

}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(LinearContainer<Data>& structure) : HashTable<Data>() {

    vector = Vector<BST<Data>>(tableSize);
    
    DictionaryContainer<Data>::Insert(structure);

}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(ulong value, LinearContainer<Data>& structure) : HashTable<Data>() {

    if (value != 0) {

        tableSize = HashTable<Data>::RoundTableSize(value);

    }
    
    vector = Vector<BST<Data>>(tableSize);
    
    DictionaryContainer<Data>::Insert(structure);

}


/* ************************************************************************** */

// Copy constructor

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr& structure) : HashTable<Data>(structure) {

    vector = structure.vector;

}

// Move constructor

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& structure) noexcept : HashTable<Data>(std::move(structure)) {

    std::swap(vector, structure.vector);

}

/* ************************************************************************** */

// Copy Assignment

template<typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& structure) {

    a = structure.a;
    b = structure.b;
    tableSize = structure.tableSize;
    size = structure.size;

    vector = structure.vector;

    return *this;

}

// Move Assignment

template<typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& structure) noexcept {

    std::swap(a, structure.a);
    std::swap(b, structure.b);
    std::swap(tableSize, structure.tableSize);
    std::swap(size, structure.size);

    std::swap(vector, structure.vector);

    return *this;

}


/* ************************************************************************** */

// Comparison operators

template <typename Data>
void SupportComparisonCls(const Data& value, const void* parameter, void* exists) noexcept {

    if (!(*(HashTableClsAdr<Data>*)parameter).Exists(value))
        *((bool*) exists) = false;


}

template<typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& structure) const noexcept {

    if (size == structure.size) {

        bool exists = true;

        Fold(&SupportComparisonCls<Data>, &structure, &exists);

        if (exists)
            return true;
        
    }

    return false;
 
}

template<typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& structure) const noexcept {

    return !(*this == structure);

}


/* ************************************************************************** */

// Specific member functions (inherited from HashTable)

template <typename Data>
void SupportResizeCls(Data& value, void* parameter) {

    (*(HashTableClsAdr<Data>*)parameter).Insert(value);

}

template<typename Data>
void HashTableClsAdr<Data>::Resize(const ulong value) {

    if (value == 0) {

        Clear();

    } else if (tableSize != value) {

        HashTableClsAdr<Data> temp = HashTableClsAdr(HashTable<Data>::RoundTableSize(value));

        Map(SupportResizeCls<Data>, &temp);

        std::swap(*this, temp);

    }

}


/* ************************************************************************ */

// Specific member functions (inherited from DictionaryContainer)

template<typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& value) {

    ulong index = HashKey(value);

    if ((vector[index]).Insert(value)) {

        size++;
        return true;

    }

    return false;

}

template<typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& value) {

    ulong index = HashKey(value);

    if ((vector[index]).Insert(std::move(value))) {

        size++;
        return true;

    }
  
    return false;

}

template<typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& value) {

    ulong index = HashKey(value);
    

    if ((vector[index]).Remove(value)){

        size--;
        return true;

    }
        

    return false;

}


/* ************************************************************************ */

// Specific member functions (inherited from TestableContainer)

template<typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& value) const noexcept {

    ulong index = HashKey(value);
    
    if ((vector[index]).Exists(value)) {

        return true;

    }

    return false;

}


/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)

template<typename Data>
void HashTableClsAdr<Data>::Map(MapFunctor function, void* parameter) {

    for (ulong i = 0; i < tableSize; i++) {

        (vector[i]).Map(function, parameter);

    }

}


/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)

template<typename Data>
void HashTableClsAdr<Data>::Fold(FoldFunctor function, const void* parameter, void* accumulator) const {

    for (ulong i = 0; i < tableSize; i++) {

        (vector[i]).Fold(function, parameter, accumulator);

    }

}


/* ************************************************************************ */

// Specific member functions (inherited from Container)

template<typename Data>
void HashTableClsAdr<Data>::Clear() {

    size = 0;

    vector.Clear();

    vector.Resize(128);
    
    tableSize = 128;

}


}
