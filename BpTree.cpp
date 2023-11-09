#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {
	string name = newData->getName();
	BpTreeNode* node;
	if (root == NULL) {						//if root is NULL
		root = new BpTreeDataNode;
		root->insertDataMap(name, newData);	//Data Insert and set Root
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
		else if (data->getCode() < 500) {
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
				BpTreeNode* next = NULL;
				for (auto iter : *m) {					//map search
					if (iter.first > name) break;
					next = iter.second;
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
	if (pDataNode->getPrev()) pDataNode->getPrev()->setNext(newDataNode);
	pDataNode->setPrev(newDataNode);

	while (newDataNode->getDataMap()->size() < order / 2) {		//Split Data Node
		string first = pDataNode->getDataMap()->begin()->first;
		LoanBookData* second = pDataNode->getDataMap()->begin()->second;
		pDataNode->deleteMap(first);
		newDataNode->insertDataMap(first, second);
	}

	if (pDataNode->getParent() == NULL) {						//Index Node Construct
		BpTreeNode* newIndexNode = new BpTreeIndexNode;
		newIndexNode->setMostLeftChild(newDataNode);
		newDataNode->setParent(newIndexNode);
		pDataNode->setParent(newIndexNode);

		string first = pDataNode->getDataMap()->begin()->first;
		newIndexNode->insertIndexMap(first, pDataNode);
		if (pDataNode == root) root = newIndexNode;
	}
	else {														//Index node already exists
		BpTreeNode* IndexNode = pDataNode->getParent();
		newDataNode->setParent(IndexNode);
		if (IndexNode->getIndexMap()->find(newDataNode->getDataMap()->begin()->first) != IndexNode->getIndexMap()->end()) {
			IndexNode->deleteMap(newDataNode->getDataMap()->begin()->first);
			IndexNode->insertIndexMap(newDataNode->getDataMap()->begin()->first, newDataNode);
		}

		if (IndexNode->getMostLeftChild() == pDataNode) IndexNode->setMostLeftChild(newDataNode);

		string first = pDataNode->getDataMap()->begin()->first;
		IndexNode->insertIndexMap(first, pDataNode);

		if (excessIndexNode(IndexNode)) splitIndexNode(IndexNode);
	}

	return;
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	BpTreeNode* newIndexChild = new BpTreeIndexNode;

	while (newIndexChild->getIndexMap()->size() < order / 2) {	//Split Child Node
		string first = pIndexNode->getIndexMap()->begin()->first;
		BpTreeNode* second = pIndexNode->getIndexMap()->begin()->second;
		pIndexNode->deleteMap(first);
		newIndexChild->insertIndexMap(first, second);
		second->setParent(newIndexChild);
	}

	if (pIndexNode->getParent() == NULL) {						//new Parant Index Node Construct
		BpTreeNode* newIndexParant = new BpTreeIndexNode;
		newIndexParant->setMostLeftChild(newIndexChild);
		newIndexChild->setParent(newIndexParant);
		newIndexChild->setMostLeftChild(pIndexNode->getMostLeftChild());
		newIndexChild->getMostLeftChild()->setParent(newIndexChild);
		pIndexNode->setMostLeftChild(pIndexNode->getIndexMap()->begin()->second);
		pIndexNode->setParent(newIndexParant);

		string first = pIndexNode->getIndexMap()->begin()->first;
		newIndexParant->insertIndexMap(first, pIndexNode);
		pIndexNode->deleteMap(first);
		if (pIndexNode == root) root = newIndexParant;
	}
	else {														//if Parant Index node already exists
		BpTreeNode* IndexParant = pIndexNode->getParent();
		newIndexChild->setParent(IndexParant);
		newIndexChild->setMostLeftChild(pIndexNode->getMostLeftChild());
		newIndexChild->getMostLeftChild()->setParent(newIndexChild);
		pIndexNode->setMostLeftChild(pIndexNode->getIndexMap()->begin()->second);

		map<string, BpTreeNode*>* m = IndexParant->getIndexMap();
		for (auto iter : *m) {
			if (iter.second == pIndexNode) {
				IndexParant->deleteMap(iter.first);
				IndexParant->insertIndexMap(iter.first, newIndexChild);
				break;
			}
		}

		if (IndexParant->getMostLeftChild() == pIndexNode) IndexParant->setMostLeftChild(newIndexChild);

		string first = pIndexNode->getIndexMap()->begin()->first;
		IndexParant->insertIndexMap(first, pIndexNode);
		pIndexNode->deleteMap(first);

		if (excessIndexNode(IndexParant)) splitIndexNode(IndexParant);
	}

	return;

}

BpTreeNode* BpTree::searchDataNode(string name) {
	BpTreeNode* pCur = root;
	while (pCur->getMostLeftChild()) {				//while Find DataNode
		if (pCur->getIndexMap()->begin()->first > name) {
			pCur = pCur->getMostLeftChild();		//if name is small
		}
		else {										//if name is big
			map<string, BpTreeNode*>* m = pCur->getIndexMap();
			BpTreeNode* next = NULL;
			for (auto iter : *m) {					//map search
				if (iter.first > name) break;
				next = iter.second;
			}
			pCur = next;							//set next
		}
	}
	if (pCur->getDataMap()->find(name) == pCur->getDataMap()->end()) {	//if Can't Find
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
			BpTreeNode* next = NULL;
			for (auto iter : *m) {					//map search
				if (iter.first > name) break;
				next = iter.second;
			}
			pCur = next;							//set next
		}
	}
	if (pCur->getDataMap()->find(name) != pCur->getDataMap()->end()) {	//if find name
		LoanBookData* data = pCur->getDataMap()->find(name)->second;
		*fout << "========SEARCH_BP========\n";
		*fout << data->getName() << "/";
		if (data->getCode() == 0) *fout << "00";
		*fout << data->getCode() << "/" << data->getAuthor() << "/" << data->getYear() << "/" << data->getLoanCount() << "\n";
		*fout << "=========================\n\n";
		return true;
	}
	else return false;
}

bool BpTree::searchRange(string start, string end) {
	BpTreeNode* pCur = root;
	bool check = false;
	while (pCur->getMostLeftChild()) {				//while Find DataNode
		if (pCur->getIndexMap()->begin()->first[0] > start[0]) {
			pCur = pCur->getMostLeftChild();		//if name is small
		}
		else {										//if name is big
			map<string, BpTreeNode*>* m = pCur->getIndexMap();
			BpTreeNode* next = NULL;
			for (auto iter : *m) {					//map search
				if (iter.first[0] > start[0]) break;
				next = iter.second;
			}
			pCur = next;							//set next
		}
	}

	BpTreeNode* pCheck = pCur;
	bool ch = false;								//if can't find data
	while (pCheck) {
		for (auto iter : *pCheck->getDataMap()) {
			if (iter.first[0] > end[0]) break;
			else if (iter.first[0] >= start[0]) {
				ch = true;
			}
		}
		pCheck = pCheck->getNext();
		if (pCheck->getDataMap()->begin()->first[0] > end[0]) break;
		if (ch) break;
	}
	
	if (!ch) return false;

	*fout << "========SEARCH_BP========\n";
	while (pCur != NULL) {
		for (auto iter : *pCur->getDataMap()) {
			if (iter.first[0] >= start[0] && iter.first[0] <= end[0]) {		//Outputting data in range
				*fout << iter.second->getName() << "/";
				if (iter.second->getCode() == 0) *fout << "00";
				*fout << iter.second->getCode() << "/" << iter.second->getAuthor() << "/"
					<< iter.second->getYear() << "/" << iter.second->getLoanCount() << "\n";
			}
			if (iter.first[0] >= end[0]) check = true;				//When the string exceeds end
		}
		if (check) break;
		pCur = pCur->getNext();
	}

	*fout << "=========================\n\n";
	return true;
}

bool BpTree::PrintBook() {
	if (root == NULL) return false;				//if Tree Doesn't have node, return false
	else {
		BpTreeNode* Print = root;
		while (Print->getMostLeftChild()) {		//go to list's First Node
			Print = Print->getMostLeftChild();
		}
		*fout << "========PRINT_BP========\n";
		while (Print != NULL) {							//Print All Node
			for (auto iter : *Print->getDataMap()) {	//Print All map's Value
				*fout << iter.second->getName() << "/";
				if (iter.second->getCode() == 0) *fout << "00";
				*fout << iter.second->getCode() << "/" << iter.second->getAuthor() << "/"
					<< iter.second->getYear() << "/" << iter.second->getLoanCount() << "\n";
			}
			Print = Print->getNext();					//go to next node
		}
		*fout << "========================\n\n";
		return true;
	}
}

void BpTree::DeleteData(string name) {
	BpTreeNode* delNode = searchDataNode(name);
	LoanBookData* data = delNode->getDataMap()->find(name)->second;
	delNode->getDataMap()->erase(name);
	//딜리트 전체 추가해야 함


	stree->Insert(data);
}

void BpTree::Destruct(BpTreeNode* delNode) {
	if (delNode == NULL) return;
	if (delNode->getMostLeftChild()) {
		Destruct(delNode->getMostLeftChild());
		while (delNode->getIndexMap()->size()) {
			Destruct(delNode->getIndexMap()->begin()->second);
			delNode->deleteMap(delNode->getIndexMap()->begin()->first);
		}
	}
	else {
		while (delNode->getDataMap()->size()) {
			delete delNode->getDataMap()->begin()->second;
			delNode->deleteMap(delNode->getDataMap()->begin()->first);
		}
	}
	
	delete delNode;
}