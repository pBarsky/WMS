#include "client.h"

Client* create_client() {
	char *tmp = NULL;
	Client *cl = malloc(sizeof(Client)); //memory for client
	int success = 0;
	puts("Enter client ID");
	cl->ID = scanInt();
	//scanf_s(" %d", &cl->ID);
	//getchar();
	printf("cl->ID = %d\n", cl->ID);
	puts("Enter name: ");
	tmp = scanString();
	cl->NAME = malloc(strlen(tmp) + 1); //memory for clients name
	success = strcpy_s(cl->NAME, strlen(tmp) + 1, tmp);
	free(tmp);
	puts("Enter surname: ");
	tmp = scanString();
	cl->SURNAME = malloc(strlen(tmp) + 1);
	strcpy_s(cl->SURNAME, strlen(tmp) + 1, tmp);
	free(tmp);
	return cl;
}

Client* create_client_fromDB() {
	return 0;
}

void free_client(Client* client) {
	free(client->NAME);
	free(client->SURNAME);
	free(client);
}