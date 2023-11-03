#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {
	string name = newData->getName();
	BpTreeNode* node;
	if (root == NULL) {						//if root is NULL
		node = new BpTreeDataNode;
		node->insertDataMap(name, newData);	//Data Insert and set Root
		root = node;
		return true;
	}

	if (searchDataNode(name) != NULL) {		//if Data Node is exist
		delete newData;
		LoanBookData* data = searchDataNode(name)->getDataMap()->find(name)->second;
		data->updateCount();				//data count + 1
		if (data->getCode() < 300) {		//if delete count is full
			if (data->getLoanCount() >= 3) {
				DeleteData(name);			//delete data
				return false;
			}
		}
		else if (data->getCode() < 500){
			if (data->getLoanCount() >= 4) {
				DeleteData(name);
				return false;
			}
		}
		else {
			if (data->getLoanCount() >= 2) {
				DeleteData(name);
				return false;
			}
		}
	}
	else {									//if Data Node is not exist
		BpTreeNode* pCur = root;
		while (pCur->getMostLeftChild()) {				//while Find DataNode
			if (pCur->getIndexMap()->begin()->first > name) {
				pCur = pCur->getMostLeftChild();		//if name is small
			}
			else {										//if name is big
				map<string, BpTreeNode*>* m = pCur->getIndexMap();
				BpTreeNode* next;
				for (auto iter : *m) {					//map search
					next = iter.second;
					if (iter.first == name) break;
				}
				pCur = next;							//set next
			}
		}
		pCur->insertDataMap(name, newData);				//insert Data Map
		if (excessDataNode(pCur)) splitDataNode(pCur);	//if Data Node is full, split
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
	BpTreeNode* newDataNode = new BpTreeDataNode;

	newDataNode->setNext(pDataNode);					//set DataNode Prev, Next
	newDataNode->setPrev(pDataNode->getPrev());
	pDataNode->setPrev(newDataNode);

	while (newDataNode->getDataMap()->size() != order / 2) {	//Split Data Node
		string first = pDataNode->getDataMap()->begin()->first;
		LoanBookData* second = pDataNode->getDataMap()->begin()->second;
		pDataNode->getDataMap()->erase(first);
		newDataNode->insertDataMap(first, second);
	}

	if (pDataNode->getParent() == NULL) {						//Index Node Construct
		BpTreeNode* newIndexNode = new BpTreeIndexNode;
		newIndexNode->setMostLeftChild(newDataNode);
		newDataNode->setParent(newIndexNode);
		pDataNode->setParent(newIndexNode);

		string first = pDataNode->getDataMap()->begin()->first;
		newIndexNode->insertIndexMap(first, pDataNode);
	}
	else {														//Index node already exists
		BpTreeNode* IndexNode = pDataNode->getParent();
		if (IndexNode->getMostLeftChild() == pDataNode) IndexNode->setMostLeftChild(newDataNode);

		string first = pDataNode->getDataMap()->begin()->first;
		IndexNode->insertIndexMap(first, pDataNode);

		if (excessIndexNode(IndexNode)) splitIndexNode(IndexNode);
	}
	
	return;
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	
}

BpTreeNode* BpTree::searchDataNode(string name) {
	BpTreeNode* pCur = root;
	while (pCur->getMostLeftChild()) {				//while Find DataNode
		if (pCur->getIndexMap()->begin()->first > name) {
			pCur = pCur->getMostLeftChild();		//if name is small
		}
		else {										//if name is big
			map<string, BpTreeNode*>* m = pCur->getIndexMap();
			BpTreeNode* next;
			for (auto iter : *m) {					//map search
				next = iter.second;
				if (iter.first == name) break;
			}
			pCur = next;							//set next
		}
	}
	if (pCur->getDataMap()->find(name) == pCur->getDataMap()->end()) {
		return NULL;
	}

	return pCur;
}

bool BpTree::searchBook(string name) {
	BpTreeNode* pCur = root;
	while (pCur->getMostLeftChild()) {				//while Find DataNode
		if (pCur->getIndexMap()->begin()->first > name) {
			pCur = pCur->getMostLeftChild();		//if name is small
		}
		else {										//if name is big
			map<string, BpTreeNode*>* m = pCur->getIndexMap();
			BpTreeNode* next;
			for (auto iter : *m) {					//map search
				next = iter.second;
				if (iter.first == name) break;
			}
			pCur = next;							//set next
		}
	}
	if (pCur->getDataMap()->find(name) != pCur->getDataMap()->end()) {	//if find name
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
	BpTreeNode* pCur = root;
	while (pCur->getMostLeftChild()) {				//while Find DataNode
		if (pCur->getIndexMap()->begin()->first > start) {
			pCur = pCur->getMostLeftChild();		//if name is small
		}
		else {										//if name is big
			map<string, BpTreeNode*>* m = pCur->getIndexMap();
			BpTreeNode* next;
			for (auto iter : *m) {					//map search
				next = iter.second;
				if (iter.first == start) break;
			}
			pCur = next;							//set next
		}
	}
	//이제 범위지정이 필요함

}

void BpTree::DeleteData(string name) {

}