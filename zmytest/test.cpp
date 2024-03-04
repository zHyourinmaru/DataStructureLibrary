
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>
#include "test.hpp"

ulong choice;
ulong structureSize;
ushort dataChoice = 0;
ushort structureChoice = 0;
ushort iteratorChoice = 0;


const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


// /* ************************************************************************ */

// // Starting Menu

// /* ************************************************************************ */


void myTestMainMenu() {

    while ( std::cout << std::endl << std::endl << "Choose which type of structure to test:" << std::endl << std::endl << 
        "\t[1] HashTable with Closed Addressing;" << std::endl << std::endl << "\t[2] HashTable with Open Addressing;" 
        << std::endl << std::endl << "\t[3] Exit." << std::endl 
        << std::endl && !(std::cin >> choice)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input." << std::endl << std::endl;
    }
        
    switch (choice) {
        case 1:
            dataChoose();
            break;
        case 2:
            dataChoose();
            break;
        case 3: {
            std::cout << std::endl << "Exiting the program..." << std::endl;
            _Exit(0);
            break;
        }
        default:
            std::cout << std::endl << std::endl << "Error: Invalid entered value. Return to the Menu..." << std::endl;
            myTestMainMenu();
            break;
    }
    
}

void dataChoose() {

    dataChoice = 0;
    
    while (dataChoice <= 0 || dataChoice > 4) {

        
        while (std::cout << std::endl << "Choose on which type of data to create the structure:" << std::endl << std::endl << 
            "\t[1] Integer;" << std::endl << std::endl << "\t[2] Double;" << std::endl << std::endl << "\t[3] String;" << std::endl 
            << std::endl << "\t[4] Back to the Main Menu." << std::endl << std::endl && !(std::cin >> dataChoice)) {

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Invalid input." << std::endl << std::endl;
        }

        if (dataChoice < 4 && dataChoice > 0) {
            
            while (std::cout << std::endl << "Enter the size of the structure:" << std::endl << std::endl 
                && !(std::cin >> structureSize)) {

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Invalid input." << std::endl << std::endl;
            }
        }
          
        switch (dataChoice) {
            case 1: {

                if (structureChoice == 1) {
                    HashTableClsAdr<int>* hashTable = new HashTableClsAdr<int>();
                    generateHashTable<int>(*hashTable);
                    menuHashTable(*hashTable); 
                } else {
                    HashTableOpnAdr<int>* hashTable = new HashTableOpnAdr<int>();
                    generateHashTable<int>(*hashTable);
                    menuHashTable(*hashTable); 
                }  
                break;
            }
            case 2: { 

                if (structureChoice == 1) {
                    HashTableClsAdr<double>* hashTable = new HashTableClsAdr<double>();
                    generateHashTable<double>(*hashTable);
                    menuHashTable(*hashTable);  
                } else {
                    HashTableOpnAdr<double>* hashTable = new HashTableOpnAdr<double>();
                    generateHashTable<double>(*hashTable);
                    menuHashTable(*hashTable);          
                }
                break;
            }
            case 3: {

                if (structureChoice == 1) {
                    HashTableClsAdr<std::string>* hashTable = new HashTableClsAdr<std::string>();
                    generateHashTable<std::string>(*hashTable);
                    menuHashTable(*hashTable);               
                } else {
                    HashTableOpnAdr<std::string>* hashTable = new HashTableOpnAdr<std::string>();
                    generateHashTable<std::string>(*hashTable);
                    menuHashTable(*hashTable);         
                }
                break;
            }
            case 4:
                myTestMainMenu();
                break;
            default:
                std::cout << std::endl << std::endl << "Error: Invalid entered value. Return to the Menu..." << std::endl;
                break;
        }
    }
}



/* ************************************************************************ */

// Generating Value

/* ************************************************************************ */

template<typename Data>
void generateHashTable(HashTable<Data>& hashTable) {};


template<>
void generateHashTable(HashTable<int>& hashTable) {

    std::default_random_engine randomGen(std::random_device{}());
    std::uniform_int_distribution<int> range(-1000, 1000);

    int structureValue;
    ulong i = structureSize;

    while (i > 0) {
        
        structureValue = range(randomGen);

        if (hashTable.Insert(structureValue))
            i--;

    }

    supportVisualize(hashTable);

}

template<>
void generateHashTable(HashTable<double>& hashTable) {

    std::default_random_engine randomGen(std::random_device{}());
    std::uniform_real_distribution<double> range(-100, 100);

    double structureValue;
    ulong i = structureSize;

    while (i > 0) {
        
        structureValue = range(randomGen);

        if (hashTable.Insert(structureValue))
            i--;

    }
    
    supportVisualize(hashTable);
}

template<>
void generateHashTable(HashTable<std::string>& hashTable) {

    std::default_random_engine randomGen(std::random_device{}());
    std::uniform_int_distribution<> range(0, characters.size() - 1);

    std::string structureValue;

    std::default_random_engine randomGenLenght(std::random_device{}());
    std::uniform_int_distribution<int> rangeLenght(1, 50);

    int lenght;
    ulong i = structureSize;

    while (i > 0) {
        
        structureValue = "";

        lenght = rangeLenght(randomGenLenght);

        for (int i = 0; i < lenght; i++) {
            structureValue += characters[range(randomGen)];
        }
        
        if (hashTable.Insert(structureValue))
            i--;

    }

    supportVisualize(hashTable);
  
}



/* ************************************************************************ */

// HashTable Menu

/* ************************************************************************ */


template<typename Data>
void menuHashTable(HashTable<Data>& hashTable) {
    
    while (
            std::cout << std::endl << std::endl << "Choose the function:" << std::endl << std::endl << 
            "\t[1] Visualize the HashTable" << std::endl << std::endl << "\t[2] Insert a value (Copy of the value);"
            << std::endl << std::endl << "\t[3] Insert a value (move of the value);" << std::endl << std::endl << 
            "\t[4] Remove a value;" << std::endl << std::endl << "\t[5] Specific Fold Function for the type;"
            << std::endl << std::endl << "\t[6] Check the existence of a value;" << std::endl << std::endl << 
            "\t[7] Resize the HashTable;" << std::endl << std::endl << "\t[8] Clear of the HashTable;" 
            << std::endl << std::endl << "\t[9] Generate other Values;" << std::endl << std::endl <<  "\t[10] Back to the Main Menu."
            << std::endl << std::endl
            && !(std::cin >> choice)
            ) {

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Invalid input." << std::endl << std::endl;
        }
    
    switch (choice) {
        case 1: {
            supportVisualize(hashTable);
            break;
        }
        case 2: {
            HashTableInsertCopy(hashTable);
            break;
        }
        case 3: {
            HashTableInsertMove(hashTable);
            break;
        }
        case 4: {
            HashTableRemove(hashTable);
            break;
        }
        case 5: {
            specificFoldFunction<Data>(hashTable);
            break;
        }
        case 6: {
            existElement(hashTable);
            break;
        }
        case 7: {
            HashTableResize(hashTable);
            break;
        }
        case 8: {
            std::cout << std::endl << "Executing the clear of the HashTable..." << std::endl;           
            hashTable.Clear();
            structureSize = 0;
            std::cout << std::endl << "Clear of the HashTable completed." << std::endl;
            
            break;
        }
        case 9: {
            hashTable.Clear();
            generateHashTable<Data>(hashTable);
            break;
        }
        case 10: {
            delete &hashTable;
            myTestMainMenu();
            break;
        }
        default:{
            std::cout << std::endl << std::endl << "Error: Invalid entered value." << std::endl;
            break;
        }
    }   

    menuHashTable(hashTable);

}


/* ************************************************************************ */

// Support Functions for the HashTable

/* ************************************************************************ */


template<typename Data>
void supportVisualize(HashTable<Data>& hashTable) {

    std::cout << std::endl << "The size of the HashTable is:\t" << hashTable.Size() << std::endl;

    std::cout << std::endl << "The values of the HashTable are:\t" << std::endl;
    hashTable.Map(printAllStructureValues<Data>, nullptr);

}

template<typename Data>
void printAllStructureValues(Data& value, const void* parameter) {

    std::cout << std::endl << std::setprecision(20) << "There is the value:\t" << value;

}

template<typename Data>
void specificFoldFunction(HashTable<int>& hashTable) {
    
    int result = 1;

    int choice;

    std::cout << std::endl << "Calculating the product for integers less than an n:\t";

    while (std::cout << std::endl << "Enter the n value:\t" && !(std::cin >> choice)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input." << std::endl << std::endl;
    }

    std::cout << std::endl << "The result:\t";
    
    hashTable.Fold(supportSpecificFoldInt, &choice, &result);

    std::cout << result << std::endl;
}

template<typename Data>
void specificFoldFunction(HashTable<double>& hashTable) {
    
    double result = 0;

    double choice;

    std::cout << std::endl << "Calculating the sum for doubles greather than an n:\t";

    while (std::cout << std::endl << "Enter the n value:\t" && !(std::cin >> choice)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input." << std::endl << std::endl;
    }

    std::cout << std::endl << "The result:\t";
    
    hashTable.Fold(supportSpecificFoldDouble, &choice, &result);

    std::cout << result << std::endl;

}

template<typename Data>
void specificFoldFunction(HashTable<std::string>& hashTable) {
    
    std::string result = "";

    std::string choice;

    std::cout << std::endl << "The Concatenation for strings with lenght less than or equal to n is:\t";

    while (std::cout << std::endl << "Enter the n value:\t" && !(std::cin >> choice)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input." << std::endl << std::endl;
    }

    std::cout << std::endl << "The result:\t";
    
    hashTable.Fold(supportSpecificFoldString, &choice, &result);

    std::cout << result << std::endl;
}


void supportSpecificFoldInt(const int& value, const void* parameter, void* accumulator) {

    if (value < *((int*)(parameter))) {

        *((int*)(accumulator)) = *((int*)(accumulator)) * value;

    }

}

void supportSpecificFoldDouble(const double& value, const void* parameter, void* accumulator) {

    if (value > *((double*)(parameter))) {

        *((double*)(accumulator)) = *((double*)(accumulator)) + value;

    }

}

void supportSpecificFoldString(const std::string& value, const void* parameter, void* accumulator) {

    if (value.length() <= *((ulong*)(parameter))) {

        *((std::string*)(accumulator)) = *((std::string*)(accumulator)) + value;

    }

}

template<typename Data>
void HashTableInsertCopy(HashTable<Data>& hashTable) {

    Data choiceInsert;

    while (std::cout << std::endl << "Enter the value to be inserted:\t" && !(std::cin >> choiceInsert)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input." << std::endl << std::endl;
    }

    if (hashTable.Insert(choiceInsert)) {
        std::cout << "The value is inserted correctly.";
        structureSize++;
    } else {
        std::cout << "The value already exist.";
    }

}

template<typename Data>
void HashTableInsertMove(HashTable<Data>& hashTable) {

    Data choiceInsert;

    while (std::cout << std::endl << "Enter the value to be inserted:\t" && !(std::cin >> choiceInsert)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input." << std::endl << std::endl;
    }

    if (hashTable.Insert(std::move(choiceInsert))) {
        std::cout << "The value is inserted correctly.";
        structureSize++;
    } else {
        std::cout << "The value already exist.";
    }
}

template<typename Data>
void HashTableRemove(HashTable<Data>& hashTable) {

    Data choiceInsert;

    while (std::cout << std::endl << "Enter the value to be removed:\t" && !(std::cin >> choiceInsert)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input." << std::endl << std::endl;
    }

    if (hashTable.Remove(choiceInsert)) {
        std::cout << "The value is removed correctly.";
        structureSize--;
    } else {
        std::cout << "The value doesn't exist.";
    }

}

template<typename Data>
void HashTableResize(HashTable<Data>& hashTable) {

    ulong choiceInsert;

    while (std::cout << std::endl << "Enter the new size of the HashTable:\t" && !(std::cin >> choiceInsert)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input." << std::endl << std::endl;
    }

    hashTable.Resize(choiceInsert);

}

template<typename Data>
void existElement(HashTable<Data>& hashTable) {

    Data choiceExist;

    while (std::cout << std::endl << "Enter the value on which perform the existence check:\t"
        && !(std::cin >> choiceExist)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input." << std::endl << std::endl;
    }

    if (hashTable.Exists(choiceExist)) {
        std::cout << std::endl << std::endl << "The value " << choiceExist << " exists.";
    } else {
        std::cout << std::endl << std::endl << "The value " << choiceExist << " does not exists.";
    }

}



