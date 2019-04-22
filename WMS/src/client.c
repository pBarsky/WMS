#include "../include/client.h"
#define SEARCHCLIENT "SELECT * FROM CLIENTS WHERE NAME LIKE '' AND SURNAME LIKE '';"


Client* create_client() {
	char* tmp = NULL;
	Client* cl = malloc(sizeof(Client)); //memory for client
	int success = 0;
	puts("Enter client ID");
	if (cl != NULL) {
		cl->ID = scanInt();
		//scanf_s(" %d", &cl->ID);
		//getchar();
		printf("cl->ID = %d\n", cl->ID);
		puts("Enter name: ");
		tmp = scanString();
		cl->NAME = malloc(strlen(tmp) + 1); //memory for clients name
		if (cl->NAME != NULL) {
			strcpy_s(cl->NAME, strlen(tmp) + 1, tmp);
		}
		else { 
			exit(-1);
		}
		free(tmp);
		puts("Enter surname: ");
		tmp = scanString();
		cl->SURNAME = malloc(strlen(tmp) + 1);
		if (cl->SURNAME != NULL) {
			strcpy_s(cl->SURNAME, strlen(tmp) + 1, tmp);
		}
		else {
			exit(-1);
		}
		free(tmp);
		return cl;
	}
	else {
		perror("COULD NOT ");
		exit(-1);
	}

}

Client * create_client_fromDB(sqlite3 * db)
{
	char* tmp = NULL;
	char* name = NULL;
	char* surname = NULL;
	char** zErrMsg = NULL;
	char* sql = NULL;
	Client* cl = malloc(sizeof(Client));

	puts("Please input your name: ");
	name = scanString();
	puts("Please input your surname: ");
	surname = scanString();
	sql = malloc(strlen(SEARCHCLIENT) + strlen(name) + strlen(surname) + 1);
	if (sql != NULL) {
		snprintf(sql, strlen(sql), "SELECT * FROM CLIENTS WHERE NAME LIKE '%s' AND SURNAME LIKE '%s';", name, surname);
	}
	else {
		exit(-1);
	}
	sqlite3_exec(db, sql, client_creation_callback, cl, zErrMsg);
	return cl;
}


int client_creation_callback(Client* cl, int argc, char** argv, char** azColName) {
	printf("ID: %s\nNAME: %s\nSURNAME: %s\n", argv[0], argv[1], argv[2]);
	printf("string: %10s  strlen: %3d\n", argv[0], (int)strlen(argv[0]));
	printf("string: %10s  strlen: %3d\n", argv[1], (int)strlen(argv[1]));
	printf("string: %10s  strlen: %3d\n", argv[2], (int)strlen(argv[2]));
	return 0;
}


void free_client(Client * client) {
	free(client->NAME);
	free(client->SURNAME);
	free(client);
}