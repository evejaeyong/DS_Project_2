#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>

class SelectionTree {
private:
    SelectionTreeNode* root;
    ofstream* fout;
    SelectionTreeNode* run[8];

public:
    SelectionTree(ofstream* fout) {
        this->root = NULL;
        this->fout = fout;
        setTree();
    }

    ~SelectionTree() {

    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    void setTree();

    bool Insert(LoanBookData* newData);
    bool Delete();
    bool printBookData(int bookCode);
};