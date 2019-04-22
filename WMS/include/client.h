#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "conversions.h"
#include "../3rdparty/include/sqlite3.h"

typedef struct client {
	int ID;
	char *NAME;
	char *SURNAME;
} Client;

Client* create_client();
Client* create_client_fromDB(sqlite3* db);
int client_creation_callback(Client* cl, int argc, char** argv, char** azColName);
void free_client(Client*);