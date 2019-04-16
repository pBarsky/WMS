#include "menu.h"
int main(int argc, char* argv[]) {
	sqlite3* db;
	Client* cl = NULL;
	char* zErrMsg = 0;
	int rc;
	char finished = 0;

	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else {
		fprintf(stdout, "Opened database successfully\n");
	}

	sql_init(db);
	//drawEntryMenu();
	//getChoiceEntry(cl);
	drawMenu();
	getChoice(db, cl);
	system("pause");
	return 0;
}