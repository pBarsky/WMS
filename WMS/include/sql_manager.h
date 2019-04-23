#pragma once
#include "../3rdparty/include/sqlite3.h"
#include "client.h"
#include "items.h"
#define CREATETABLE "CREATE TABLE IF NOT EXISTS 'ITEMS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'QUANTITY'	INTEGER NOT NULL DEFAULT 0,\
		'CLIENT_ID'	INTEGER NOT NULL DEFAULT 0);\
		INSERT INTO CLIENTS VALUES (1, 'WH', 'WH') ON CONFLICT(ID) DO UPDATE SET ID=excluded.ID;\
		 CREATE TABLE IF NOT EXISTS 'CLIENTS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'SURNAME'	TEXT NOT NULL);\
		CREATE TABLE IF NOT EXISTS 'UTILITY' (\
		'ID'	INTEGER NOT NULL PRIMARY KEY UNIQUE,\
		'LAST_CLIENT_ID'	INTEGER,\
		'LAST_ITEM_ID'	INTEGER);\
		INSERT INTO UTILITY VALUES (1, 5, 1) ON CONFLICT(ID) DO UPDATE SET ID=excluded.ID;"
#define INSERTCLIENT "INSERT INTO CLIENTS (ID, NAME, SURNAME) VALUES(, '', '');"
#define REMOVECLIENT "DELETE FROM CLIENTS WHERE ID=;"
#define UPDATECLIENT "UPDATE CLIENTS SET NAME='' WHERE ID=;"
#define SHOWCLIENT "SELECT * FROM CLIENTS WHERE ID=;"
#define SHOWALLCLIENTS "SELECT * FROM CLIENTS;"

#define INSERTITEM "INSERT INTO ITEMS (ID, NAME, QUANTITY, CLIENT_ID) VALUES(, '', , );"
#define REMOVEITEM "DELETE FROM ITEMS WHERE NAME='' AND CLIENT_ID=;"
#define REMOVEALLITEMS "DELETE FROM ITEMS WHERE CLIENT_ID=;"
#define SHOWITEM "SELECT * FROM ITEMS WHERE NAME LIKE '' AND CLIENT_ID=;"
#define UPDATEITEM "UPDATE ITEMS SET QUANTITY= WHERE ID=;"
#define SHOWALLITEMS "SELECT * FROM ITEMS;"
#define SHOWALLITEMSOFCLIENT "SELECT * FROM ITEMS WHERE CLIENT_ID=;"

#define DUMPLASTIDS "UPDATE UTILITY SET LAST_CLIENT_ID=, LAST_ITEM_ID=;"

int default_callback(void *, int, char **, char **);
int item_callback(void *, int, char **, char **);
int client_callback(void *, int, char **, char **);
int fetchIDs(int *, int, char **, char **);

void sql_init(sqlite3 *);
void sql_addClient(sqlite3 *, Client *);
void sql_removeClient(sqlite3 *, Client *);
//void sql_updateClient(sqlite3*, Client*);
void sql_showAllClients(sqlite3 *);
//void sql_showClient(sqlite3*, Client*);

void sql_addItem(sqlite3 *, Item *, Client *);
void sql_removeItem(sqlite3 *, char *, Client *);
void sql_removeAllItems(sqlite3 *, Client *);
void sql_updateItem(sqlite3 *, Item *);
//void sql_showAllItems(sqlite3*);
void sql_showAllItemsOfClient(sqlite3 *, Client *);
void sql_dump_lastIDs(sqlite3 *, int *);
void sql_showItem(sqlite3 *, Client *, char *);

void sql_setLastIDs(sqlite3 *db, int *);
