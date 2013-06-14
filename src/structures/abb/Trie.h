#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include "../data/StringMatch.h"

class Trie {
public:
	Trie();
	virtual ~Trie();
	int addMatch(std::string label, StringMatch match);
};

#endif /* TRIE_H_ */
