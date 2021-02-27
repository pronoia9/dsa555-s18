/*************************************************************/
/*                                                           */
/*    Starter file for a2                                    */
/*                                                           */
/*************************************************************/
//#include <iostream>
#include <string>
#include <utility>
using namespace std;

template <class TYPE>
class Table {
public:
	Table() {}
	virtual bool update(const string& key, const TYPE& value) = 0;
	virtual bool remove(const string& key) = 0;
	virtual bool find(const string& key, TYPE& value) = 0;
	virtual int numRecords() const = 0;
	virtual bool isEmpty() const = 0;
	virtual ~Table() {}
};

template <class TYPE>
class SimpleTable :public Table<TYPE> {
	struct Record {
		TYPE data_;
		string key_;
		Record(const string& key, const TYPE& data) { key_ = key;  data_ = data; }
	};
	Record** records_;   //the table
	int max_;           //capacity of the array
	int size_;          //current number of records held
	int search(const string& key);
	void sort();
	void grow();
public:
	SimpleTable(int maxExpected);
	SimpleTable(const SimpleTable& other);
	SimpleTable(SimpleTable&& other);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual const SimpleTable& operator=(SimpleTable&& other);
	virtual ~SimpleTable();
	virtual bool isEmpty() const { return size_ == 0; }
	virtual int numRecords() const { return size_; }
};

//returns index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key) {
	int rc = -1;
	for (int i = 0; i < size_; i++) {
		if (records_[i]->key_ == key) {
			rc = i;
		}
	}
	return rc;
}

//sort the according to key in table
template <class TYPE>
void SimpleTable<TYPE>::sort() {
	int minIdx = 0;
	for (int i = 0; i < size_; i++) {
		minIdx = i;
		for (int j = i + 1; j < size_; j++) {
			if (records_[j]->key_ < records_[minIdx]->key_) {
				minIdx = j;
			}
		}
		Record* tmp = records_[i];
		records_[i] = records_[minIdx];
		records_[minIdx] = tmp;
	}
}

//grow the array by one element
template <class TYPE>
void SimpleTable<TYPE>::grow() {
	Record** newArray = new Record*[max_ * 2];
	max_ = max_ * 2;
	for (int i = 0; i < size_; i++) {
		newArray[i] = records_[i];
	}
	delete[] records_;
	records_ = newArray;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected) : Table<TYPE>() {
	records_ = new Record*[maxExpected];
	max_ = maxExpected;
	size_ = 0;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other) {
	records_ = new Record*[other.max_];
	max_ = other.max_;
	size_ = 0;
	for (int i = 0; i < other.size_; i++) {
		update(other.records_[i]->key_, other.records_[i]->data_);
	}
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other) {
	size_ = other.size_;
	max_ = other.max_;
	records_ = other.records_;
	other.records_ = nullptr;
	other.size_ = 0;
	other.max_ = 0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value) {
	int idx = search(key);
	if (idx == -1) {
		if (size_ == max_) {
			grow();
		}
		records_[size_++] = new Record(key, value);
		sort();
	}
	else {
		records_[idx]->data_ = value;
	}
	return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key) {
	int idx = search(key);
	if (idx != -1) {
		delete records_[idx];
		for (int i = idx; i < size_ - 1; i++) {
			records_[i] = records_[i + 1];
		}
		size_--;
		return true;
	}
	else {
		return false;
	}
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value) {
	int idx = search(key);
	if (idx == -1)
		return false;
	else {
		value = records_[idx]->data_;
		return true;
	}
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other) {
	if (this != &other) {
		if (records_) {
			int sz = size_;
			for (int i = 0; i < sz; i++) {
				remove(records_[0]->key_);
			}
			delete[] records_;
		}
		records_ = new Record*[other.max_];
		max_ = other.max_;
		size_ = 0;
		for (int i = 0; i < other.size_; i++) {
			update(other.records_[i]->key_, other.records_[i]->data_);
		}

	}
	return *this;
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other) {
	swap(records_, other.records_);
	swap(size_, other.size_);
	swap(max_, other.max_);
	return *this;
}

template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
	if (records_) {
		int sz = size_;
		for (int i = 0; i < sz; i++) {
			remove(records_[0]->key_);
		}
		delete[] records_;
	}
}

template <class TYPE>
class LPTable : public Table<TYPE> {
private:
    struct Record {
        TYPE data_;
        string key_;
        Record(const string& key, const TYPE& data) { key_ = key;  data_ = data; }
    };
    Record** records_;
    int max_;
    int size_;
	// EXTRA
	int search(const string& key);
	void grow();
	void sort();
public:
    LPTable(int maxExpected);
    LPTable(const LPTable& other);
    LPTable(LPTable&& other);
    virtual bool update(const string& key, const TYPE& value);
    virtual bool remove(const string& key);
    virtual bool find(const string& key, TYPE& value);
    virtual const LPTable& operator=(const LPTable& other);
    virtual const LPTable& operator=(LPTable&& other);
    virtual ~LPTable();
    bool isEmpty() const;
    int numRecords() const;
	// EXTRA
	int iHash(const string& key);
	int max() const;
	bool isFull() const;
	string getKey(const int idx) const;
	TYPE getData(const int idx) const;
};

// returns the index of where key is found, or -1 if not found
template <class TYPE>
int LPTable<TYPE>::search(const string& key) {
	int idx = iHash(key);
	if (records_[idx] != nullptr) {
		if (records_[idx]->key_ == key) {
			return idx;
		}
		else {
			int i = idx + 1;
			if (idx == max_ - 1) {
				i = 0;
			}
			while (records_[i] != nullptr && i != idx) {
				if (records_[i]->key_ == key) {
					return i;
				}
				if (i == max_ - 1) {
					i = 0;
				}
				else {
					i++;
				}
			}
		}
	}
	return -1;
}

// grows the array by x2
template <class TYPE>
void LPTable<TYPE>::grow() {
	Record** newRecs = new Record*[max_ * 2];
	for (int i = 0; i < max_ * 2; i++) {
		if (i < max_ && records_[i] != nullptr) {
			newRecs[i] = records_[i];
		}
		else {
			newRecs[i] = nullptr;
		}
	}
	max_ *= 2;
	delete[] records_;
	records_ = newRecs;
}

// sort; could easily do ascending/descending... but need to account iHash() indexes
// maybe a modified bucket like algorithm, or a 2D smt
// TODO : later. maybe.
template <class TYPE>
void LPTable<TYPE>::sort() {
}

// LPTable constructor, initializes table 200% bigger
template <class TYPE>
LPTable<TYPE>::LPTable(int maxExpected) : Table<TYPE>() {
	max_ = maxExpected * 2;
	size_ = 0;
	records_ = new Record*[max_];
	for (int i = 0; i < max_; i++) {
		records_[i] = nullptr;
	}
}

// copy constructor for LPTable
template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other) {
	max_ = other.max_;
	size_ = other.size_;
	records_ = new Record*[max_];
	for (int i = 0; i < max_; i++) {
		if (other.records_[i] != nullptr) {
			records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_);
		}
		else {
			records_[i] = nullptr;
		}
	}
}

// move constructor for LPTable
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other) {
	max_ = other.max_;
	size_ = other.size_;
	records_ = other.records_;
	other.records_ = nullptr;
	other.size_ = 0;
	other.max_ = 0;
}

// adds a new element to the table, or updates (the data of) an existing one
template <class TYPE>
bool LPTable<TYPE>::update(const string& key, const TYPE& value) {
	int idx = search(key);
	if (idx == -1) {
		if (size_ == max_) {
			grow();
		}
		idx = iHash(key);
		while (records_[idx] != nullptr && records_[idx]->key_ != key && idx < max_ - 1) {
			idx++;
			if (idx == max_) {
				idx = 0;
			}
		}
		records_[idx] = new Record(key, value);
		size_++;
		return true;
	}
	else {
		records_[idx]->data_ = value;
		return true;
	}
}

// returns true if an element is in the table, false if not
template <class TYPE>
bool LPTable<TYPE>::find(const string& key, TYPE& value) {
	int idx = search(key); 
	if (idx != -1) {
		value = records_[idx]->data_;
		return true;
	}
	else {
		return false;
	}
}

// removes an element('s key) from the table, returns true on success
template <class TYPE>
bool LPTable<TYPE>::remove(const string& key) {
	int idx = iHash(key);
	if (records_[idx] != nullptr) {
		if (records_[idx]->key_ == key) {
			records_[idx]->key_ = "";
			return true;
		}
		else {
			int i = idx + 1;
			if (idx == max_ - 1) {
				i = 0;
			}
			while (records_[i] != nullptr && i != idx) {
				if (records_[i]->key_ == key) {
					records_[i]->key_ = "";
					return true;
				}
				if (i == max_ - 1) {
					i = 0;
				}
				else {
					i++;
				}
			}
		}
	}
	return false;
}

// copy assignment operator for LPTable
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other) {
	if (this != &other) {
		if (records_) {
			for (int i = 0; i < max_; i++) {
				if (records_[i] != nullptr) {
					// delete existing records
					delete records_[i];
				}
			}
			delete[] records_;
		}
		max_ = other.max_;
		size_ = other.size_;
		records_ = new Record*[max_];
		for (int i = 0; i < max_; i++) {
			if (other.records_[i] != nullptr) {
				records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_);
			}
			else {
				records_[i] = nullptr;
			}
		}
	}
	return *this;
}

// move assignment operator for LPTable
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other) {
	if (this != &other) {
		swap(max_, other.max_);
		swap(size_, other.size_);
		swap(records_, other.records_);
		// delete other's records?
	}
	return *this;
}

// destructor for LPTable
template <class TYPE>
LPTable<TYPE>::~LPTable() {
	for (int i = 0; i < max_; i++) {
		if (records_[i] != nullptr) {
			delete records_[i];
		}
	}
	delete records_;
}

// returns the hash index of a string key
template <class TYPE>
int LPTable<TYPE>::iHash(const string& key) {
    std::hash<std::string> hashFunction;
	size_t hashIndex = hashFunction(key) % max_;
	return hashIndex;
}

// returns true if the table has 1+ element(s)
template <class TYPE>
bool LPTable<TYPE>::isEmpty() const {
	return size_ == 0;
}

// returns the number of elements in the table
template <class TYPE>
int LPTable<TYPE>::numRecords() const {
	return size_;
}

// returns whether or not the table is full
template <class TYPE>
bool LPTable<TYPE>::isFull() const {
	return size_ == max_;
}

// returns the max number of elements the table can hold
template <class TYPE>
int LPTable<TYPE>::max() const {
	return max_;
}

// returns the key_ of records_[idx]
template <class TYPE>
string LPTable<TYPE>::getKey(const int idx) const {
	if (records_[idx] != NULL) {
		return records_[idx]->key_;
	}
	else {
		return "";
	}
}

// returns the data_ of records_[idx]
template <class TYPE>
TYPE LPTable<TYPE>::getData(const int idx) const {
	if (records_[idx] != NULL) {
		return records_[idx]->data_;
	}
	else {
		return 0;
	}
}