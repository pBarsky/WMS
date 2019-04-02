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
#define INSERTCLIENT "INSERT INTO CLIENTS (ID, NAME, SURNAME) VALUES(, '', '');"
#define REMOVECLIENT "DELETE FROM CLIENTS WHERE ID=;"
#define SHOWCLIENT "SELECT * FROM CLIENTS WHERE ID=;"
#define SHOWALLCLIENTS "SELECT * FROM CLIENTS;"

void sql_init(sqlite3 *db) {
	char *zErrMsg = 0;
	sqlite3_exec(db, CREATETABLE, default_callback, 0, &zErrMsg);
	if (zErrMsg != NULL)
		printf("%s\n", zErrMsg);
}

int default_callback(void *notUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int client_callback(void *data, int argc, char** argv, char** azColName) {
	int i;
	// TODO: finish client callback
}

void sql_addClient(sqlite3* db, Client* cl) {
	char* sql = malloc(strlen(INSERTCLIENT) + strlen(cl->NAME) + strlen(cl->SURNAME) + intLen(cl->ID) + 1);
	int success = 0;
	char* zErrMsg;
	success = snprintf(sql, strlen(sql), "INSERT INTO CLIENTS (ID, NAME, SURNAME) VALUES(%d, \'%s\', \'%s\');", cl->ID, cl->NAME, cl->SURNAME);
	sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
	free(sql);
}

void sql_removeClient(sqlite3* db, Client* cl) {
	char* sql = malloc(strlen(REMOVECLIENT) + intLen(cl->ID) + 1);
	int success = 0;
	char* zErrMsg;
	success = snprintf(sql, strlen(sql), "DELETE FROM CLIENTS WHERE ID=%d;", cl->ID);
	sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
	free(sql);
}

void sql_showClient(sqlite3* db, Client* cl) {
	char* sql = malloc(strlen(SHOWCLIENT) + intLen(cl->ID) + 1);
	int success = 0;
	char* zErrMsg;
	success = snprintf(sql, strlen(sql), "SELECT * FROM CLIENTS WHERE ID=%d;", cl->ID);
	sqlite3_exec(db, sql, default_callback, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
	free(sql);
}

void sql_showAllClients(sqlite3* db) {
	int success = 0;
	char* zErrMsg;
	sqlite3_exec(db, SHOWALLCLIENTS, default_callback, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
}
