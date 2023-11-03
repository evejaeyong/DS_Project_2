#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {
	string name = newData->getName();
	BpTreeNode* node;
	if (root == NULL) {
		node = new BpTreeDataNode;
		node->insertDataMap(name, newData);
		return true;
	}

	if (searchDataNode(name) != NULL) {
		delete newData;
		LoanBookData* data = searchDataNode(name)->getDataMap()->find(name)->second;
		data->updateCount();
		if (data->getCode() < 300) {
			if (data->getLoanCount() >= 3) {
				//delete
				return false;
			}
		}
		else if (data->getCode() < 500){
			if (data->getLoanCount() >= 4) {
				//delete
				return false;
			}
		}
		else {
			if (data->getLoanCount() >= 2) {
				//delete
				return false;
			}
		}
	}
	else {
		
	}

	return true;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	
}

BpTreeNode* BpTree::searchDataNode(string name) {
	BpTreeNode* pCur = root;
	while (pCur->getMostLeftChild()) {
		if (pCur->getIndexMap()->begin()->first > name) {
			pCur = pCur->getMostLeftChild();
		}
		else {
			pCur = pCur->getIndexMap()->find(name)->second;
		}
	}
	if (pCur->getDataMap()->find(name) == pCur->getDataMap()->end()) {
		return NULL;
	}

	return pCur;
}

bool BpTree::searchBook(string name) {
	BpTreeNode* pCur = root;
	while (pCur->getMostLeftChild()) {
		if (pCur->getIndexMap()->begin()->first > name) {
			pCur = pCur->getMostLeftChild();
		}
		else {
			pCur = pCur->getIndexMap()->find(name)->second;
		}
	}
	if (pCur->getDataMap()->find(name) != pCur->getDataMap()->end()) {
		fout->open("log.txt");
		LoanBookData* data = pCur->getDataMap()->find(name)->second;
		*fout << "========SEARCH_BP========\n";
		*fout << data->getName() << "/" << data->getCode() << "/" << data->getAuthor() << "/" << data->getYear() << "/" << data->getLoanCount() <<"\n";
		*fout << "==========================\n\n";
		fout->close();
		return true;
	}
	else return false;	
}

bool BpTree::searchRange(string start, string end) {
	
}
