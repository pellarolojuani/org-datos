#ifndef TRIELEAF_H_
#define TRIELEAF_H_

#include <list>
#include <string>

struct TrieNodeData {
	int data;
};

class TrieNode {
public:
	TrieNode();
	virtual ~TrieNode();
	bool hasChild();
	/**
	 * addChild agrega un nodo hijo con el tag Tag, si ya hay uno con ese tag, lo devuelve.
	 */
	TrieNode* addChild(char tag);
	TrieNode* getChild(char tag);
	char getTag();
	void setData(std::string key, TrieNodeData data);
	TrieNodeData getData(std::string key);
	int countChild();
private:
	//Función recursiva que recorre las hojas del trie
	void addChildRec(std::string substring, TrieNodeData data);
	int size;
	char tag;
	std::list<TrieNode*> childList;
	/**
	 * (si, es ineficiente, puedo hacer cosas con casteo y usar un único puntero,
	 * pero es sencillísimo)
	 */
	TrieNodeData nodeData;
};

#endif /* TRIELEAF_H_ */
