#include "TrieNodeTest.h"

Testable::~Testable(){
}

/*
 * Pruebo getData con un solo
 */
void TrieNodeTest::testGetData1() {
	TrieNode testNode;
	TrieNodeData data1, data2;
	data1.data = 1234;
	testNode.setData("foo", data1);
	data2 = testNode.getData("foo");
	ASSERT_EQUAL(data1.data, data2.data);
}

void TrieNodeTest::testGetData2() {
	TrieNode testNode;
	TrieNodeData data1, data2, data3, data4;
	data1.data = 1234;
	data2.data = 234;
	data3.data = 34;
	testNode.setData("foo", data1);
	testNode.setData("foh", data2);
	testNode.setData("ZOMG", data3);
	data4 = testNode.getData("foo");
	ASSERT_EQUAL(data1.data, data4.data);
	data4 = testNode.getData("ZOMG");
	ASSERT_EQUAL(data3.data, data4.data);
	data4 = testNode.getData("foh");
	ASSERT_EQUAL(data2.data, data4.data);
}

void TrieNodeTest::testCountChild() {
	TrieNode testNode;
	TrieNodeData data1;
	testNode.setData("foo", data1);
	testNode.setData("fuh", data1);
	ASSERT_EQUAL(1, testNode.countChild());
	testNode = *(testNode.getChild('f'));
	ASSERT_EQUAL(2, testNode.countChild());
}

cute::suite TrieNodeTest::testSuite(){
	cute::suite s;
	s.push_back(CUTE(testGetData1));
	s.push_back(CUTE(testGetData2));
	s.push_back(CUTE(testCountChild));
	return s;
}
