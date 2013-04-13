#include "TrieNode.h"

TrieNode::TrieNode() {
	// TODO Auto-generated constructor stub

}

TrieNode::~TrieNode() {
	// TODO Auto-generated destructor stub
}

bool TrieNode::hasChild() {
	return !this->childList.empty();
}

TrieNode* TrieNode::addChild(char tag) {
	TrieNode* node = getChild(tag);
	if (node == NULL){
		node = new TrieNode();
	}
	return node;
}

TrieNode* TrieNode::getChild(char tag) {
	std::list<TrieNode*>::iterator iterator;
	TrieNode* result = NULL;
	for(this->childList.begin(); iterator != this->childList.end(); iterator++){
		if ((*iterator)->getTag() == tag){
			result = *iterator;
		}
	}
	return result;
}
TrieNodeData TrieNode::getData(std::string key) {
	char tag = key.at(1);
	TrieNode* node = this->getChild(tag);
	return node->nodeData;
}

void TrieNode::setData(std::string key, TrieNodeData data) {

}

char TrieNode::getTag(){
	return this->tag;
}

int TrieNode::countChild() {
	return this->childList.size();
}

void TrieNode::addChildRec(std::string substring, TrieNodeData data){
	if (substring.size() > 0){
		//TrieNode* node  = getChild(substring.substr( ));
	}
}
