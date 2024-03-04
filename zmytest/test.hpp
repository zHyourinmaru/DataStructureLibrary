
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/binarytree.hpp"
#include "../bst/bst.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

using namespace lasd;

/* ************************************************************************** */

template<typename Data> 
void generateHashTable(HashTable<Data>&);

template<> 
void generateHashTable(HashTable<int>&);

template<> 
void generateHashTable(HashTable<double>&);

template<> 
void generateHashTable(HashTable<std::string>&);

template<typename Data>
void menuHashTable(HashTable<Data>&);

template<typename Data>
void supportVisualize(HashTable<Data>&);
template<typename Data>
void printAllStructureValues(Data&, const void*);

template<typename Data>
void specificFoldFunction(HashTable<int>&);
template<typename Data>
void specificFoldFunction(HashTable<double>&);
template<typename Data>
void specificFoldFunction(HashTable<std::string>&);

void supportSpecificFoldInt(const int&, const void*, void*);
void supportSpecificFoldDouble(const double&, const void*, void*);
void supportSpecificFoldString(const std::string&, const void*, void*);

template<typename Data>
void HashTableInsertCopy(HashTable<Data>&);
template<typename Data>
void HashTableInsertMove(HashTable<Data>&);
template<typename Data>
void HashTableRemove(HashTable<Data>&);
template<typename Data>
void HashTableResize(HashTable<Data>&);

template<typename Data>
void existElement(HashTable<Data>&);

void myTestMainMenu();
void dataChoose();

/* ************************************************************************** */


#endif
