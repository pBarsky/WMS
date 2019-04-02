#pragma once
#include "sqlite3.h"
#include "client.h"
#include "items.h"

int default_callback(void*, int, char**, char**);
void sql_init(sqlite3*);
void sql_addClient(sqlite3* db, Client* cl);
void sql_removeClient(sqlite3* db, Client* cl);
void sql_updateClient(sqlite3* db, Client* cl);

void sql_addItem(sqlite3* db, Item* item);
void sql_removeItem(sqlite3* db, Item* item);
void sql_updateItem(sqlite3* db, Item* item);
