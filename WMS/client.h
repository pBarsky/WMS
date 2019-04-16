#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "conversions.h"

typedef struct client {
	int ID;
	char *NAME;
	char *SURNAME;
} Client;

Client* create_client();
Client* create_client_fromDB();
void free_client(Client*);