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
#define UPDATECLIENT "UPDATE CLIENTS SET NAME='' WHERE ID=;"
#define SHOWCLIENT "SELECT * FROM CLIENTS WHERE ID=;"
#define SHOWALLCLIENTS "SELECT * FROM CLIENTS;"

#define INSERTITEM "INSERT INTO ITEMS (ID, NAME, QUANTITY, CLIENT_ID) VALUES(, '', , );"
#define REMOVEITEM "DELETE FROM ITEMS WHERE ID=;"
#define SHOWITEM "SELECT * FROM ITEMS WHERE ID=;"
#define SHOWALLITEMS "SELECT * FROM ITEMS;"
#define SHOWALLITEMSOFCLIENT "SELECT * FROM ITEMS WHERE CLIENT_ID=;"


void sql_init(sqlite3* db) {
	char* zErrMsg = 0;
	sqlite3_exec(db, CREATETABLE, default_callback, 0, &zErrMsg);
	if (zErrMsg != NULL)
		printf("%s\n", zErrMsg);
}

int default_callback(void* data, int argc, char** argv, char** azColName) {
	int i;
	if (argc == 0) {
		puts("No data to show.");
	}
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int client_creation_callback() {
	return 0;
}

int client_callback(void* data, int argc, char** argv, char** azColName) {
	printf("ID: %s\tName: %s\tSurname: %s\n", argv[0], argv[1], argv[2]);
	return 0;
}

void sql_addClient(sqlite3 * db, Client * cl) {
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

void sql_removeClient(sqlite3 * db, Client * cl) {
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

void sql_updateClient(sqlite3 * db, Client * cl) {
	char* sql = malloc(strlen(UPDATECLIENT) + intLen(cl->ID) + 1);
	int success = 0;
	char* zErrMsg, *newName, *newSurname;
	puts("Please enter new name for the client.");
	newName = scanString();
	puts("Please enter new surname for the client");
	newSurname = scanString();

	success = snprintf(sql, strlen(sql), "UPDATE CLIENTS SET NAME='%s', SURNAME='%s' WHERE ID=%d;", newName, newSurname, cl->ID);
	sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
	free(sql);
}

void sql_showClient(sqlite3 * db, Client * cl) {
	char* sql = malloc(strlen(SHOWCLIENT) + intLen(cl->ID) + 1);
	int success = 0;
	char* zErrMsg;
	success = snprintf(sql, strlen(sql), "SELECT * FROM CLIENTS WHERE ID=%d;", cl->ID);
	sqlite3_exec(db, sql, client_callback, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
	free(sql);
}

void sql_showAllClients(sqlite3 * db) {
	int success = 0;
	char* zErrMsg;
	sqlite3_exec(db, SHOWALLCLIENTS, default_callback, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
}


void sql_addItem(sqlite3 * db, Item * it, Client * cl) {
	char* sql = malloc(strlen(INSERTITEM) + intLen(it->ID) + strlen(it->NAME) + intLen(it->QUANTITY) + intLen(cl->ID) + 1);
	int success = 0;
	char* zErrMsg;
	success = snprintf(sql, strlen(sql), "INSERT INTO ITEMS (ID, NAME, QUANTITY, CLIENT_ID) VALUES(%d, '%s', %d, %d);", it->ID, it->NAME, it->QUANTITY, cl->ID);
	sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
	free(sql);
}

void sql_removeItem(sqlite3 * db, Item * it) {
	char* sql = malloc(strlen(REMOVEITEM) + intLen(it->ID) + 1);
	char* zErrMsg;
	int success;
	success = snprintf(sql, strlen(sql), "DELETE FROM ITEMS WHERE ID=%d;", it->ID);
	sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
	free(sql);
}

void sql_showItem(sqlite3 * db, Item * it) {
	char* sql = malloc(strlen(SHOWITEM) + intLen(it->ID) + 1);
	char* zErrMsg;
	int success;
	success = snprintf(sql, strlen(sql), "SELET * FROM ITEM WHERE ID=%d;", it->ID);
	sqlite3_exec(db, sql, default_callback, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
	free(sql);
}

void sql_showAllItems(sqlite3 * db) {
	char* zErrMsg;
	int success = 0;
	sqlite3_exec(db, SHOWALLCLIENTS, default_callback, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
}

void sql_showAllItemsOfClient(sqlite3 * db, Client * cl) {
	char* sql = malloc(strlen(SHOWALLITEMSOFCLIENT) + intLen(cl->ID) + 1);
	char* zErrMsg;
	int success = 0;
	success = snprintf(sql, strlen(sql), "SELECT * FROM ITEMS WHERE CLIENT_ID=%d;", cl->ID);
	sqlite3_exec(db, sql, default_callback, 0, &zErrMsg);
	if (zErrMsg) {
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
	free(sql);
}
