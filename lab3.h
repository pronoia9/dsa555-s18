#include <iostream>

/**********************************************************************************************************************/
/******************************************************* DLIST ********************************************************/
/**********************************************************************************************************************/

template <typename T>
class DList {
private:
	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) { data_=data;  next_=next;  prev_=prev; }
	};
	Node* front_;
	Node* back_;

public:
	DList();
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~DList();
};

template <typename T>
DList<T>::DList() {
	front_ = nullptr;
	back_  = nullptr;
}

template <typename T>
void DList<T>::push_front(const T& data) 
{
	Node* nn = new Node(data, front_, nullptr);
	if (front_ != nullptr) { front_ -> prev_ = nn; }
	else                   { back_ = nn; }
	front_ = nn;
}

template <typename T>
void DList<T>::push_back(const T& data) 
{
	Node* nn = new Node(data, nullptr, back_);
	if (back_ != nullptr) { back_ -> next_ = nn; }
	else                  { front_ = nn; }
	back_ = nn;
}

template <typename T>
void DList<T>::pop_front() 
{
	if (front_ != nullptr)
	{
		Node* rn = front_;
		if (front_ != back_) {
			front_ = rn -> next_;
			front_ -> prev_ = nullptr;
		}
		else { front_ = back_ = nullptr; }
		delete rn;
	}
}

template <typename T>
void DList<T>::pop_back() 
{
	if (back_ != nullptr) {
		Node* rn = back_;
		if (back_ != front_) {
			back_ = back_ -> prev_;
			back_ -> next_ = nullptr;
		}
		else { front_ = back_ = nullptr; }
		delete rn;
	}
}

template <typename T>
void DList<T>::print() const 
{
	Node* curr = front_;
	while (curr != nullptr) {
		std::cout << curr -> data_ << " ";
		curr = curr -> next_;
	}
	std::cout << std::endl;
}

template <typename T>
void DList<T>::reversePrint() const 
{
	Node* curr = back_;
	while (curr != nullptr) {
		std::cout << curr -> data_ << " ";
		curr = curr -> prev_;
	}
	std::cout << std::endl;
}

template <typename T>
DList<T>::~DList() 
{
	Node* curr = front_;
	while (curr) {
		Node* rm = curr;
		curr = curr -> next_;
		delete rm;
	}
}


/**********************************************************************************************************************/
/****************************************************** SENTINEL ******************************************************/
/**********************************************************************************************************************/

template <typename T>
class Sentinel {
private:
	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T(), Node* next = nullptr, Node* prev = nullptr) { data_=data;  next_=next;  prev_=prev; }
	};
	Node* front_;
	Node* back_;

public:
	Sentinel();
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~Sentinel();
};

template <typename T>
Sentinel<T>::Sentinel() {
	front_ = new Node();
	back_  = new Node();
	front_ -> next_ = back_;
	back_  -> prev_ = front_;
}

template <typename T>
void Sentinel<T>::push_front(const T& data)
{
	Node* push = front_ -> next_;
	Node* nn = new Node(data, push, front_);
	push   -> prev_ = nn;
	front_ -> next_ = nn;
}

template <typename T>
void Sentinel<T>::push_back(const T& data)
{
	Node* push = back_ -> prev_;
	Node* nn = new Node(data, back_, push);
	push  -> next_ = nn;
	back_ -> prev_ = nn;
}

template <typename T>
void Sentinel<T>::pop_front()
{
	if (front_ -> next_ != back_)
	{
		Node* rn = front_ -> next_;
		Node* push = rn -> next_;
		push -> prev_ = front_;
		front_ -> next_ = push;
		delete rn;
	}
}

template <typename T>
void Sentinel<T>::pop_back()
{
	if (front_ -> next_ != back_)
	{
		Node* rn = back_ -> prev_;
		Node* push = rn -> prev_;
		back_ -> prev_ = push;
		push -> next_ = back_;
		delete rn;
	}
}

template <typename T>
void Sentinel<T>::print() const 
{
	Node* curr = front_ -> next_;
	while (curr != back_) {
		std::cout << curr -> data_ << " ";
		curr = curr -> next_;
	}
	std::cout << std::endl;
}

template <typename T>
void Sentinel<T>::reversePrint() const 
{
	Node* curr = back_ -> prev_;
	while(curr != front_) {
		std::cout << curr -> data_ << " ";
		curr = curr -> prev_;
	}
	std::cout << std::endl;
}

template <typename T>
Sentinel<T>::~Sentinel() 
{
	Node* curr = front_;
	while (curr) {
		Node* rm = curr;
		curr = curr -> next_;
		delete rm;
	}
}
