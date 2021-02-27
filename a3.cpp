#include "a3.h"
#include <algorithm>
using namespace std;

// gets a letter, returns its index (place in the alphabeth)
int getIdx(char ch) {
    return (int)ch - (int)'a';
}

// gets a number, returns what letter is in that spot in the alphabeth
char getLetter(int idx) {
    return idx + (int)'a';
}

// Node constructor, creates a new node with all its children 'nullptr'd
SpellCheck::Node::Node() {
    letter_ = ' ';
    terminal_ = false;
    for (int i = 0; i < 26; i++) {
        children_[i] = nullptr;
    }
}

// Node constructor, creates a new node with the letter given, and the optional terminal
SpellCheck::Node::Node(const char letter, const bool terminal) {
	letter_ = letter;
    terminal_ = terminal;
    for (int i = 0; i < 26; i++) {
        children_[i] = nullptr;
    }
}

// constructor, gets array of (string) words and (int) size of array (number of words to be added);
// adds them to Spell Checker, and sets the size to the number of words added
SpellCheck::SpellCheck(string data[], int size) {
    root_ = new Node();
    size_ = 0;
    Node* currNode = root_;
    for (int i = 0; i < size; i++) {
        addWord(data[i]);
    }
}

// gets a (string) word, adds it to SpellCheck
// adds that word to Spell Check
void SpellCheck::addWord(const string& newWord) {
    Node* currNode = root_;
    for (int i = 0; i < newWord.length(); i++) { 
        int idx = getIdx(newWord[i]);
        if (currNode->children_[idx] == nullptr) {
            currNode->children_[idx] = new Node(newWord[i]);
        }
        currNode = currNode->children_[idx];
    }
    if (currNode->terminal_ != true) { // dont add to size if the addedWord is already in there
        size_++;
    }
    currNode->terminal_ = true;
}

// gets a (string) word, 
// returns true if that word is in SpellCheck
bool SpellCheck::lookup(const string& word) const {
    Node* currNode = root_;
    for (int i = 0; i < word.length(); i++) {
        int idx = getIdx(word[i]);
        if (currNode->children_[idx] == nullptr) {
            return false;
        }
        currNode = currNode->children_[idx];
    }
    return (currNode != nullptr && currNode->terminal_);
}

// gets a (string) word, checks the SpellCheck to find all the suggestions, 
// returns number of words stored within suggestions
int SpellCheck::suggest(const string& partialWord, string suggestions[]) const {
    Node* currNode = root_;
    for (int i = 0; i < partialWord.length(); i++) {
        int idx = getIdx(partialWord[i]);
        if (currNode->children_[idx] == nullptr) {
            return 0;
        }
        currNode = currNode->children_[idx];
    }
    vector<string> suggestVector;
    suggest(currNode, partialWord, suggestVector);
    if (currNode->terminal_) {
        suggestVector.push_back(partialWord);
    }
    sort(suggestVector.begin(), suggestVector.end());
    copy(suggestVector.begin(), suggestVector.end(), suggestions);
    return suggestVector.size();
}

void SpellCheck::suggest(const Node* subroot, const string& partialWord, vector<string>& suggestions) const {
    for (int i = 0; i < 26; i++) {
        if (subroot->children_[i] != nullptr) {
            string partial = partialWord + subroot->children_[i]->letter_;
            suggest(subroot->children_[i], partial, suggestions);
            if (subroot->children_[i]->terminal_) {
                suggestions.push_back(partial);
            }
        }
    }
}

// returns true if the subroot has any children, false if it doesnt
bool SpellCheck::hasChildren(const Node* subroot) const {
    for (int i = 0; i < 26; i++) {
        if (subroot->children_[i]) {
            return true;
        }
    }
    return false;
}

// destructor helper
// deletes all nodes
void SpellCheck::destroy(Node* subroot) {
	if (subroot != nullptr) {
		for (int i = 0; i < 26; i++) {
			destroy(subroot->children_[i]);
		}
		delete subroot;
	}
}

int SpellCheck::getSize() const {
    return size_;
}

SpellCheck::~SpellCheck() {
    destroy(root_);
}