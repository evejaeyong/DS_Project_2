#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include "SelectionTree.h"
#include <fstream>
#include <iostream>
using namespace std;

class BpTree {
private:
	BpTreeNode* root;
	int	order;		// m children
	ofstream* fout;
	SelectionTree* stree;

public:
	BpTree(ofstream *fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	
	~BpTree() {
		BpTreeNode* pCur = root;
		while (pCur->getMostLeftChild()) pCur = pCur->getMostLeftChild();

		BpTreeNode* del = pCur;
		pCur = pCur->getNext();
		while (del->getDataMap()->size()) {
			DeleteData(del->getDataMap()->begin()->first);
		}
	}

	/* essential */
	bool		Insert(LoanBookData* newData);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(string name);

	bool searchBook(string name);
	bool searchRange(string start, string end);

	void SetSTree(SelectionTree* stree) { this->stree = stree; }
	bool PrintBook();
	void DeleteData(string name);
};

#endif
