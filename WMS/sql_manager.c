#include "sql_manager.h"
#include <stdio.h>
#include "client.h"


void sql_init(sqlite3 *db) {
	char sql[] = "CREATE TABLE IF NOT EXISTS 'PRODUCTS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'QUANTITY'	INTEGER NOT NULL DEFAULT 0,\
		'CLIENT_ID'	INTEGER NOT NULL DEFAULT 0);\
		 CREATE TABLE IF NOT EXISTS 'CLIENTS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'SURNAME'	TEXT NOT NULL);";
	char *zErrMsg = 0;
	sqlite3_exec(db, sql, default_callback, 0, &zErrMsg);
	if(zErrMsg != NULL)
		printf("%s", zErrMsg);
}

int default_callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void sql_addClient(sqlite3 *db, Client *cl) {

}
