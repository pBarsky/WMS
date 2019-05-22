#pragma once
#include "../3rdparty/include/sqlite3.h"
#include "../3rdparty/include/sha1.h"
#include "conversions.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SEARCHCLIENT "SELECT * FROM CLIENTS WHERE NAME='' AND SURNAME='';"

typedef struct client {
  int ID;
  char *NAME;
  char *PASSWD;
} Client;

Client *create_client(int *);
Client *create_client_fromDB(sqlite3 *db);
int client_creation_callback(Client *, int, char **, char **);
void free_client(Client *);