#include "../include/sql_manager.h"

void sql_init(sqlite3* db)
{
	char* z_err_msg = 0;
	sqlite3_exec(db, CREATETABLE, NULL, 0, &z_err_msg);
	if (z_err_msg != NULL)
	{
		printf("%s\n", z_err_msg);
	}
}

int default_callback(void* data, const int argc, char** argv, char** az_col_name)
{
	for (int i = 1; i < argc; i++)
	{
		printf("|| %10s = %12s|| \n", az_col_name[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n\n");
	return 0;
}

int item_list_callback(item_list* data, int argc, char** argv, char** az_colname)
{
	item* it = malloc(sizeof(item));
	if (it == NULL)
	{
		perror("AN ERROR OCCURED");
		exit(-1);
	}
	it->id = string_to_int(argv[0]);
	it->name = malloc(strlen(argv[1]) + 1);
	if (it->name == NULL)
	{
		perror("AN ERROR OCCURED");
		exit(-1);
	}
	strcpy_s(it->name, strlen(argv[1]) + 1, argv[1]);
	it->quantity = string_to_int(argv[2]);
	it->client_id = string_to_int(argv[3]);
	data->size++;
	item** old_list = data->list;
	data->list = realloc(data->list, data->size * sizeof(item));
	if (data->list == NULL)
	{
		for (int i = 0; i < data->size - 1; i++)
		{
			free_item(old_list[i]);
		}
		perror("AN ERROR OCCURED");
		exit(-1);
	}
	data->list[data->size - 1] = it;
	return 0;
}

int item_callback(void* data, int argc, char** argv, char** az_col_name)
{
	printf("|| %10s = %12s|| \n", az_col_name[1], argv[1] ? argv[1] : "NULL");
	printf("|| %10s = %12s|| \n", az_col_name[2], argv[2] ? argv[2] : "NULL");
	printf("\n\n");
	return 0;
}

int client_callback(void* data, int argc, char** argv, char** azColName)
{
	printf("||ID: %4s\tName: %12s||\n", argv[0], argv[1]);
	return 0;
}

int fetch_ids(int* data, int argc, char** argv, char** az_col_name)
{
	data[0] = string_to_int(argv[0]);
	data[1] = string_to_int(argv[1]);
	return 0;
}

void sql_add_client(sqlite3* db, client* cl)
{
	char* sql = malloc(strlen(INSERTCLIENT) + strlen(cl->name) + int_len(cl->passwd) + int_len(cl->id) + 1);
	char* z_err_msg;
	if (sql != NULL)
	{
		snprintf(
			sql, strlen(sql),
			"INSERT INTO CLIENTS (ID, NAME, PASSWD) VALUES(%d, \'%s\', %d);", cl->id, cl->name, cl->passwd);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	sqlite3_exec(db, sql, NULL, 0, &z_err_msg);
	if (z_err_msg)
	{
		puts(z_err_msg);
	}
	sqlite3_free(z_err_msg);
	free(sql);
}

void sql_remove_client(sqlite3* db, client* cl)
{
	char* sql = malloc(strlen(REMOVECLIENT) + int_len(cl->id) + 1);
	char* z_err_msg;
	if (sql != NULL)
	{
		snprintf(sql, strlen(sql), "DELETE FROM CLIENTS WHERE ID=%d;", cl->id);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	sqlite3_exec(db, sql, NULL, 0, &z_err_msg);
	if (z_err_msg)
	{
		puts(z_err_msg);
	}
	sqlite3_free(z_err_msg);
	free(sql);
}

void sql_show_all_clients(sqlite3* db)
{
	char* z_err_msg;
	sqlite3_exec(db, SHOWALLCLIENTS, client_callback, 0, &z_err_msg);
	if (z_err_msg)
	{
		puts(z_err_msg);
	}
	sqlite3_free(z_err_msg);
}

void sql_add_item(sqlite3* db, item* it, client* cl)
{
	char* sql = malloc(
		strlen(INSERTITEM) + int_len(it->id) + strlen(it->name) + int_len(it->quantity) + int_len(cl->id) + 1);
	char* z_err_msg;
	if (sql != NULL)
	{
		snprintf(sql, strlen(sql), "INSERT INTO ITEMS (ID, NAME, QUANTITY, CLIENT_ID) VALUES(%d, '%s', %d, %d);",
			it->id, it->name, it->quantity, cl->id);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	sqlite3_exec(db, sql, NULL, 0, &z_err_msg);
	if (z_err_msg)
	{
		puts(z_err_msg);
	}
	sqlite3_free(z_err_msg);
	free(sql);
}

void sql_remove_item(sqlite3* db, char* name, client* cl)
{
	char* sql = malloc(strlen(REMOVEITEM) + strlen(name) + int_len(cl->id) + 1);
	char* z_err_msg;
	if (sql != NULL)
	{
		snprintf(sql, strlen(sql), "DELETE FROM ITEMS WHERE NAME='%s' AND CLIENT_ID=%d;", name, cl->id);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	sqlite3_exec(db, sql, NULL, 0, &z_err_msg);
	if (z_err_msg)
	{
		puts(z_err_msg);
	}
	sqlite3_free(z_err_msg);
	free(sql);
}

void sql_update_item(sqlite3* db, item* it)
{
	char* sql = malloc(strlen(UPDATEITEM) + int_len(it->id) + int_len(it->quantity) + 1);
	char* zErrMsg;
	if (sql != NULL)
	{
		snprintf(sql, strlen(sql), "UPDATE ITEMS SET QUANTITY=%d WHERE ID=%d;", it->quantity, it->id);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (zErrMsg)
	{
		puts(zErrMsg);
	}
	free(sql);
	sqlite3_free(zErrMsg);
}

void sql_remove_all_items(sqlite3* db, client* cl)
{
	char* sql = malloc(strlen(REMOVEALLITEMS) + int_len(cl->id) + 1);
	char* zErrMsg;

	if (sql != NULL)
	{
		snprintf(sql, strlen(sql), "DELETE FROM ITEMS WHERE CLIENT_ID=%d;", cl->id);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (zErrMsg)
	{
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
	free(sql);
}

void sql_show_item(sqlite3* db, client* cl, char* name)
{
	char* sql = malloc(strlen(SHOWITEM) + strlen(name) + int_len(cl->id) + 1);
	char* zErrMsg;
	if (sql != NULL)
	{
		snprintf(sql, strlen(sql), "SELECT * FROM ITEMS WHERE NAME LIKE '%s' AND CLIENT_ID=%d;", name, cl->id);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	sqlite3_exec(db, sql, item_callback, 0, &zErrMsg);
	if (zErrMsg)
	{
		puts(zErrMsg);
	}
	sqlite3_free(zErrMsg);
	free(sql);
}

void sql_set_last_ids(sqlite3* db, int* i_ds)
{
	char* z_err_msg;
	sqlite3_exec(db, "SELECT LAST_CLIENT_ID, LAST_ITEM_ID FROM UTILITY;", fetch_ids, i_ds, &z_err_msg);
	if (z_err_msg)
	{
		puts(z_err_msg);
	}
	sqlite3_free(z_err_msg);
}

void sql_show_all_items_of_client(sqlite3* db, client* cl, item_list* items)
{
	char* sql = malloc(strlen(SHOWALLITEMSOFCLIENT) + int_len(cl->id) + 1);
	char* z_err_msg;
	if (sql != NULL)
	{
		snprintf(sql, strlen(sql), "SELECT * FROM ITEMS WHERE CLIENT_ID=%d;", cl->id);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	sqlite3_exec(db, sql, item_list_callback, items, &z_err_msg);
	if (z_err_msg)
	{
		puts(z_err_msg);
	}
	sqlite3_free(z_err_msg);
	free(sql);
}

void sql_dump_last_ids(sqlite3* db, int* i_ds)
{
	char* z_err_msg;
	char* sql = malloc(strlen(DUMPLASTIDS) + int_len(i_ds[0]) + int_len(i_ds[1]));
	if (sql != NULL)
	{
		snprintf(sql, strlen(sql), "UPDATE UTILITY SET LAST_CLIENT_ID=%d, LAST_ITEM_ID=%d", i_ds[0], i_ds[1]);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	sqlite3_exec(db, sql, NULL, NULL, &z_err_msg);
	if (z_err_msg)
	{
		puts(z_err_msg);
	}
	sqlite3_free(z_err_msg);
}