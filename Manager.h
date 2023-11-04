#pragma once
#include "SelectionTree.h"
#include "BpTree.h"

class Manager {
private:
	char* cmd;
	BpTree* bptree;
	SelectionTree* stree;
	
public:
	Manager(int bpOrder) {		//constructor
		flog.open("log.txt");
		bptree = new BpTree(&flog, bpOrder);
		stree = new SelectionTree(&flog);
	}


	~Manager() {				//destructor
		flog.close();
		delete bptree;
		delete stree;
	}

	ifstream fin;
	ofstream flog;
	

	void run(const char* command);
	bool LOAD();
	bool ADD();

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST();

	bool DELETE();

	void printErrorCode(int n);
	void printSuccessCode(string success);

};

