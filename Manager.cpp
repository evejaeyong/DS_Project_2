#include "Manager.h"

void Manager::run(const char* command) {
	fin.open(command);
	if(!fin) {
		flog << "File Open Error" << endl;
		return;
	}
	while (!fin.eof()) {
		string cmd;
		while (1) {
			fin >> cmd;                   //Receive commands
			if (cmd == "LOAD") LOAD();
			else if (cmd == "ADD") ADD();
			else if (cmd == "SEARCH_BP") {
				//여기 질문 답변 온 후에 구현해야 함
				string book;
				fin >> book;
				SEARCH_BP_BOOK(book);
			}
			else if (cmd == "PRINT_BP") PRINT_BP();
			else if (cmd == "PRINT_ST") PRINT_ST();
			else if (cmd == "DELETE") DELETE();
			else if (cmd == "EXIT") {
				printSuccessCode("EXIT");
				break;                      //Stop Receive commands
			}
			else {
				printErrorCode(1000);       //if invalid command, Print Error Code 1000
			}
		}
	}	
	fin.close();
	return;
}

bool Manager::LOAD() {
	ifstream fdata;
    fdata.open("loan_book.txt");                     //Open data file

    if (!fdata) {                               //if data file don't exist
        printErrorCode(100);                    //Print Error Code 100
		return false;
    }
    else if (bptree->getRoot() != NULL || stree->getRoot()->getHeap() != NULL) {        //if data already exists
        printErrorCode(100);                    //Print Error Code 100
		return false;
    }
	else {                                      //normal case
        string line;
        while (getline(fdata, line)) {          //Get one line at loan_book file
            int len = 0;
            string name, s_code, author, s_year, s_loan_count;
            int code, year, loan_count;

            while (line[len] != '\t') {          //Parsing name
                name.push_back(line[len++]);
            }
            len++;

            while (line[len] != '\t') {           //Parsing code
                s_code.push_back(line[len++]);
            }
            code = stoi(s_code);                 //string to int
            len++;

			while (line[len] != '\t') {          //Parsing author
                author.push_back(line[len++]);
            }
            len++;

            while (line[len] != '\t') {          //Parsing year
                s_year.push_back(line[len++]);
            }
            year = stoi(s_year);                 //string to int
            len++;

			while (line[len] != '\0') {          //Parsing loan count 
                s_loan_count.push_back(line[len++]);
            }
            loan_count = stoi(s_loan_count);     //string to int
            
			LoanBookData* newNode = new LoanBookData;
			newNode->setBookData(name, code, author, year);
			for (int i = 0; i < loan_count; i++) {
				newNode->updateCount();
			}
			bptree->Insert(newNode);			 //insert to bp tree
        }
		printSuccessCode("LOAD");
    }
    fdata.close();
	return true;
}

bool Manager::ADD() {
	string line;
	getline(fin, line);                //Get One line
	int len = 0;
    string name, s_code, author, s_year;
    int code, year;

	while (line[len] != '\t') {          //Parsing name
        name.push_back(line[len++]);
		if (line[len] == NULL) {        //if have less data
            printErrorCode(200);        //Print Error Code 200
            return false;
        }
	}
    len++;

    while (line[len] != '\t') {           //Parsing code
        s_code.push_back(line[len++]);
		if (line[len] == NULL) {        //if have less data
            printErrorCode(200);        //Print Error Code 200
            return false;
        }
    }
    code = stoi(s_code);                 //string to int
    len++;

	while (line[len] != '\t') {          //Parsing author
        author.push_back(line[len++]);
		if (line[len] == NULL) {        //if have less data
            printErrorCode(200);        //Print Error Code 200
            return false;
        }
    }
    len++;

    while (line[len] != '\0') {          //Parsing year
        s_year.push_back(line[len++]);
    }
	if (s_year[0] == NULL) {	        //if have less data
        printErrorCode(200);    	    //Print Error Code 200
        return false;
    }
    year = stoi(s_year);                 //string to int
            
	LoanBookData* newNode = new LoanBookData;
	newNode->setBookData(name, code, author, year);
	bptree->Insert(newNode);			 //insert to bp tree

	return true;
}

bool Manager::SEARCH_BP_BOOK(string book) {
	if (!bptree->searchBook(book)) {	//if Book Search Failed
		printErrorCode(300);
		return false;
	}
	return true;
}

bool Manager::SEARCH_BP_RANGE(string s, string e) {
	if (!bptree->searchRange(s, e)) {	//if Book Search Failed
		printErrorCode(300);
		return false;
	}
	return true;
}

bool Manager::PRINT_BP() {
	if (!bptree->PrintBook()) {			//if Data can't find
		printErrorCode(400);
		return false;
	}
	return true;
}

bool Manager::PRINT_ST() {
	int num;
	fin >> num;				//get Book Code

	if (stree->printBookData(num)) {
		return true;
	}
	else {					//if Stree Doesn't Have Data
		printErrorCode(500);
		return false;
	}
}

bool Manager::DELETE() {
	if (stree->Delete()) {
		printSuccessCode("DELETE");
		return true;
	}
	else {					//if Stree Doesn't Have Data
		printErrorCode(600);
		return false;
	}

}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "========ERROR========\n";
	flog << n << "\n";
	flog << "=====================\n\n";
}

void Manager::printSuccessCode(string success) {	//SUCCESS CODE PRINT 
	flog << "========"<< success << "========\n";
	flog << "Success" << "\n";
	flog << "====================\n\n";
}

