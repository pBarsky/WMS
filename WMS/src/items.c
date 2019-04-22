#include "../include/items.h"

Item* create_item(Client* cl) {
	char *tmp = NULL;
	Item *item = malloc(sizeof(Item)); //memory for client
	puts("Enter item ID");
	if (item != NULL)
	{
		item->ID = scanInt();
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}

	puts("Enter item name: ");
	tmp = scanString();
	item->NAME = malloc(strlen(tmp) + 1); //memory for clients name
	if (item->NAME != NULL)
	{
		strcpy_s(item->NAME, strlen(tmp) + 1, tmp);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	free(tmp);
	puts("Enter item quantity: ");
	item->QUANTITY = scanInt();
	item->CLIENT_ID = cl->ID;
	return item;
}

void free_item(Item* item) {
	free(item->NAME);
	free(item);
}