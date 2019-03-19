#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define BUFFER 128

typedef struct client {
	int ID;
	char *NAME;
	char *SURNAME;
} Client;

Client* create_client(int);
void free_client(Client*);