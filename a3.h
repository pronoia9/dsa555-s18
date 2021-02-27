#ifndef A3_H
#define A3_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int getIdx(char ch);
char getLetter(int idx);

class SpellCheck {
private:
	struct Node {
		char letter_;
		bool terminal_; // is true if its end of the word
		Node* children_[26];
		Node();
		Node(const char letter, const bool terminal = false);
	};
	Node* root_;
	int size_; // number of words in SpellCheck
public:
	SpellCheck(string data[], int size);
	void addWord(const string& newWord);
	bool lookup(const string& word) const;
	int suggest(const string& partialWord, string suggestions[]) const;
	void suggest(const Node* subroot, const string& partialWord, vector<string>& suggestions) const;
	bool hasChildren(const Node* subroot) const;
	void destroy(Node* subroot);
	int getSize() const;
	~SpellCheck();	
};
#endif