#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
    datanum++;
    if (root == NULL) {     //if root is NULL
        root = pN;
        return;
    }
    stack<int> s;
    int pos = datanum;

    while (pos) {           //Search Position
        s.push(pos % 2);
        pos = pos / 2;
    }
    s.pop();

    LoanBookHeapNode* node = root;
    while (node) {          //Search Position
        int num = s.top();
        if (num == 0) {
            if (node->getLeftChild() == NULL) break;
            else {
                node = node->getLeftChild();
                s.pop();
            }
        }
        else {
            if (node->getRightChild() == NULL) break;
            else {
                node = node->getRightChild();
                s.pop();
            }
        }
    }
    

    if (s.top() == 0) {             //Insert Node
        node->setLeftChild(pN);
        pN->setParent(node);
        node = node->getLeftChild();
    }
    else {
        node->setRightChild(pN);
        pN->setParent(node);
        node = node->getRightChild();
    }

    while (node != root) {          //Sort
        if (node->getParent()->getBookData()->getName() > node->getBookData()->getName()) {
            LoanBookData* temp = node->getParent()->getBookData();
            node->getParent()->setBookData(node->getBookData());
            node->setBookData(temp);
        }
        else break;
    }

}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
    root->setBookData(pN->getBookData());       //root Data Setting
    if (pN != root) {                           //Delete Node
        LoanBookHeapNode* pNParant = pN->getParent();
        if (pNParant->getLeftChild() == pN) pNParant->setLeftChild(NULL);
        else pNParant->setRightChild(NULL);
    }
    else {
        root = NULL;
    }
    delete pN;

    LoanBookHeapNode* node = root;
    while (1) {                                 //Sort
        string name = node->getBookData()->getName();
        if (node->getLeftChild() == NULL) break;
        else if (node->getLeftChild()->getBookData()->getName() < name) {
            LoanBookData* temp = node->getBookData();
            node->setBookData(node->getLeftChild()->getBookData());
            node->getLeftChild()->setBookData(temp);
        }
        else if (node->getRightChild() == NULL) break;
        else if (node->getRightChild()->getBookData()->getName() < name) {
            LoanBookData* temp = node->getBookData();
            node->setBookData(node->getRightChild()->getBookData());
            node->getRightChild()->setBookData(temp);
        }
        else break;
    }
    datanum--;
    return;
}

bool LoanBookHeap::Insert(LoanBookData* data) {
    LoanBookHeapNode* node = new LoanBookHeapNode;  //Construct new Node
    node->setBookData(data);                        //Data Setting
    heapifyUp(node);                                //insert
    return true;
}

LoanBookData* LoanBookHeap::Delete() {
    LoanBookData* Data = root->getBookData();       //Get Data

    stack<int> s;
    int pos = datanum;

    while (pos) {
        s.push(pos % 2);
        pos = pos / 2;
    }
    s.pop();

    LoanBookHeapNode* node = root;
    while (!s.empty()) {
        int num = s.top();
        if (num == 0) {
            node = node->getLeftChild();
            s.pop(); 
        }
        else {
            node = node->getRightChild();
            s.pop();
        }    
    }
    heapifyDown(node);
    return Data;
}

void LoanBookHeap::Destruct() {
    LoanBookData* Data = Delete();
    delete Data;
    return;
}