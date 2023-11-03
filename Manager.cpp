#include "Manager.h"

void Manager::run(const char* command) {
	fin.open(command);
	if(!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
	while (!fin.eof())
	{
		/* You must fill here */
	}	
	fin.close();
	return;
}

bool Manager::LOAD() {
	return true;
}

bool Manager::ADD() {
	
	return true;
}

bool Manager::SEARCH_BP_BOOK(string book) {
	
}

bool Manager::SEARCH_BP_RANGE(string s, string e) {
	
}

bool Manager::PRINT_BP() {
	
}

bool Manager::PRINT_ST() {

}

bool Manager::DELETE() {

}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "========ERROR========\n";
	flog << n << "\n";
	flog << "======================\n\n";
}

void Manager::printSuccessCode(string success) {	//SUCCESS CODE PRINT 
	flog << "=======================" << "\n";
	flog << "Success" << "\n";
	flog << "=======================" << "\n\n";
}

