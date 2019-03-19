#pragma once
#include "sqlite3.h"
#include "client.h"

int default_callback(void*, int, char**, char**);
void sql_init(sqlite3*);
void sql_addClient(sqlite3* db, Client* cl);