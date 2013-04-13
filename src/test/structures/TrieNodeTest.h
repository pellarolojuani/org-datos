#ifndef TRIENODETEST_H_
#define TRIENODETEST_H_

#include "../Testable.h"
#include "../../structures/trie/TrieNode.h"

class TrieNodeTest : public Testable{
public:
	void static testGetChild();

	void static testCountChild();

	cute::suite testSuite();
};
#endif
