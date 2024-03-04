
// #include "..."

namespace lasd {

/* ************************************************************************** */

// Comparison operators (Node)

template<typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept {
    
    if (this->Element() == node.Element()) {

        if ((this->HasLeftChild() == node.HasLeftChild()) && (this->HasRightChild() == node.HasRightChild())) {
           
            if (this->HasLeftChild() && this->HasRightChild()) {
            
                return ((this->LeftChild() == node.LeftChild()) && (this->RightChild() == node.RightChild()));
            
            } else if (this->HasLeftChild()) {
                
                return (this->LeftChild() == node.LeftChild());
            
            } else if (this->HasRightChild()) {

                return (this->RightChild() == node.RightChild());
            
            } else {

                return true;

            } 
        }
    }

    return false;

}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept {
    
    return !(*this == node);

}

/* ********************************************************************** */

// Specific member functions

template <typename Data>
bool BinaryTree<Data>::Node::IsLeaf() const noexcept {
    
    return (!HasLeftChild() && !HasRightChild());

}


/* ************************************************************************** */

// Comparison operators (Binary Tree)

template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& binaryTree) const noexcept {
    
    if (size == binaryTree.size) {

        if (size != 0)
            return Root() == binaryTree.Root();
        else
            return true;

    } else {
        
        return false;

    }

}

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& binaryTree) const noexcept {
    
    return !(*this == binaryTree);

}


/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void BinaryTree<Data>::Map(MapFunctor function, void* parameter) {
    
    if (size > 0)
        MapPreOrder(function, parameter);

}


/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void BinaryTree<Data>::Fold(FoldFunctor function, const void* parameter, void* accumulator) const {
    
    if (size > 0)
        FoldPreOrder(function, parameter, accumulator);

}

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor function, void* parameter) {
   
    if (size > 0)
        MapPreOrder(function, parameter, &(Root()));

}

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderFoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor function, const void* parameter, void* accumulator) const {
    
    if (size > 0)
        FoldPreOrder(function, parameter, accumulator, &(Root()));

}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor function, void* parameter) {
    
    if (size > 0)
        MapPostOrder(function, parameter, &(Root()));

}


/* ************************************************************************ */

// Specific member functions (inherited from PostOrderFoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor function, const void* parameter, void* accumulator) const {
    
    if (size > 0)
        FoldPostOrder(function, parameter, accumulator, &(Root()));

}


/* ************************************************************************ */

// Specific member functions (inherited from InOrderMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor function, void* parameter) {
    
    if (size > 0)
        MapInOrder(function, parameter, &(Root()));

}


/* ************************************************************************ */

// Specific member functions (inherited from InOrderFoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor function, const void* parameter, void* accumulator) const {

    if (size > 0)
        FoldInOrder(function, parameter, accumulator, &(Root()));

}


/* ************************************************************************ */

// Specific member functions (inherited from BreadthMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapBreadth(MapFunctor function, void* parameter) {
    
    if (size > 0)
        MapBreadth(function, parameter, &(Root()));

}


/* ************************************************************************ */

// Specific member functions (inherited from BreadthFoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldBreadth(FoldFunctor function, const void* parameter, void* accumulator) const {
    
    if (size > 0)
        FoldBreadth(function, parameter, accumulator, &(Root()));

}

/* ************************************************************************ */

// Auxiliary member functions (for PreOrderMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor function, void* parameter, Node* node) {
    
    if (node != nullptr) {

        function(node->Element(), parameter);

        if(node->HasLeftChild())
            MapPreOrder(function, parameter, &(node->LeftChild()));

        if(node->HasRightChild())
            MapPreOrder(function, parameter, &(node->RightChild()));

    }

}


/* ************************************************************************ */

// Auxiliary member functions (for PreOrderFoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor function, const void* parameter, void* accumulator, Node* node) const {

    if (node != nullptr) {

        function(node->Element(), parameter, accumulator);

        if(node->HasLeftChild())
            FoldPreOrder(function, parameter, accumulator, &(node->LeftChild()));

        if(node->HasRightChild())
            FoldPreOrder(function, parameter, accumulator, &(node->RightChild()));

    }

}


/* ************************************************************************ */

// Auxiliary member functions (for PostOrderMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor function, void* parameter, Node* node) {

    if (node != nullptr) {

        if(node->HasLeftChild())
            MapPostOrder(function, parameter, &(node->LeftChild()));
        
        if(node->HasRightChild())
            MapPostOrder(function, parameter, &(node->RightChild()));
        
        function(node->Element(), parameter);

    }

}


/* ************************************************************************ */

// Auxiliary member functions (for PostOrderFoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor function, const void* parameter, void* accumulator, Node* node) const {

    if (node != nullptr) {

        if(node->HasLeftChild())
            FoldPostOrder(function, parameter, accumulator, &(node->LeftChild()));
        
        if(node->HasRightChild())
            FoldPostOrder(function, parameter, accumulator, &(node->RightChild()));
        
        function(node->Element(), parameter, accumulator);

    }

}


/* ************************************************************************ */

// Auxiliary member functions (for InOrderMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor function, void* parameter, Node* node) {
    
    if (node != nullptr) {
        
        if (node->HasLeftChild())
            MapInOrder(function, parameter, &(node->LeftChild()));

        function(node->Element(), parameter);

        if (node->HasRightChild())
            MapInOrder(function, parameter, &(node->RightChild()));
    
    }

}


/* ************************************************************************ */

// Auxiliary member functions (for InOrderFoldableContainer)

template <typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor function, const void* parameter, void* accumulator, Node* node) const {
    
    if (node != nullptr) {
        
        if (node->HasLeftChild())
            FoldInOrder(function, parameter, accumulator, &(node->LeftChild()));

        function(node->Element(), parameter, accumulator);

        if (node->HasRightChild())
            FoldInOrder(function, parameter, accumulator, &(node->RightChild()));
    
    }

}


/* ************************************************************************ */

// Auxiliary member functions (for BreadthMappableContainer)

template <typename Data>
void BinaryTree<Data>::MapBreadth(MapFunctor function, void* parameter, Node* node) {
    
    lasd::QueueLst<Node*> queue;

    queue.Enqueue(node);
    Node* tmpNode;

    while (!(queue.Empty())) {

        tmpNode = queue.HeadNDequeue();

        function(tmpNode->Element(), parameter);
        
        if(tmpNode->HasLeftChild())
            queue.Enqueue(&(tmpNode->LeftChild()));
        
        if(tmpNode->HasRightChild())
            queue.Enqueue(&(tmpNode->RightChild()));

    }

}

template <typename Data>
void BinaryTree<Data>::FoldBreadth(FoldFunctor function, const void* parameter, void* accumulator, Node* node) const {
    
    lasd::QueueLst<const Node*> queue;

    queue.Enqueue(node);
    const Node* tmpNode;

    while (!(queue.Empty())) {

        tmpNode = queue.HeadNDequeue();

        function(tmpNode->Element(), parameter, accumulator);
        
        if(tmpNode->HasLeftChild())
            queue.Enqueue(&(tmpNode->LeftChild()));
        
        if(tmpNode->HasRightChild())
            queue.Enqueue(&(tmpNode->RightChild()));

    }

}


/* ************************************************************************** */

// Specific constructors (BTPreOrderIterator)

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& binaryTree) {

    if (binaryTree.Size() != 0) {

        root = &(binaryTree.Root());   
        current = &(binaryTree.Root());

    }

}


/* ************************************************************************ */

// Copy constructor (BTPreOrderIterator)

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& iterator) {

    root = iterator.root;
    current = iterator.current;

    stack = iterator.stack;

}


// Move constructor (BTPreOrderIterator)

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& iterator) noexcept {

    std::swap(root, iterator.root);
    std::swap(current, iterator.current);

    std::swap(stack, iterator.stack);

}


/* ************************************************************************ */

// Copy assignment (BTPreOrderIterator)

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& iterator) {
    
    BTPreOrderIterator<Data>* tmpIterator = new BTPreOrderIterator<Data>(iterator);

    std::swap(*tmpIterator, *this);

    delete (tmpIterator);

    return *this;

}

// Move assignment (BTPreOrderIterator)

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& iterator) noexcept {
    
    std::swap(root, iterator.root);
    std::swap(current, iterator.current);

    stack = std::move(iterator.stack);
    
    return *this;

}


/* ************************************************************************ */

// Comparison operators (BTPreOrderIterator)

template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> &iterator) const noexcept {
    
    if (current != iterator.current)
        return false;
    
    
    if (stack != iterator.stack)
        return false;
    
    return true;
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data> &iterator) const noexcept {
    
    return !(*this == iterator);

}


/* ************************************************************************ */

// Specific member functions (inherited from Iterator) (BTPreOrderIterator)

template <typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {

    if(Terminated())
        throw std::out_of_range("The PreOrder Iterator is terminated.");
    else
        return current->Element();

}

template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {

    return (current == nullptr);

}


/* ************************************************************************ */

// Specific member functions (inherited from ForwardIterator) (BTPreOrderIterator)

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    
    if (Terminated()) {

        throw std::out_of_range("The PreOrder Iterator is terminated.");

    } else {

        if(current->HasRightChild())
            stack.Push(&(current->RightChild()));

        if(current->HasLeftChild())
            stack.Push(&(current->LeftChild()));

        if(!(stack.Empty()))
            current = stack.TopNPop(); 
        else
            current = nullptr;
        
        return (*this);

    }
}


/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator) (BTPreOrderIterator)

template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {

    if (root != nullptr) {
        
        current = root;
        stack.Clear();

    }

}


/* ************************************************************************** */

// Specific constructors (BTPostOrderIterator)
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& binaryTree) {
    
    if (binaryTree.Size() != 0) {

        root = &binaryTree.Root();
        current = &binaryTree.Root();
        last = current;

        PostOrderNodeChoice();
        last = current;

    }

}


/* ************************************************************************ */

// Copy constructor (BTPostOrderIterator)

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& iterator) {
    
    root = iterator.root;
    current = iterator.current;

    last = iterator.last;
    stack = iterator.stack;

}

// Move constructor (BTPostOrderIterator)

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& iterator) noexcept {
    
    std::swap(root, iterator.root);
    std::swap(current,iterator.current);   

    std::swap(last, iterator.last);
    std::swap(stack, iterator.stack);

}


/* ************************************************************************ */

// Copy assignment (BTPostOrderIterator)

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& iterator) {
    
    BTPostOrderIterator<Data> *tmpIterator = new BTPostOrderIterator<Data>(iterator);
    
    std::swap(*tmpIterator, *this);

    delete tmpIterator;

    return *this;

}

// Move assignment (BTPostOrderIterator)

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& iterator) noexcept {
    
    std::swap(root, iterator.root);
    std::swap(current, iterator.current);
    std::swap(last, iterator.last);

    stack = std::move(iterator. stack);

    return *this;

}


/* ************************************************************************ */

// Comparison operators (BTPostOrderIterator)

template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& iterator) const noexcept {
    
    if (current != iterator.current)
        return false;

    if (last != iterator.last)
        return false;
    
    if (stack != iterator.stack)
        return false;
    
    return true;

}

template <typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& iterator) const noexcept {
    
    return !(*this==iterator);

}


/* ************************************************************************ */

// Specific member functions (inherited from Iterator) (BTPostOrderIterator)

template <typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
    
    if(Terminated())
        throw std::out_of_range("The PostOrder Iterator is terminated.");


    return current->Element();

}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
    
    return (current == nullptr);

}


/* ************************************************************************ */


// Specific member functions (inherited from ForwardIterator) (BTPostOrderIterator)

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
    
    if (Terminated())
        throw std::out_of_range("The PostOrder Iterator is terminated.");

    if (stack.Empty()) {

        current = nullptr;
        last = nullptr;

    } else {

        current = stack.TopNPop();

        if (current->HasRightChild() && !(&(current->RightChild()) == last)) {
            
            stack.Push(current);

            current = &(current->RightChild());

            PostOrderNodeChoice();

        }

    }

    last = current;

    return (*this);

}

/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator) (BTPostOrderIterator)

template<typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept {

    if (root != nullptr) {

        current = root;
        stack.Clear();

        PostOrderNodeChoice();
        last = current;

    }

}

/* ************************************************************************ */

// Auxiliary member functions (BTPostOrderIterator)

template<typename Data>
void BTPostOrderIterator<Data>::PostOrderNodeChoice() {
    
    bool cicle = true;
    
    while (!Terminated() && cicle) {
        
        if (current->HasLeftChild()) {

            stack.Push(current);
            current = &(current->LeftChild());

        } else {

            cicle = false;
   
        }
        
    }

    if (!Terminated()) {

        if(current->HasRightChild()) {

            stack.Push(current);
            current = &(current->RightChild());

            PostOrderNodeChoice();
        }

    }

}


/* ************************************************************************** */

// Specific constructors (BTInOrderIterator) 

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& binaryTree) {
    
    if (binaryTree.Size() != 0) {

        root = &binaryTree.Root();
        current = &binaryTree.Root();

        InOrderNodeChoice();

    }

}


/* ************************************************************************ */

// Copy constructor (BTInOrderIterator) 

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& iterator) {
    
    root = iterator.root;
    current = iterator.current;

    stack = iterator.stack;

}


// Move constructor (BTInOrderIterator) 

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& iterator) noexcept {
    
    std::swap(root, iterator.root);
    std::swap(current, iterator.current);

    std::swap(stack, iterator.stack);

}


/* ************************************************************************ */

// Copy assignment (BTInOrderIterator) 

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& iterator) {
    
    BTInOrderIterator<Data> *tmpIterator = new BTInOrderIterator<Data>(iterator);
    std::swap(*tmpIterator, *this);

    delete (tmpIterator);
    
    return *this;

}
 
// Move assignment (BTInOrderIterator) 

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& iterator) noexcept {
    
    std::swap(root, iterator.root);
    std::swap(current, iterator.current);
    stack = std::move(iterator.stack);
    
    return *this;

}


/* ************************************************************************ */

// Comparison operators (BTInOrderIterator) 

template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& iterator) const noexcept {
    
    if (current != iterator.current)
        return false;
    
    if (stack != iterator.stack)
        return false;
    
    return true;

}

template <typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& iterator) const noexcept {
    
    return !(*this == iterator);

}


/* ************************************************************************ */

// Specific member functions (inherited from Iterator) (BTInOrderIterator) 

template <typename Data>
Data& BTInOrderIterator<Data>::operator*() const {
    
    if (Terminated())
        throw std::out_of_range("The Iterator InOrder is terminated.");

    return current->Element();

}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
    
    return (current == nullptr);

}

/* ************************************************************************ */

// Specific member functions (inherited from ForwardIterator) (BTInOrderIterator) 

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
    
    if (Terminated())
        throw std::out_of_range("The Iterator InOrder is terminated.");
        
    if (current->HasRightChild()){

        current = &(current->RightChild());
        InOrderNodeChoice();

    } else {
        if (stack.Empty())
            current = nullptr;
        else
            current = stack.TopNPop(); 
    }

    return (*this);

}


/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator) (BTInOrderIterator) 

template<typename Data>
void BTInOrderIterator<Data>::Reset() noexcept {

    if (root != nullptr) {

        current = root;
        stack.Clear();

        InOrderNodeChoice();

    }

}

/* ************************************************************************** */

// Auxiliary member functions (BTInOrderIterator) 

template <typename Data>
void BTInOrderIterator<Data>::InOrderNodeChoice() {

    if (!Terminated()) {

        if (current->HasLeftChild()) {

            stack.Push(current);
            current = &(current->LeftChild());

            InOrderNodeChoice();

        }
    }
}


/* ************************************************************************** */

// Specific constructors (BTBreadthIterator)

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& binaryTree) {
    
    if (binaryTree.Size() != 0) {

        root = &binaryTree.Root();
        current = &binaryTree.Root();

    }

}


/* ************************************************************************ */

// Copy constructor (BTBreadthIterator)

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& iterator) {
    
    root = iterator.root;
    current = iterator.current;
    queue = iterator.queue;

}

// Move constructor (BTBreadthIterator)

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& iterator) noexcept {
    
    std::swap(root, iterator.root);
    std::swap(current,iterator.current);
    std::swap(queue, iterator.queue);   

}


/* ************************************************************************ */

// Copy assignment (BTBreadthIterator)

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& iterator) {
    
    BTBreadthIterator<Data> *tmpIterator = new BTBreadthIterator<Data>(iterator);

    std::swap(*tmpIterator, *this);

    delete (tmpIterator);

    return *this;

}

// Move assignment (BTBreadthIterator)

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& iterator) noexcept {
    
    std::swap(root, iterator.root);
    std::swap(current, iterator.current);
    queue = std::move(iterator.queue);
    
    return *this;
}


/* ************************************************************************ */

// Comparison operators (BTBreadthIterator)

template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& iterator) const noexcept {
    
    if (current != iterator.current)
        return false;
    
    if (queue != iterator.queue)
        return false;
    
    return true;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& iterator) const noexcept {
    
    return !(*this == iterator);

}


/* ************************************************************************ */

// Specific member functions (inherited from Iterator) (BTBreadthIterator)

template <typename Data>
Data& BTBreadthIterator<Data>::operator*() const {

    if (Terminated())
        throw std::out_of_range("The Breadth Iterator is terminated.");

    return current->Element();
}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {

    return (current == nullptr);

}


/* ************************************************************************ */

// Specific member functions (inherited from ForwardIterator) (BTBreadthIterator)

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    
    if (Terminated())
        throw std::out_of_range("The Breadth Iterator is terminated.");
    
    if (current->HasLeftChild())
        queue.Enqueue(&(current->LeftChild()));
    
    if (current->HasRightChild())
        queue.Enqueue(&(current->RightChild()));
    
    if (queue.Empty())
        current = nullptr;
    else
        current = queue.HeadNDequeue();

    return (*this);

}


/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator) (BTBreadthIterator)

template<typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {

    if (root != nullptr) {
        
        current = root;

        queue.Clear();

    }

}

}
