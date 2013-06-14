#include <iostream>
#include "TrieNode.h"


void printRec(TrieNode* node){
	if (node != NULL){
		TrieNode* aux = node->childList.begin().operator *();
		std::cout << aux->getTag() << " tiene el dato : " << aux->nodeData.data <<  std::endl;
		if (aux->getTag() != 0){
			printRec(aux);
		}
	}
}

void TrieNode::printTrie(){
	printRec(this);
}

TrieNode::TrieNode() {
	this->size = 0;
	this->tag = 0;
}

TrieNode::~TrieNode() {
	// TODO Auto-generated destructor stub
}

bool TrieNode::hasChild() {
	return !this->childList.empty();
}

/**
 * Busca un hijo con el tag dado, si lo encuentra, lo devuelve, sino, lo crea y devuelve el nuevo.
 */
TrieNode* TrieNode::addChild(char tag) {
	TrieNode* node = getChild(tag);
	if (node == NULL){
		node = new TrieNode();
		node->tag = tag;
		this->childList.push_back(node);
	}
	return node;
}

/**
 * Devuelve el hijo con el tag pasado por parámetro, si no lo encuentra, devuelve null.
 */
TrieNode* TrieNode::getChild(char tag) {
	std::list<TrieNode*> list;
	typename std::list<TrieNode*>::iterator iterator;
	TrieNode* result = NULL;
	for(iterator = this->childList.begin(); iterator != this->childList.end(); iterator++){
		if ((*iterator)->getTag() == tag){
			result = *iterator;
			break;
		}
	}
	return result;
}

/**
 * Asumo que el string tiene aunque sea 1 caracter (incluyendo fin de linea)
 */
TrieNodeData TrieNode::getDataRec(std::string key) {
	//Hace getChild con la primer letra del key
	TrieNode* childNode = this->getChild(key[0]);
	//TODO: if childNode == NULL, tiro excepcion
	if (key.size() > 0){
		return childNode->getDataRec(key.substr(1));
	} else {
		return childNode->nodeData;
	}
}

TrieNodeData TrieNode::getData(std::string key) {
	std::cout << "Obteniendo data" << key << std::endl;
	return getDataRec(key);
}

void TrieNode::setData(std::string key, TrieNodeData data) {
	TrieNode* childNode;
	if (key.size() > 0){
		childNode = this->addChild(key[0]);
		childNode->setData(key.substr(1), data);
	} else {
		//Es fin de palabra
		childNode = this->addChild(0);
		childNode->nodeData = data;
	}
}

char TrieNode::getTag(){
	return this->tag;
}

int TrieNode::countChild() {
	return this->childList.size();
}
