#pragma once
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SEARCHITEM "SELECT * FROM ITEM WHERE NAME LIKE '' AND CLIENT_ID=;"

typedef struct item {
  int ID;
  char *NAME;
  int QUANTITY;
  int CLIENT_ID;
} Item;

Item *create_item(Client *, int *);
Item *create_item_fromDB(sqlite3 *, Client* cl, char*);
int item_creation_callback(Item *, int, char **, char **);

void free_item(Item *item);