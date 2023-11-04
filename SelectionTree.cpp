#include "SelectionTree.h"

void SelectionTree::setTree() {
    for (int i = 0; i < 8; i++) {           //setting run
        run[i] = new SelectionTreeNode;
        run[i]->HeapInit();
    }

    root = new SelectionTreeNode;           //setting tree
    SelectionTreeNode* leftchild = new SelectionTreeNode;
    SelectionTreeNode* rightchild = new SelectionTreeNode;
    SelectionTreeNode* llchild = new SelectionTreeNode;
    SelectionTreeNode* lrchild = new SelectionTreeNode;
    SelectionTreeNode* rlchild = new SelectionTreeNode;
    SelectionTreeNode* rrchild = new SelectionTreeNode;

    root->setLeftChild(leftchild);          //level 0
    root->setRightChild(rightchild);
    leftchild->setParent(root);
    rightchild->setParent(root);

    leftchild->setLeftChild(llchild);       //level 1
    leftchild->setRightChild(lrchild);
    llchild->setParent(leftchild);
    lrchild->setParent(leftchild);

    rightchild->setLeftChild(rlchild);
    rightchild->setRightChild(rrchild);
    rlchild->setParent(rightchild);
    rrchild->setParent(rightchild);

    llchild->setLeftChild(run[0]);          //level 2
    llchild->setRightChild(run[1]);
    run[0]->setParent(llchild);
    run[1]->setParent(llchild);

    lrchild->setLeftChild(run[2]);
    lrchild->setRightChild(run[3]);
    run[2]->setParent(lrchild);
    run[3]->setParent(lrchild);

    rlchild->setLeftChild(run[4]);
    rlchild->setRightChild(run[5]);
    run[4]->setParent(rlchild);
    run[5]->setParent(rlchild);

    rrchild->setLeftChild(run[6]);
    rrchild->setRightChild(run[7]);
    run[6]->setParent(rrchild);
    run[7]->setParent(rrchild);
}

bool SelectionTree::Insert(LoanBookData* newData) {
    run[newData->getCode() / 100]->getHeap()->Insert(newData);

    
}

bool SelectionTree::Delete() {
    if (root->getBookData() == NULL) {
        return false;   
    }
    else {
        
    }
}

bool SelectionTree::printBookData(int bookCode) {
    run[bookCode / 100]->getHeap();
}