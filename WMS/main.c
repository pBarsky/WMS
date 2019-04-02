#include "conversions.h"
#include "menu.h"
int main(int argc, char* argv[]) {
	sqlite3 *db;
	Client *cl;
	Item *item;
	char *zErrMsg = 0;
	int rc;
	/* Open database */
	rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else {
		fprintf(stdout, "Opened database successfully\n");
	}

	if (rc != SQLITE_OK) {
		fprintf(stdout, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}
	drawMenu(0);
	sql_init(db);
	//sqlite3_exec(db, "SELECT * FROM CLIENTS", default_callback, 0, &zErrMsg);
	getChoice(db);
	system("pause");;
	return 0;
}