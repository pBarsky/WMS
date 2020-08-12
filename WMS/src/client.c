#include "../include/client.h"

client* create_client(int* i_ds)
{
	char* tmp = NULL;
	char* hexDump = malloc(41);
	char* binDump = malloc(21);
	client* cl = malloc(sizeof(client)); // memory for client
	int success = 0;
	if (cl != NULL)
	{
		cl->ID = i_ds[0]++;
		puts("Enter name: ");
		tmp = scan_string();
		cl->NAME = malloc(strlen(tmp) + 1); // memory for clients name
		if (cl->NAME != NULL)
		{
			strcpy_s(cl->NAME, strlen(tmp) + 1, tmp);
		}
		else
		{
			perror("AN ERROR OCCURRED");
			exit(-1);
		}
		free(tmp);
		puts("Enter password: ");
		tmp = scan_string();
		cl->PASSWD = hash_password(tmp);
		free(tmp);
	}
	else
	{
		perror("AN ERROR OCCURED");
		exit(-1);
	}
	return cl;
}

client* create_client_from_db(sqlite3* db)
{
	char* name = NULL;
	char* password = NULL;
	char* z_err_msg = NULL;
	char* sql = NULL;
	int hash = 0;
	client* cl = malloc(sizeof(client));
	if (cl != NULL)
	{
		cl->NAME = NULL;
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}

	puts("Please input your login: ");
	name = scan_string();
	puts("Please input your password: ");
	password = scan_string();
	hash = hash_password(password);
	free(password);
	sql = malloc(strlen(SEARCHCLIENT) + strlen(name) + int_len(hash) + 1);
	if (sql != NULL)
	{
		snprintf(sql, strlen(sql), "SELECT * FROM CLIENTS WHERE NAME='%s' AND PASSWD=%d;", name, hash);
	}
	else
	{
		perror("AN ERROR OCCURED");
		exit(-1);
	}
	sqlite3_exec(db, sql, client_creation_callback, cl, &z_err_msg);
	return cl;
}

int client_creation_callback(client* cl, int argc, char** argv, char** azColName)
{
	cl->ID = string_to_int(argv[0]);
	cl->NAME = malloc(strlen(argv[1]) + 1);
	if (cl->NAME != NULL)
	{
		strcpy_s(cl->NAME, strlen(argv[1]) + 1, argv[1]);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	cl->PASSWD = string_to_int(argv[2]);
	return 0;
}

void free_client(client* client)
{
	if (client->NAME != NULL)
	{
		free(client->NAME);
	}
	free(client);
}