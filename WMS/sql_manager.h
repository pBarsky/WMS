#pragma once
#include "sqlite3.h"

int callback(void*, int, char**, char**);
void sql_init(sqlite3*);
void sql_addClient(sqlite3*);