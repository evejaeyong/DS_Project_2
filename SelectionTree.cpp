#include "SelectionTree.h"
#include <queue>

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
    run[newData->getCode() / 100]->getHeap()->Insert(newData);  //heap insert

    if (run[newData->getCode() / 100]->getHeap()->getRoot()->getBookData() == newData) {
        SelectionTreeNode* Parant = run[newData->getCode() / 100]->getParent();
        while (Parant) {                                        //Compare
            if (Parant->getBookData() == NULL) {
                Parant->setBookData(newData);
            }
            else if (Parant->getBookData()->getName() > newData->getName()) {
                Parant->setBookData(newData);
            }
            else break;
            Parant = Parant->getParent();
        }
    }
    return true;
}

bool SelectionTree::Delete() {
    if (root->getBookData() == NULL) {          //if Selection Tree doesn't have Data
        return false;   
    }
    else {
        string name = root->getBookData()->getName();
        SelectionTreeNode* node = root;
        node->setBookData(NULL);
        while (node) {                          //Search while leaf Node
            if (node->getLeftChild()->getBookData()->getName() == name) node = node->getLeftChild();
            else node = node->getRightChild();

            node->setBookData(NULL);

            if (node->getHeap()) {              //Heap Delete
                node->getHeap()->Delete();
                node->setBookData(node->getHeap()->getRoot()->getBookData());

                SelectionTreeNode* Parant = node->getParent();

                while (Parant) {                //Selection Tree rearrangement
                    SelectionTreeNode* Left = Parant->getLeftChild();
                    SelectionTreeNode* Right = Parant->getRightChild();

                    if (Left->getBookData() == NULL) Parant->setBookData(Right->getBookData());
                    else if (Right->getBookData() == NULL) Parant->setBookData(Left->getBookData());
                    else if (Left->getBookData()->getName() > Right->getBookData()->getName()) Parant->setBookData(Right->getBookData());
                    else Parant->setBookData(Left->getBookData());

                    Parant = Parant->getParent();
                }
                break;
            }
        }
        return true;
    }
}

bool SelectionTree::printBookData(int bookCode) {
    LoanBookHeap* Print = run[bookCode / 100]->getHeap();
    queue<LoanBookData*> q;

    if (Print->getRoot() == NULL) return false;         //if Heap doesn't have data
    else {
        *fout << "========PRINT_ST========\n";          //Print Data
        while (Print->getRoot()) {
            LoanBookData* PopData = Print->Delete();
            q.push(PopData);                            //Heap Data Push to Queue

            *fout << PopData->getName() << "/";
            if (PopData->getCode() == 0) *fout << "00";
            *fout << PopData->getCode() << "/" << PopData->getAuthor() << "/" << 
            PopData->getYear() << "/" << PopData->getLoanCount() << "\n";
        }
        *fout << "========================\n\n";

        while (!q.empty()) {                            //Queue Data Push to Heap
            Print->Insert(q.front());
            q.pop();
        }
        return true;
    }
}