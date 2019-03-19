#include "client.h"

Client* create_client(int id) {
	char tmp[BUFFER];
	Client *cl = malloc(sizeof(Client)); //memory for client
	int success = 45;
	cl->ID = id;
	puts("Enter name: ");
	scanf_s("%s", tmp, BUFFER);
	cl->NAME = malloc(strlen(tmp) + 1); //memory for clients name
	success = strcpy_s(cl->NAME, strlen(tmp) + 1, tmp);
	printf("%d", success);
	puts("Enter surname: ");
	scanf_s("%s", tmp, BUFFER);
	cl->SURNAME = malloc(strlen(tmp) + 1);
	strcpy_s(cl->SURNAME, strlen(tmp) + 1, tmp);
	return cl;
}

void free_client(Client* client) {
	free(client->NAME);
	free(client->SURNAME);
	free(client);
}