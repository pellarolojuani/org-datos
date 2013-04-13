#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include "../../text/StringMatch.h"

class Trie {
public:
	Trie();
	virtual ~Trie();
	int addData(std::string label, StringMatch match);
};

#endif /* TRIE_H_ */
