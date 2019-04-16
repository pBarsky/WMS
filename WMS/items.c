#include "items.h"

Item* create_item(Client* cl) {
	char *tmp = NULL;
	Item *item = malloc(sizeof(Item)); //memory for client
	//int quantity = 0;
	int success = 0;
	puts("Enter item ID");
	item->ID = scanInt();
	puts("Enter item name: ");
	tmp = scanString();
	item->NAME = malloc(strlen(tmp) + 1); //memory for clients name
	success = strcpy_s(item->NAME, strlen(tmp) + 1, tmp);
	free(tmp);
	puts("Enter item quantity: ");
	//scanf_s("%d", &quantity);
	//item->QUANTITY = quantity;
	item->QUANTITY = scanInt();
	item->CLIENT_ID = cl->ID;
	return item;
}

void free_item(Item* item) {
	free(item->NAME);
	free(item);
}