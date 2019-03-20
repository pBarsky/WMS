#include "items.h"

Item* create_item(int id, Client* cl) {
	char *tmp = NULL;
	Item *item = malloc(sizeof(Item)); //memory for client
	int quantity = 0;
	int success = 0;
	item->ID = id;
	puts("Enter item name: ");
	tmp = scanString(tmp);
	item->NAME = malloc(strlen(tmp) + 1); //memory for clients name
	success = strcpy_s(item->NAME, strlen(tmp) + 1, tmp);
	puts("Enter item quantity: ");
	scanf_s("%d", &quantity);
	item->QUANTITY = quantity;
	item->CLIENT_ID = cl->ID;
	return item;
}

void free_item(Item* item) {
	free(item->NAME);
	free(item);
}