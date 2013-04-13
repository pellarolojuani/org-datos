#include "TrieNodeTest.h"

Testable::~Testable(){
}

void TrieNodeTest::testGetChild() {
	TrieNode testNode;
	TrieNodeData data1;
	testNode.setData("foo", data1);
	testNode.setData("fuh", data1);
	ASSERT_EQUAL(2, testNode.countChild());
}

void TrieNodeTest::testCountChild() {
	TrieNode testNode;
	TrieNodeData data1;
	testNode.setData("foo", data1);
	testNode.setData("fuh", data1);
	ASSERT_EQUAL(2, testNode.countChild());
}

cute::suite TrieNodeTest::testSuite(){
	cute::suite s;
	s.push_back(CUTE(testGetChild));
	s.push_back(CUTE(testCountChild));
	return s;
}
