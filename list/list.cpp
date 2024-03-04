
namespace lasd {

/* ************************************************************************** */

// Specific constructor (Node)

template<typename Data>
List<Data>::Node::Node(Data&& value) noexcept {
    std::swap(element, value);
}

/* ************************************************************************** */

// Move constructor (Node)

template<typename Data>
List<Data>::Node::Node(Node&& node) noexcept {
    std::swap(element, node.element);
    std::swap(next, node.next);
}

/* ************************************************************************** */

// Destructor (Node)

template<typename Data>
List<Data>::Node::~Node() {
    delete next;
}

/* ************************************************************************** */

// Comparison operators (Node)

template<typename Data>
bool List<Data>::Node::operator==(const Node& node) const noexcept {
    return (this->element == node.element);
}

template<typename Data>
inline bool List<Data>::Node::operator!=(const Node& node) const noexcept {
    return !(*this == node);
}


/* ************************************************************************** */

// Specific costructor (List)

template<typename Data>
List<Data>::List(const LinearContainer<Data>& structure) {
    
    size = 0;

    for (ulong i = 0; i < structure.Size(); i++) {
        InsertAtBack(structure[i]);
    }
}


/* ************************************************************************** */

// Copy Constructor (List)

template<typename Data>
List<Data>::List(const List<Data>& list) {

    Node* tmpHead = list.head;

    while (tmpHead != nullptr) {

        InsertAtBack(tmpHead->element);

        tmpHead = tmpHead->next;
    }

}


/* ************************************************************************** */

// Move Constructor (List)

template<typename Data>
List<Data>::List(List<Data>&& list) noexcept {

    std::swap(tail, list.tail);
    std::swap(head, list.head);
    std::swap(size, list.size);

}


/* ************************************************************************** */

// Destructor

template<typename Data>
List<Data>::~List() {

    while (head != nullptr) {
        RemoveFromFront();
    }
}


/* ************************************************************************** */

// Copy Assignment

template<typename Data>
List<Data>& List<Data>::operator=(const List<Data>& list) {
    
    List<Data>* tmpList = new List<Data>(list);
    std::swap(*tmpList, *this);

    delete tmpList;
    return *this;
}

// Move Assignment

template<typename Data>
List<Data>& List<Data>::operator=(List&& list) noexcept {

    std::swap(tail, list.tail);
    std::swap(head, list.head);
    std::swap(size, list.size);

    return *this;
}

/* ************************************************************************** */

// Comparison Operator

template<typename Data>
bool List<Data>::operator==(const List& list) const noexcept {

    if (size != list.size) {
        
        return false;

    } else {
        
        for (ulong i = 0; i < size; i++) {

            if ((*this)[i] != list[i]) {

                return false;
            }
        }

        return true;
    }
}

template<typename Data>
bool List<Data>::operator!=(const List& list) const noexcept {
    return !(*this == list);
}

/* ************************************************************************** */

// Specific member function


// Copy of the Value
template<typename Data>
void List<Data>::InsertAtFront(const Data& value) {

    Node* tmpHead = new Node(value);

    size++;

    if (head == nullptr) {

        head = tmpHead;
        tail = head;

    } else {

        tmpHead->next = head;
        head = tmpHead;
    }
}

// Move of the Value
template<typename Data>
void List<Data>::InsertAtFront(Data&& value) {

    Node* tmpHead = new Node(std::move(value));

    size++;

    if (head == nullptr) {

        head = tmpHead;
        tail = head;

    } else {

        tmpHead->next = head;
        head = tmpHead;
    }
}

template<typename Data>
void List<Data>::RemoveFromFront() {

    if (head != nullptr) {

        Node* tmpHead = head;
        head = head->next;
        tmpHead->next = nullptr;

        size--;

        delete tmpHead;

    } else {

        throw std::length_error("Access to an empty List");
    }
}

template<typename Data>
Data List<Data>::FrontNRemove() {

    if (head != nullptr) {

        Node* tmpHead = head;
        Data value = tmpHead->element;

        head = head->next;
        tmpHead->next = nullptr;

        size--;

        delete tmpHead;

        return value;

    } else {

        throw std::length_error("Access to an empty List");
    }
}


// Copy of the value
template<typename Data>
void List<Data>::InsertAtBack(const Data& value) noexcept {

    Node* tmpTail = new Node(value);

    size++;

    if (head == nullptr) {

        head = tmpTail;
        tail = head;

    } else {

        tail->next = tmpTail;
        tail = tmpTail;
    }

}

// Move of the value
template<typename Data>
void List<Data>::InsertAtBack(Data&& value) {

    Node* tmpTail = new Node(std::move(value));

    size++;

    if (head == nullptr) {

        head = tmpTail;
        tail = head;

    } else {

        tail->next = tmpTail;
        tail = tmpTail;
    }
}


/* ************************************************************************** */

// Specific member functions (inherited from Container)

template<typename Data>
void List<Data>::Clear() {

    while (head != nullptr) {

        RemoveFromFront();
        
    }

    head = nullptr;
    tail = nullptr;

    size = 0;

}


/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

template<typename Data>
Data& List<Data>::Front() const {
    
    if (head != nullptr) {

        return head->element;

    } else {

        throw std::length_error("Access to an empty List");
    }
}

template<typename Data>
Data& List<Data>::Back() const {
    
    if (head != nullptr) {

        return tail->element;

    } else {

        throw std::length_error("Access to an empty List");
    }
}


template<typename Data>
Data& List<Data>::operator[](ulong value) const {

    if (value > size) {
        throw std::out_of_range("Access at index out of range.");
    }
    
    Node* tmpNode = head;
    ulong i = 0;

    while (i < value) {
        
        tmpNode = tmpNode->next;

        i++;
    }

    return tmpNode->element;
}


/* ************************************************************************** */


// Specific Member Functions (inherited from MappableContainer)

template<typename Data>
inline void List<Data>::Map(MapFunctor function, void* parameter) {
    MapPreOrder(function, parameter);
}

/* ************************************************************************** */

// Specific member function (inherited from PreOrderMappableContainer)

template<typename Data>
inline void List<Data>::MapPreOrder(MapFunctor function, void* parameter) {
    MapPreOrder(function, parameter, head);
}

/* ************************************************************************** */

// Specific member function (inherited from PostOrderMappableContainer)

template<typename Data>
inline void List<Data>::MapPostOrder(MapFunctor function, void* parameter) {
    MapPostOrder(function, parameter, head);
}

/* ************************************************************************** */

// Specific member function (inherited from FoldableContainer)

template<typename Data>
inline void List<Data>::Fold(FoldFunctor function, const void* parameter, void* accumulator) const {
    FoldPreOrder(function, parameter, accumulator, head);
}

/* ************************************************************************** */

// Specific member function (inherited from PreOrderFoldableContainer)

template<typename Data>
inline void List<Data>::FoldPreOrder(FoldFunctor function, const void* parameter, void* accumulator) const {
    FoldPreOrder(function, parameter, accumulator, head);
}

/* ************************************************************************** */

// Specific member function (inherited from PostOrderFoldableContainer)

template<typename Data>
inline void List<Data>::FoldPostOrder(FoldFunctor function, const void* parameter, void* accumulator) const {
    FoldPostOrder(function, parameter, accumulator, head);
}

/* ************************************************************************** */

// Auxiliary member functions (for MappableContainer)

template<typename Data>
void List<Data>::MapPreOrder(MapFunctor function, void* parameter, Node* current) {
    for(; current != nullptr; current = current->next) {
        function(current->element, parameter);
    }
}

template<typename Data>
void List<Data>::MapPostOrder(MapFunctor function, void* parameter, Node* current) {
    if (current != nullptr) {
        MapPostOrder(function, parameter, current->next);
        function(current->element, parameter);
    }
}

/* ************************************************************************** */

// Auxiliary member functions (for FoldableContainer)

template<typename Data>
void List<Data>::FoldPreOrder(FoldFunctor function, const void* parameter, void* accumulator, Node* current) const {
    for(; current!= nullptr; current = current->next) {
        function(current->element, parameter, accumulator);
    }
}

template<typename Data>
void List<Data>::FoldPostOrder(FoldFunctor function, const void* parameter, void* accumulator, Node* current) const {
    if (current != nullptr) {
        FoldPostOrder(function, parameter, accumulator, current->next);
        function(current->element, parameter, accumulator);
    }
}

}
