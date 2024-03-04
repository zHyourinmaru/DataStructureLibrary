
namespace lasd {

/* ************************************************************************** */

//  Hash

/* ************************************************************************** */

template<>
class Hash<int> {

public:

    ulong operator()(const int& value) const noexcept {

        return (value * value);

    }

};

template<>
class Hash<double> {

public:

    ulong operator()(const double& value) const noexcept {

        long partInt = floor(value);
        long partFrac = pow(2, 24) * (value - partInt);

        return (partInt * partFrac);

    }

};

template<>
class Hash<std::string> {

public:

    ulong operator()(const std::string& value) const noexcept {

        const int prime = 31;

        int hash = 0;

        for (int i = 0; i < value.length(); i++) {

            hash += value[i] * pow(prime, i);

        }

        return hash;

    }

};


/* ************************************************************************** */

// HashTable

/* ************************************************************************** */

// Default Constructor

template<typename Data>
HashTable<Data>::HashTable() {

    std::default_random_engine randomGen(std::random_device{}());
    std::uniform_int_distribution<unsigned long long> rangeA(0, prime-1);
    std::uniform_int_distribution<unsigned long long> rangeB(1, prime-1);

    a = rangeA(randomGen);

    if (a % 2 == 0) {
        a++;
    }

    b = rangeB(randomGen);

    size = 0;

}


/* ************************************************************************** */

// Copy Constructor

template<typename Data>
HashTable<Data>::HashTable(const HashTable& structure) {

    a = structure.a;
    b = structure.b;
    tableSize = structure.tableSize;
    size = structure.size;

}

// Move Constructor

template<typename Data>
HashTable<Data>::HashTable(HashTable&& structure) noexcept {

    std::swap(a, structure.a);
    std::swap(b, structure.b);
    std::swap(tableSize, structure.tableSize);
    std::swap(size, structure.size);

}


/* ************************************************************************** */

// Auxiliary member functions

template<typename Data>
ulong HashTable<Data>::HashKey(Data value) const {

    ulong returnValue = hashFunction.operator()(value);

    returnValue = (((a * returnValue) + b) % prime) % tableSize;

    return returnValue;

}

template<typename Data>
ulong HashTable<Data>::RoundTableSize(ulong value) {

    int power = 3;

    while (pow(2, power) < value) {
        power++;
    }

    return pow(2, power);

}

}
