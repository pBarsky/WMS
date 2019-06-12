#pragma once
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SEARCHITEM "SELECT NAME, QUANTITY FROM ITEM WHERE NAME LIKE '' AND CLIENT_ID=;"

typedef struct item {
  int ID;
  char *NAME;
  int QUANTITY;
  int CLIENT_ID;
} Item;

typedef struct itemList {
  int size;
  Item **list;
} ItemList;

Item *create_item(Client *, int *, char*);
Item *create_item_fromDB(sqlite3 *, Client* cl, char*);
int item_creation_callback(Item *, int, char **, char **);

void free_item(Item *item);