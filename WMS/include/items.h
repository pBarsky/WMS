#pragma once
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SEARCHITEM "SELECT NAME, QUANTITY FROM ITEM WHERE NAME LIKE '' AND CLIENT_ID=;"

typedef struct item
{
	int id;
	char* name;
	int quantity;
	int client_id;
} item;

typedef struct item_list
{
	int size;
	item** list;
} item_list;

item_list* new_item_list();
item* create_item(client*, int*, char*);
item* create_item_from_db(sqlite3*, client* cl, char*);
int item_creation_callback(item*, int, char**, char**);
void handle_create_item_input(const char* input, item* item);
void create_item_from_input(const char* input, item* item);
void create_item_manually(item* item);

void free_item(item* item);
void free_item_list(item_list* items);
