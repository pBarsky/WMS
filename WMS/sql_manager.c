#include "sql_manager.h"
#include "client.h"
#define CREATETABLE "CREATE TABLE IF NOT EXISTS 'ITEMS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'QUANTITY'	INTEGER NOT NULL DEFAULT 0,\
		'CLIENT_ID'	INTEGER NOT NULL DEFAULT 0);\
		 CREATE TABLE IF NOT EXISTS 'CLIENTS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'SURNAME'	TEXT NOT NULL);"

void sql_init(sqlite3 *db) {
	/*char sql[] = "CREATE TABLE IF NOT EXISTS 'ITEMS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'QUANTITY'	INTEGER NOT NULL DEFAULT 0,\
		'CLIENT_ID'	INTEGER NOT NULL DEFAULT 0);\
		 CREATE TABLE IF NOT EXISTS 'CLIENTS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'SURNAME'	TEXT NOT NULL);";*/
	char *zErrMsg = 0;
	sqlite3_exec(db, CREATETABLE, default_callback, 0, &zErrMsg);
	if (zErrMsg != NULL)
		printf("%s\n", zErrMsg);
}

int default_callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void sql_addClient(sqlite3* db, Client* cl) {
	char* sql = malloc(56 + strlen(cl->NAME) + strlen(cl->SURNAME) + numberLength(cl->ID) + 2);
	int succes = 0;
	char* zErrMsg = 0;
	size_t b = 0;
	b = strlen(sql);
	printf("b = %d\n", b);
	succes = snprintf(sql, b, "INSERT INTO CLIENTS (ID, NAME, SURNAME) VALUES(%d, \'%s\', \'%s\');", cl->ID, cl->NAME, cl->SURNAME);
	printf("succes=%d\n", succes);
	printf("sql = %s", sql);
	sqlite3_exec(db, sql, default_callback, 0, &zErrMsg);
	sqlite3_free(zErrMsg);
	free(sql);
}

void sql_removeClient(sqlite3* db, Client* cl) {
	char* sql = malloc(strlen("DELETE FROM CLIENTS WHERE ID=") + numberLength(cl->ID) + 1);
}
