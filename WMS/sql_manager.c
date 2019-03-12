#include "sql_manager.h"
#include <stdio.h>

void sql_init(sqlite3 *db) {
	const char *sql;
	char *zErrMsg = 0;

	sql = "CREATE TABLE IF NOT EXISTS 'PRODUCTS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'QUANTITY'	INTEGER NOT NULL DEFAULT 0,\
		'CLIENT_ID'	INTEGER NOT NULL DEFAULT 0);\
		 CREATE TABLE IF NOT EXISTS 'CLIENTS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'SURNAME'	TEXT NOT NULL);";
	sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if(zErrMsg != NULL)
		printf("%s", zErrMsg);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void sql_addClient(sqlite3 *db) {

}
