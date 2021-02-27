#include <iostream>
#include <iomanip>

/*************************************** CLASS DECLARATION ***************************************/
template <typename T>
class DList {
private:
    struct Node {
        T data_;
        Node* next_;
        Node* prev_;
        Node(const T& data = T{}, Node* nx = nullptr, Node* pr = nullptr);
    };
    Node* front_;
    Node* back_;
    int size_;
    
public:
    class const_iterator {
        friend class DList;
    protected:
        Node* curr_;
        const_iterator(Node* n);
    public:
        const_iterator();
        const_iterator operator++();
        const_iterator operator++(int);
        const_iterator operator--();
        const_iterator operator--(int);
        bool operator==(const_iterator rhs);
        bool operator!=(const_iterator rhs);
        const T& operator*()const;
    };
    
    class iterator:public const_iterator {
        friend class DList;
        iterator(Node* n);
    public:
        iterator();
        iterator operator++();
        iterator operator++(int);
        iterator operator--();
        iterator operator--(int);
        T& operator*();
        const T& operator*()const;
    };
    
    // Constructors & Destructor
    DList();
    DList(const DList& rhs);
    DList(DList&& rhs);
    ~DList();
    // Assignment operators
    DList& operator=(const DList& rhs);
    DList& operator=(DList&& rhs);
    // General
    void push_front(const T& data);
    void push_back(const T& data);   
    void pop_front();
    void pop_back();
	void pop(Node* n);
    // Size check
    bool empty() const;
    int size() const; 
    // Iterator
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    iterator insert(const T& data, iterator it);
    iterator erase(iterator it);
    iterator erase(iterator first, iterator last);
    iterator search(const T& data);
    const_iterator search(const T& data) const;
    // Additional
    void printDetail();
};
/*************************************************************************************************/


/************************************** DLIST IMPLEMENTATION *************************************/
// Node constructor
// O(1)
template <typename T>
DList<T>::Node::Node(const T& data, Node* nx, Node* pr) { 
    data_ = data; 
    next_ = nx; 
    prev_ = pr; 
}

// Constructor, creates an empty list with sentinels
// O(1)
template <typename T>
DList<T>::DList() {
    front_ = new Node();
    back_  = new Node();
    front_->next_ = back_;
    back_->prev_ = front_;
    size_ = 0;
}

// Copy constructor
// O(n)
template <typename T>
DList<T>::DList(const DList& rhs) {
	front_ = new Node();
    back_  = new Node();
    front_->next_ = back_;
    back_->prev_ = front_;
    size_ = 0;
    for (const_iterator i = rhs.begin(); i != rhs.end(); i++) {
        push_back(*i);
    }
}

// Move constructor
// O(1)
template <typename T>
DList<T>::DList(DList&& rhs) {
    size_ = rhs.size();
    front_ = rhs.front_;
    back_ = rhs.back_;
    rhs.front_ = new Node();
    rhs.back_ = new Node();
	rhs.front_->next_ = rhs.back_;
	rhs.back_->prev_ = rhs.front_;
    rhs.size_ = 0;
}

// Destructor
// O(n)
template <typename T>
DList<T>::~DList() {
    Node* curr = front_;
    while (curr) {
        Node* rm = curr;
        curr = curr -> next_;
        delete rm;
    }
    size_ = 0;
}

// Copy assignment operator
// O(n)
template <typename T>
DList<T>& DList<T>::operator=(const DList& rhs) {
    if (this != &rhs) {
        if (!empty()) {
            //erase(begin(), end());
			while (size_ > 0) {
                pop_back();
            }
        }
        for (const_iterator i = rhs.begin(); i != rhs.end(); i++) {
            push_back(*i);
        }
        size_ = rhs.size();
    }
    return *this;
}

// Move assignment operator
// O(1)
template <typename T>
DList<T>& DList<T>::operator=(DList&& rhs) {
    if (this != &rhs) {
        DList<T> temp;
        temp.front_ = front_;
        temp.back_ = back_;
        front_ = rhs.front_;
        back_ = rhs.back_;
        size_ = rhs.size();
        rhs.front_ = new Node();
		rhs.back_ = new Node();
		rhs.front_->next_ = rhs.back_;
		rhs.back_->prev_ = rhs.front_;
    }
    return *this;
}

// Adds a node to the front of the list
// O(1)
template <typename T>
void DList<T>::push_front(const T& data) {
    Node* push = front_->next_;
    Node* nn = new Node(data, push, front_);
    push->prev_ = nn;
    front_->next_ = nn;
    size_++;
}

// Adds a node to the back of the list
// O(1)
template <typename T>
void DList<T>::push_back(const T& data) {
    Node* push = back_->prev_;
    Node* nn = new Node(data, back_, push);
    push->next_ = nn;
    back_->prev_ = nn;
    size_++;
}

// Removes the node from front of the list
// O(1)
template <typename T>
void DList<T>::pop_front() {
    if (front_->next_ != back_) {
        Node* rm = front_->next_;
        Node* push = rm->next_;
        push->prev_ = front_;
        front_->next_ = push;
        delete rm;
        size_--;
    }
}

// Removes a node from back of the list
// O(1)
template <typename T>
void DList<T>::pop_back() {
    if (back_->prev_ != front_) {
        Node* rm = back_->prev_;
        Node* push = rm->prev_;
        push->next_ = back_;
        back_->prev_ = push;
        delete rm;
        size_--;
    }
}

// Removes the node 'n'
// O(1)
template <typename T>
void DList<T>::pop(Node* n) {
	Node* before = n->prev_;
	Node* after  = n->next_;
	before->next_ = after;
	after->prev_ = before;
	size_--;
	delete n;
}

// Returns true if the list is empty (not counting sentinels)
// O(1)
template <typename T>
bool DList<T>::empty() const {
    //return size() == 0;
    return front_->next_ == back_;
}

// Returns the number of nodes with data
// O(1)
template <typename T>
int DList<T>::size() const {
    return size_;
}

// Returns iterator to first node with data
// O(1)
template<typename T>
typename DList<T>::iterator DList<T>::begin() {
    return iterator(front_->next_);
}

// Returns iterator to node after the last node with data (aka Last Sentinel)
// O(1)
template<typename T>
typename DList<T>::iterator DList<T>::end() {
    return iterator(back_);   
}

// Returns const_iterator to first node with data
// O(1)
template<typename T>
typename DList<T>::const_iterator DList<T>::begin() const {
    return const_iterator(front_->next_);
}

// Returns const_iterator to node after the last node with data
// O(1)
template<typename T>
typename DList<T>::const_iterator DList<T>::end() const {
    return const_iterator(back_);  
}

// Adds a node before the node referred to by the iterator
// O(1)
template <typename T>
typename DList<T>::iterator DList<T>::insert(const T& data, iterator it) {
    Node* before = it.curr_->prev_;
    Node* after  = it.curr_;
    Node* nn = new Node(data, after, before);
    before->next_ = nn;
    after->prev_ = nn;
    it.curr_ = nn;
    size_++;
    return it;
}

// Removes the node referred to by the iterator; returns the node after the removed node
// O(1)
template <typename T>
typename DList<T>::iterator DList<T>::erase(iterator it) {
	/*Node* before = it.curr_->prev_;
    Node* after  = it.curr_->next_;
	Node* rm = it.curr_;
    before->next_ = after;
    after->prev_ = before;
	it++;
	delete rm;
    size_--;
    return it;*/
    Node* rm = it.curr_;
	iterator after = ++it;
	--it;
	pop(it.curr_);
	return after;
}

// Removes the nodes starting with first up to (NOT including) last; returns iterator to last
// O(n), where n = last - first
template <typename T>
typename DList<T>::iterator DList<T>::erase(iterator first, iterator last) {
    while(first != last)  {
        first = erase(first);
    }
	/*while (first != last) {
		Node* rm = first.curr_;
		first++;
		pop(rm);
	}*/
    return last;
}

// Returns iterator to the node containing data. If not found, returns end()
// O(n)
template <typename T>
typename DList<T>::iterator DList<T>::search(const T& data) { 
    for (iterator i = begin(); i != end(); i++) {
        if (*i == data) { return i; }
    }
    return end();
}

// Returns const_iterator to the node containing data. If not found, returns end()
// O(n)
template <typename T>
typename DList<T>::const_iterator DList<T>::search(const T& data) const {
    for (iterator i = begin(); i != end(); i++) {
        if (*i == data) { return i; }
    }
    return end();
}

// Prints the list: with node number, node data, next node data
// O(n)
/*template <typename T>
void DList<T>::printDetail() // TODO: setw()s arent proper for custom objects, or long ones
{
    Node* cur = front_;
    std::cout << "list size = " << size() << std::endl;
    bool isSentinel = false;
    bool segFault = false;
    for (int i = 0; i <= size()+1; i++)
    {
        std::cout << "(i=" << std::setw(2) << std::right << i << "): ";
        std::cout << "[node=";  if (cur == front_ || cur == back_) { std::cout << "S]  "; }
                                else                               { std::cout << i-1 << "]  "; }
        std::cout << "[data=";  if (cur == front_) { std::cout << "FS]"; isSentinel = true; }
                                else if (cur == back_)  { std::cout << "LS]"; isSentinel = true; }
                                else { std::cout << std::setw(2) << std::right << cur->data_ << "]"; }
        std::cout << "   |   ";
        std::cout << "[next=";  if (cur->next_ == back_) { std::cout << "LS]  "; }
                                else if (i!=11) { std::cout << std::setw(2) << std::right << cur->next_->data_ << "]  "; }
                                else { std::cout << "--]  "; }
        std::cout << "[prev=";  if (cur->prev_ == front_) { std::cout << "FS]"; }
                                else if (i!=0) { std::cout << std::setw(2) << std::right << cur->prev_->data_ << "]"; }
                                else { std::cout << "--]"; }
        std::cout << std::endl;
        cur = cur->next_;
    }
}*/
/*************************************************************************************************/


/********************************* CONST ITERATOR IMPLEMENTATION *********************************/
// const_iterator constructor, sets curr_ to node n
// O(1)
template <typename T>
DList<T>::const_iterator::const_iterator(Node* n) {
    curr_ = n;
}

// const_iterator constructor, sets curr_ to nullpointer
// O(1)
template <typename T>
DList<T>::const_iterator::const_iterator() {
    curr_ = nullptr;
}

// Prefix increment
// O(1)
template<typename T>
typename DList<T>::const_iterator DList<T>::const_iterator::operator++() {
    curr_ = curr_->next_;
    return *this;
}

// Postfix increment
// O(1)
template<typename T>
typename DList<T>::const_iterator DList<T>::const_iterator::operator++(int) {
    const_iterator old = *this;
    curr_ = curr_->next_;
    return old;
}

// Prefix decrement
// O(1)
template<typename T>
typename DList<T>::const_iterator DList<T>::const_iterator::operator--() {
    curr_ = curr_->prev_;
    return *this;
}

// Postfix decrement
// O(1)
template<typename T>
typename DList<T>::const_iterator DList<T>::const_iterator::operator--(int) {
    const_iterator old = curr_;
    curr_ = curr_->prev_;
    return old;
}

// Compares it and rhs. Returns true if they ARE the same
// O(1)
template<typename T>
bool DList<T>::const_iterator::operator==(const_iterator rhs) {
    return curr_ == rhs.curr_;
}

// Compares it and rhs. Returns true if they are NOT the same
// O(1)
template<typename T>
bool DList<T>::const_iterator::operator!=(const_iterator rhs) {
    return curr_ != rhs.curr_;
}

// Dereferencing operator, returns the data (const) in the node pointed to by iterator
// O(1)
template<typename T>
const T & DList<T>::const_iterator::operator*() const {
    return curr_->data_;
}
/*************************************************************************************************/


/************************************ ITERATOR IMPLEMENTATION ************************************/
// Iterator constructor, sets curr_ = n
// O(1)
template <typename T>
DList<T>::iterator::iterator(Node* n) : const_iterator(n) {}

// Iterator constructor, sets curr as nullptr
// O(1)
template <typename T>
DList<T>::iterator::iterator() : const_iterator() {}

// Prefix increment
// O(1)
template<typename T>
typename DList<T>::iterator DList<T>::iterator::operator++() {
    this->curr_ = this->curr_->next_;
    return *this;
}

// Postfix increment
// O(1)
template<typename T>
typename DList<T>::iterator DList<T>::iterator::operator++(int) {
    iterator old = this->curr_;
    this->curr_ = this->curr_->next_;
    return old;
}

// Prefix decrement
// O(1)
template<typename T>
typename DList<T>::iterator DList<T>::iterator::operator--() {
    this->curr_ = this->curr_->prev_;
    return *this;
}

// Prefix decrement
// O(1)
template<typename T>
typename DList<T>::iterator DList<T>::iterator::operator--(int) {
    iterator old = this->curr_;
    this->curr_ = this->curr_->prev_;
    return old;
}

// Dereferencing operator, returns the data in the node pointed to by iterator
// O(1)
template<typename T>
T & DList<T>::iterator::operator*() {
    return this->curr_->data_;
}

// Dereferencing operator, returns the (const) data in the node pointed to by iterator
// O(1)
template<typename T>
const T & DList<T>::iterator::operator*() const {
    return this->curr_->data_;
}
/*************************************************************************************************/