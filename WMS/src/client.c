#include "../include/client.h"

client* create_client(int* i_ds)
{
	client* cl = malloc(sizeof(client)); // memory for client
	if (cl != NULL)
	{
		cl->id = i_ds[0]++;
		puts("Enter name: ");
		char* tmp = scan_string();
		cl->name = malloc(strlen(tmp) + 1); // memory for clients name
		if (cl->name != NULL)
		{
			strcpy_s(cl->name, strlen(tmp) + 1, tmp);
		}
		else
		{
			perror("AN ERROR OCCURRED");
			exit(-1);
		}
		free(tmp);
		puts("Enter password: ");
		tmp = scan_string();
		cl->passwd = hash_password(tmp);
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
	char* z_err_msg = NULL;
	client* cl = malloc(sizeof(client));

	if (cl != NULL)
	{
		cl->name = NULL;
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}

	puts("Please input your login: ");
	char* name = scan_string();
	puts("Please input your password: ");
	char* password = scan_string();
	const int hash = hash_password(password);
	free(password);
	char* sql = malloc(strlen(SEARCHCLIENT) + strlen(name) + int_len(hash) + 1);
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

int client_creation_callback(client* cl, int argc, char** argv, char** az_col_name)
{
	cl->id = string_to_int(argv[0]);
	cl->name = malloc(strlen(argv[1]) + 1);
	if (cl->name != NULL)
	{
		strcpy_s(cl->name, strlen(argv[1]) + 1, argv[1]);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	cl->passwd = string_to_int(argv[2]);
	return 0;
}

void free_client(client* client)
{
	if (client->name != NULL)
	{
		free(client->name);
	}
	free(client);
}