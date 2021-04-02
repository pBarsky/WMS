#pragma once
#include "../3rdparty/include/sqlite3.h"
#include "client.h"
#include "items.h"
#define CREATETABLE "CREATE TABLE IF NOT EXISTS 'ITEMS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'QUANTITY'	INTEGER NOT NULL DEFAULT 0,\
		'CLIENT_ID'	INTEGER NOT NULL DEFAULT 0);\
		 CREATE TABLE IF NOT EXISTS 'CLIENTS' (\
		'ID'	    INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,\
		'NAME'	    TEXT NOT NULL,\
		'PASSWD'	INTEGER NOT NULL);\
        INSERT INTO CLIENTS VALUES (1, 'WH', 159) ON CONFLICT(ID) DO UPDATE SET ID=excluded.ID;\
		CREATE TABLE IF NOT EXISTS 'UTILITY' (\
		'ID'	INTEGER NOT NULL PRIMARY KEY UNIQUE,\
		'LAST_CLIENT_ID'	INTEGER,\
		'LAST_ITEM_ID'	INTEGER);\
		INSERT INTO UTILITY VALUES (1, 2, 1) ON CONFLICT(ID) DO UPDATE SET ID=excluded.ID;"
#define INSERTCLIENT "INSERT INTO CLIENTS (ID, NAME, PASSWD) VALUES(, '', );"
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

int default_callback(void*, int, char**, char**);
int item_callback(void*, int, char**, char**);
int item_list_callback(item_list*, int, char**, char**);
int client_callback(void*, int, char**, char**);
int fetch_ids(int*, int, char**, char**);

void sql_init(sqlite3*);
void sql_add_client(sqlite3*, client*);
void sql_remove_client(sqlite3*, client*);
void sql_show_all_clients(sqlite3*);

void sql_add_item(sqlite3*, item*, client*);
void sql_remove_item(sqlite3*, char*, client*);
void sql_remove_all_items(sqlite3*, client*);
void sql_update_item(sqlite3*, item*);
void sql_show_all_items_of_client(sqlite3*, client*, item_list*);
void sql_dump_last_ids(sqlite3*, int*);
void sql_show_item(sqlite3*, client*, char*);

void sql_set_last_ids(sqlite3* db, int*);
