#pragma once
#include "../3rdparty/include/sqlite3.h"
#include "conversions.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SEARCHCLIENT "SELECT NAME FROM CLIENTS WHERE NAME LIKE '';"

typedef struct client1
{
	int ID;
	char* NAME;
	int PASSWD;
} client;

client* create_client(int*);
client* create_client_from_db(sqlite3* db);
int client_creation_callback(client*, int, char**, char**);
void free_client(client*);
