#pragma once
#include "sqlite3.h"
#include "client.h"
#include "items.h"

int default_callback(void*, int, char**, char**);
void sql_init(sqlite3*);
void sql_addClient(sqlite3*, Client*);
void sql_removeClient(sqlite3*, Client*);
void sql_updateClient(sqlite3*, Client*);
void sql_showAllClients(sqlite3*);
void sql_showClient(sqlite3*, Client*);

void sql_addItem(sqlite3*, Item*);
void sql_removeItem(sqlite3*, Item*);
void sql_updateItem(sqlite3*, Item*);
