
namespace lasd {

/* ************************************************************************** */

// Default constructor

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() : HashTable<Data>() {

    vector = Vector<Data>(tableSize);

    for (ulong i = 0; i < tableSize; i++) {
        flag.operator[](i) = 'e';
    }     

}


/* ************************************************************************** */

// Specific constructor

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(ulong value) : HashTable<Data>() {

    if (value != 0) {

        tableSize = HashTable<Data>::RoundTableSize(value);

        vector = Vector<Data>(tableSize);

        Vector<char> tempFlag = Vector<char>(tableSize);

        for (ulong i = 0; i < tableSize; i++) {
            tempFlag.operator[](i) = 'e';
        }

        std::swap(flag, tempFlag);

    } else {

        vector = Vector<Data>(tableSize);

        for (ulong i = 0; i < tableSize; i++) {
            flag.operator[](i) = 'e';
        }     

    }
    
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(LinearContainer<Data>& structure) : HashTable<Data>() {

    vector = Vector<Data>(tableSize);

    for (ulong i = 0; i < tableSize; i++) {
        flag.operator[](i) = 'e';
    }

    DictionaryContainer<Data>::Insert(structure);   

}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(ulong value, LinearContainer<Data>& structure) : HashTable<Data>() {

    this->Resize(value);

    DictionaryContainer<Data>::Insert(structure);

}


/* ************************************************************************** */

// Copy constructor

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr& structure) : HashTable<Data>(structure) {

    vector = structure.vector;
    flag = structure.flag;

}

// Move constructor

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr&& structure) noexcept : HashTable<Data>(std::move(structure)) {

    std::swap(vector, structure.vector);
    std::swap(flag, structure.flag);

}

/* ************************************************************************** */

// Copy Assignment

template<typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& structure) {

    a = structure.a;
    b = structure.b;
    tableSize = structure.tableSize;
    size = structure.size;

    vector = structure.vector;
    flag = structure.flag;

    return *this;

}

// Move Assignment

template<typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& structure) noexcept {

    std::swap(a, structure.a);
    std::swap(b, structure.b);
    std::swap(tableSize, structure.tableSize);
    std::swap(size, structure.size);

    std::swap(vector, structure.vector);
    std::swap(flag, structure.flag);

    return *this;

}


/* ************************************************************************** */

// Comparison operators

template <typename Data>
void SupportComparisonOpn(const Data& value, const void* parameter, void* exists) noexcept {

    if (!(*(HashTableOpnAdr<Data>*)parameter).Exists(value))
        *((bool*) exists) = false;

}

template<typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr& structure) const noexcept {

    if (size == structure.size) {

        bool exists = true;

        Fold(&SupportComparisonOpn<Data>, &structure, &exists);

        if (exists)
            return true;
        
    }

    return false;
 
}

template<typename Data>
bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr& structure) const noexcept {

    return !(*this == structure);

}


/* ************************************************************************** */

// Specific member functions (inherited from HashTable)

template <typename Data>
void SupportResizeOpn(Data& value, void* parameter) {

    (*(HashTableOpnAdr<Data>*)parameter).Insert(value);

}

template<typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong value) {

    if (value == 0) {

        Clear();

    } else if (tableSize != value) {    

        HashTableOpnAdr<Data> temp = HashTableOpnAdr<Data>(HashTable<Data>::RoundTableSize(value));
        
        Map(SupportResizeOpn<Data>, &temp);
        
        std::swap(*this, temp);

    }

}


/* ************************************************************************ */

// Specific member functions (inherited from DictionaryContainer)

template<typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& value) {

    Expand();

    ulong index = FindEmpty(value);

    if (flag.operator[](index) == 'f') {   
        return false;
    }
    
    flag.operator[](index) = 'f';
    vector[index] = value;
    size++;

    return true;

}

template<typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& value) {

    Expand();

    ulong index = FindEmpty(value);

    if (flag.operator[](index) == 'f') {   
        return false; 
    }

    flag.operator[](index) = 'f';
    vector[index] = std::move(value);
    size++;

    return true;

}

template<typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& value) {

    ulong index = Find(value, 0);

    if (index < tableSize) {
        flag.operator[](index) = 'd';
        size--;
        return true;
    }
    
    return false;

}


/* ************************************************************************ */

// Specific member functions (inherited from TestableContainer)

template<typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& value) const noexcept {

    ulong index = Find(value, 0);

    if (index < tableSize) {
        return true;
    }

    return false;

}


/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)

template<typename Data>
void HashTableOpnAdr<Data>::Map(MapFunctor function, void* parameter) {

    for (ulong i = 0; i < tableSize; i++) {
        
        if (flag.operator[](i) == 'f') {
            function(vector[i], parameter);
        }       

    }

}


/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)

template<typename Data>
void HashTableOpnAdr<Data>::Fold(FoldFunctor function, const void* parameter, void* accumulator) const {

    for (ulong i = 0; i < tableSize; ++i) {
        
        if (flag.operator[](i) == 'f') {
            function(vector[i], parameter, accumulator);
        }     
            
    }

}


/* ************************************************************************ */

// Specific member functions (inherited from Container)

template<typename Data>
void HashTableOpnAdr<Data>::Clear() {

    size = 0;
    tableSize = 128;
     
    Vector<char> tempFlag = Vector<char>(128);

    for (ulong i = 0; i < tableSize; i++) {
        tempFlag.operator[](i) = 'e';
    }

    std::swap(flag, tempFlag);

    vector.Clear();
    vector.Resize(128);

}


/* ************************************************************************** */

// Auxiliary member functions

template<typename Data>
ulong HashTableOpnAdr<Data>::HashKey(Data value, ulong index) const {

    return ((HashKey(value) + ((5 * index * index) + (7 * index) + 3)) % tableSize);
    
}

template<typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(Data value) const {

    ulong i = 0;
    ulong index = HashKey(value, i);

    while (flag.operator[](index) == 'f' && i < tableSize) {

        if (vector[index] == value) {
            return index;
        }

        i++;
        index = HashKey(value, i);
    }

    if (flag.operator[](index) == 'd') {
        
        ulong temp = Find(value, i);

        if (temp < tableSize) {
            index = temp;
        }
        
    }

    return index;

}

template<typename Data>
ulong HashTableOpnAdr<Data>::Find(Data value, ulong i) const {

    ulong index = HashKey(value, i);

    while (flag.operator[](index) != 'e' && i < tableSize) {

        if (vector[index] == value && flag.operator[](index) == 'f') {
            return index;
        }

        i++;
        index = HashKey(value, i);
    }

    if (flag.operator[](index) == 'f') {
        if (vector[index] == value) {
            return index;
        }
    } 

    return tableSize;

}

template<typename Data>
void HashTableOpnAdr<Data>::Expand() {

    if (size >= floor(tableSize/2)) {
        Resize(tableSize + 1);
    }

}

}
