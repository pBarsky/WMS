#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
typedef struct item {
  int ID;
  char* NAME;
  int QUANTITY;
  int CLIENT_ID;
} Item;

Item* create_item(Client*, int* IDs);
void free_item(Item* item);