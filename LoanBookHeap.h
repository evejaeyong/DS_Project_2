#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"
#include <stack>

class LoanBookHeap {
private:
    LoanBookHeapNode* root;
    int datanum;

public:
    LoanBookHeap() {
        this->root = NULL;
        datanum = 0;
    }
    ~LoanBookHeap() {
        while (root != NULL) {
            Destruct();
        }
    }
    
    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    LoanBookHeapNode* getRoot() { return root; }

    void heapifyUp(LoanBookHeapNode* pN);
    void heapifyDown(LoanBookHeapNode* pN);
    
    bool Insert(LoanBookData* data);
    LoanBookData* Delete();
    void Destruct();
};