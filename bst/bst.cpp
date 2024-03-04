
namespace lasd {

/* ************************************************************************** */

// Specific Constructors

template<typename Data>
BST<Data>::BST(const LinearContainer<Data>& structure) {
    
    for (ulong i = 0; i < structure.Size(); i++) {
        Insert(structure[i]);
    }

}   

/* ************************************************************************** */

// Copy Assignment

template<typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& binaryST) {

    BinaryTreeLnk<Data>::operator=(binaryST);
    return *this;

}

// Move Assignment

template<typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& binaryST) noexcept {

    BinaryTreeLnk<Data>::operator=(std::move(binaryST));
    return *this;
    
}


/* ************************************************************************** */

// Comparison operators

template<typename Data>
bool BST<Data>::operator==(const BST<Data>& binaryST) const noexcept {
    
    if (size == binaryST.Size()) {

        BTInOrderIterator<Data> thisIterator(*this);
        BTInOrderIterator<Data> otherIterator(binaryST);

        for (; !thisIterator.Terminated(); ++thisIterator, ++otherIterator) {

            if(*thisIterator != *otherIterator) {

                return false;
            
            }

        }
        
        return true;

    } else {

        return false;

    }
}


template<typename Data>
bool BST<Data>::operator!=(const BST<Data>& binaryST) const noexcept {

    return !(*this == binaryST);

}


/* ************************************************************************** */

// Specific member functions

template<typename Data>
const Data& BST<Data>::Min() const {

    if (size == 0)
        throw std::length_error("The BST is empty.");

    return (FindPointerToMin(root))->element;

}

template<typename Data>
Data BST<Data>::MinNRemove() {

    if (size == 0)
        throw std::length_error("The BST is empty.");

    NodeLnk* node = DetachMin(root);
    Data value = DataNDelete(node);

    return value;

}

template<typename Data>
void BST<Data>::RemoveMin() {

    if (size == 0)
        throw std::length_error("The BST is empty.");


    NodeLnk* node = DetachMin(root);
    delete node;

}


template<typename Data>
const Data& BST<Data>::Max() const {

    if (size == 0)
        throw std::length_error("The BST is empty.");

    return (FindPointerToMax(root))->element;

}

template<typename Data>
Data BST<Data>::MaxNRemove() {

    if (size == 0)
        throw std::length_error("The BST is empty.");

    
    NodeLnk* node = DetachMax(root);
    Data value = DataNDelete(node);

    return value;

}

template<typename Data>
void BST<Data>::RemoveMax() {

    if (size == 0)
        throw std::length_error("The BST is empty.");

    
    NodeLnk* node = DetachMax(root);
    delete node;
    
}


template<typename Data>
const Data& BST<Data>::Predecessor(const Data& value) const {

    if (size == 0)
        throw std::length_error("The BST is empty.");

    NodeLnk* const* node = (FindPointerToPredecessor(root, value));

    if (node != nullptr)
        return (*node)->element;
    else
        throw std::length_error("The predecessor does not exist.");

}

template<typename Data>
Data BST<Data>::PredecessorNRemove(const Data& value) {

    if (size == 0)
        throw std::length_error("The BST is empty.");

    
    NodeLnk** node = FindPointerToPredecessor(root, value);

    if (node == nullptr)
        throw std::length_error("The predecessor does not exist.");
 
    return DataNDelete(Detach(*node));

}

template<typename Data>
void BST<Data>::RemovePredecessor(const Data& value) {

    if (size == 0)
        throw std::length_error("The BST is empty.");

    NodeLnk** node = FindPointerToPredecessor(root, value);
    
    if (node == nullptr)
        throw std::length_error("The predecessor does not exist.");

    delete Detach(*node);

}

template<typename Data>
const Data& BST<Data>::Successor(const Data& value) const {

    if (size == 0)
        throw std::length_error("The BST is empty.");


    NodeLnk* const* node = (FindPointerToSuccessor(root, value));

    if (node != nullptr)
        return (*node)->element;
    else
        throw std::length_error("The successor does not exist.");

}

template<typename Data>
Data BST<Data>::SuccessorNRemove(const Data& value) {

    if (size == 0)
        throw std::length_error("The BST is empty.");


    NodeLnk** node = FindPointerToSuccessor(root, value);

    if (node == nullptr)
        throw std::length_error("The successor does not exist.");
 
    return DataNDelete(Detach(*node));

}

template<typename Data>
void BST<Data>::RemoveSuccessor(const Data& value) {

    if (size == 0)
        throw std::length_error("The BST is empty.");

    NodeLnk** node = FindPointerToSuccessor(root, value);
    
    if (node == nullptr)
        throw std::length_error("The successor does not exist.");

    delete Detach(*node);
    
}


/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

template<typename Data>
bool BST<Data>::Insert(const Data& value) {

    NodeLnk** current = &root;
    NodeLnk* node = new NodeLnk(value);

    while ((*current) != nullptr) {

        if ((*current)->element < value) {

            current = &((*current)->rightChild);

        } else if ((*current)->element > value) {

            current = &((*current)->leftChild);

        } else {

            delete node;
            return false;

        }

    }

    *current = node;
    size++;

    return true;

}

template<typename Data>
bool BST<Data>::Insert(Data&& value) {

    NodeLnk** current = &root;
    NodeLnk* node = new NodeLnk(std::move(value));

    while ((*current) != nullptr) {

        if ((*current)->element < node->element) {

            current = &((*current)->rightChild);

        } else if ((*current)->element > node->element) {

            current = &((*current)->leftChild);

        } else {

            delete node;
            return false;

        }

    }

    *current = node;
    size++;

    return true;

}

template<typename Data>
bool BST<Data>::Remove(const Data& value) {

    if (size != 0) {
  
        NodeLnk* node = Detach(FindPointerTo(root, value));

        if (node != nullptr) {

            delete node;
            return true;

        }
        
    }

    return false;
    
}


/* ************************************************************************** */

// Specific member functions (inherited from TestableContainer)

template<typename Data>
bool BST<Data>::Exists(const Data& value) const noexcept {

    if (size != 0) {

        NodeLnk* node = FindPointerTo(root, value);

        if (node == nullptr)
            return false;
        else
            return true;
    }

    return false;

}


/* ************************************************************************** */

// Auxiliary member functions


template<typename Data>
Data BST<Data>::DataNDelete(NodeLnk* node) {

    Data value = node->element;

    delete node;

    return value;

}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) noexcept {

    NodeLnk* node2Detach = nullptr;

    if (node != nullptr) {

        if (node->rightChild != nullptr && node->leftChild != nullptr) {
        
                node2Detach = DetachMin(node->rightChild);
                std::swap(node->element, node2Detach->element);

            } else {

                if (node->rightChild != nullptr) {

                    node2Detach = Skip2Right(node);

                } else if (node->leftChild != nullptr) {

                    node2Detach = Skip2Left(node);

                } else {

                    std::swap(node2Detach, node);
                    size--;

                }
            }

    }

    return node2Detach;

}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& node) noexcept {

    NodeLnk* minNode = nullptr;

    minNode = Skip2Right(FindPointerToMin(node));
    
    return minNode;

}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& node) noexcept {

    NodeLnk* maxNode = nullptr;

    maxNode = Skip2Left(FindPointerToMax(node));

    return maxNode;

}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk*& node) noexcept {

    NodeLnk* node2Skip = nullptr;

    if (node != nullptr) {

        // if (node == root)
        //     root = node->leftChild;

        std::swap(node2Skip, node->leftChild);
        std::swap(node2Skip, node);

        size--;

    }

    return node2Skip;

}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk*& node) noexcept {

    NodeLnk* node2Skip = nullptr;

    if (node != nullptr) {

        // if (node == root)
        //     root = node->rightChild;

        std::swap(node2Skip, node->rightChild);
        std::swap(node2Skip, node);

        size--;

    }

    return node2Skip;

}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& node) noexcept {

    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(node));

}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& node) const noexcept {

    NodeLnk* const* nodePtr = &node;
    NodeLnk* current = node;

    if (current != nullptr) {

        while (current->leftChild != nullptr) {

            nodePtr = &current->leftChild;
            current = current->leftChild;

        }

    }

    return *nodePtr;

}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& node) noexcept {

    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(node));

}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& node) const noexcept {

    NodeLnk* const* nodePtr = &node;
    NodeLnk* current = node;

    if (current != nullptr) {

        while (current->rightChild != nullptr) {

            nodePtr = &current->rightChild;
            current = current->rightChild;

        }

    }

    return *nodePtr;

}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& node, const Data& value) noexcept {

    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(node, value));

}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& node, const Data& value) const noexcept {

    NodeLnk* const* nodePtr = &node;
    NodeLnk* current = node;

    bool cicle = true;

    while (current != nullptr && cicle == true) {

        if (current->element < value) {

            nodePtr = &current->rightChild;
            current = current->rightChild;

        } else if (current->element > value) {

            nodePtr = &current->leftChild;
            current = current->leftChild;

        } else {

            cicle = false;

        }

    }

    return *nodePtr;

}

template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(NodeLnk*& node, const Data& value) noexcept {

    return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(node, value));

}

template<typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToPredecessor(NodeLnk* const& node, const Data& value) const noexcept {

    NodeLnk* const* nodePtr = &node;
    NodeLnk* const* predecessor = nullptr;

    do {

        NodeLnk& current = **nodePtr;

        if (current.element < value) {

            predecessor = nodePtr;

            if (current.rightChild != nullptr) {

                nodePtr = &current.rightChild;

            } else {

                return predecessor;

            }

        } else {

            if (current.leftChild != nullptr) {

                if (current.element > value) {

                    nodePtr = &current.leftChild;

                } else {

                    return &FindPointerToMax(current.leftChild);

                }

            } else {

                return predecessor;

            }

        }

    } while(true);

}

template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(NodeLnk*& node, const Data& value) noexcept {

    return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(node, value));

}

template<typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToSuccessor(NodeLnk* const& node, const Data& value) const noexcept {

    NodeLnk* const* nodePtr = &node;
    NodeLnk* const* successor = nullptr;

    do {

        NodeLnk& current = **nodePtr;
        
        if (current.element > value) {

            successor = nodePtr;

            if (current.leftChild != nullptr) {

                nodePtr = &current.leftChild;

            }   else {

                return successor;

            }

        } else {

            if (current.rightChild != nullptr) {

                if (current.element > value) {

                    return &FindPointerToMin(current.rightChild);

                } else {

                    nodePtr = &current.rightChild;                    

                }

            } else {

                return successor;

            }
        }

    } while (true);

}



}
