
namespace lasd {

/* ************************************************************************** */

// Specific constructors (Node)

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data& value, ulong newIndex, Vector<NodeVec*>* newVector) {
    
    element = value;

    index = newIndex;
    nodeVector = newVector;

}


/* ************************************************************************ */

// Specific member functions (Node)

template <typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    
    return element;

}


template <typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    
    return element;

}


template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    
    return ((index * 2 + 1) < nodeVector->Size());

}


template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
   
   return ((index * 2 + 2) < nodeVector->Size());

}


template <typename Data>
struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    
    if(!HasLeftChild())
        throw std::out_of_range("The Left Child does not exists.");

    return *(nodeVector->operator[](index * 2 + 1));
}


template <typename Data>
struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    
    if(!HasRightChild())
        throw std::out_of_range("The Right Child does not exists.");

    return *(nodeVector->operator[](index * 2 + 2));

}


/* ************************************************************************** */

// Specific constructors (BinaryTreeVec)

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& structure) {
    
    size = structure.Size();
    btVector = new Vector<NodeVec*>(size);

    for (ulong i = 0; i < size; i++) {

        NodeVec* node = new NodeVec(structure[i], i, btVector);
        
        //btVector->operator[](i) = node;

        (*btVector)[i] = node;

    }

}


/* ************************************************************************ */

// Copy constructor (BinaryTreeVec)

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& binaryTree) {
    
    size = binaryTree.size;
    btVector = new Vector<NodeVec*>(size);

    for (ulong i = 0; i < size; i++) {

        NodeVec* tmpNode = new NodeVec(binaryTree.btVector->operator[](i)->Element(), i, btVector);
        
        //btVector->operator[](i) = tmpNode;
        (*btVector)[i] = tmpNode;

    }

}

// Move constructor (BinaryTreeVec)

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& binaryTree) noexcept {
    
    btVector = new Vector<NodeVec*>();

    std::swap(size, binaryTree.size);
    std::swap(btVector, binaryTree.btVector);

}


/* ************************************************************************ */

// Destructor (BinaryTreeVec)

template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
    
    delete btVector;

}

/* ************************************************************************ */

// Copy assignment (BinaryTreeVec)

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& binaryTree) {
    
    BinaryTreeVec<Data>* tmpBinaryTree = new BinaryTreeVec<Data>(binaryTree);
	std::swap(*this, *tmpBinaryTree);

	delete tmpBinaryTree;

    return *this;

}

// Move assignment (BinaryTreeVec)

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& binaryTree) noexcept {
    
    std::swap(size, binaryTree.size);
    std::swap(btVector, binaryTree.btVector);

    return *this;

}


/* ************************************************************************ */

// Comparison operators (BinaryTreeVec)

template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& binaryTree) const noexcept {
   
   return (BinaryTree<Data>::operator==(binaryTree));

}

template <typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& binaryTree) const noexcept{
    
    return !(*this == binaryTree);

}

/* ************************************************************************ */

// Specific member functions (inherited from BinaryTree) (BinaryTreeVec)

template <typename Data>
struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    
    if (size == 0)
        throw std::length_error("The Binary Tree is empty.");

    return *(btVector->operator[](0));

}


/* ************************************************************************ */

// Specific member functions (inherited from Container) (BinaryTreeVec)
template <typename Data>
void BinaryTreeVec<Data>::Clear() {
    
    btVector->Clear();

    size = 0;

}


/* ************************************************************************ */

// Specific member functions (inherited from BreadthMappableContainer)

template <typename Data>
void BinaryTreeVec<Data>::MapBreadth(MapFunctor function, void* parameter) {
    
    for (ulong i = 0; i < size; i++) {

        function(btVector->operator[](i)->Element(), parameter);

    }
}


template <typename Data>
void BinaryTreeVec<Data>::FoldBreadth(const FoldFunctor function, const void* parameter, void* accumulator) const {
    
    for (ulong i = 0; i < size; i++) {

        function(btVector->operator[](i)->Element(), parameter, accumulator);

    }
}


}
