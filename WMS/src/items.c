#include "../include/items.h"

item_list* new_item_list()
{
	item_list* items = malloc(sizeof(item_list));
	if (items == NULL)
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	items->list = NULL;
	items->size = 0;
	return items;
}

item* create_item(client* cl, int* ids, char* input)
{
	item* it = malloc(sizeof(item));
	if (it == NULL)
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	it->id = ids[1]++;
	handle_create_item_input(input, it);
	puts("Enter item quantity: ");
	it->quantity = scan_int();
	it->client_id = cl->id;
	return it;
}

void handle_create_item_input(const char* input, item* item)
{
	if (input != NULL)
	{
		create_item_from_input(input, item);
		return;
	}
	create_item_manually(item);
}

void create_item_from_input(const char* input, item* item)
{
	item->name = malloc(strlen(input) + 1);
	if (item->name == NULL)
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	strcpy_s(item->name, strlen(input) + 1, input);
}

void create_item_manually(item* item)
{
	puts("Enter item name: ");
	char* tmp = scan_string();
	item->name = malloc(strlen(tmp) + 1);
	if (item->name == NULL)
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	strcpy_s(item->name, strlen(tmp) + 1, tmp);
	free(tmp);
}

item* create_item_from_db(sqlite3* db, client* cl, char* name)
{
	char* z_err_msg = NULL;
	item* it = malloc(sizeof(item));
	char* sql = malloc(strlen(SEARCHITEM) + strlen(name) + int_len(cl->id) + 1);
	if (sql == NULL)
	{
		perror("AN ERROR OCCURED");
		exit(-1);
	}
	if (it != NULL)
	{
		it->id = -1;
	}
	snprintf(sql, strlen(sql), "SELECT * FROM ITEMS WHERE NAME LIKE '%s' AND CLIENT_ID=%d;", name, cl->id);
	sqlite3_exec(db, sql, item_creation_callback, it, &z_err_msg);
	return it;
}

int item_creation_callback(item* it, int argc, char** argv, char** az_col_name)
{
	it->id = string_to_int(argv[0]);
	it->name = malloc(strlen(argv[1]) + 1);
	if (it->name == NULL)
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	strcpy_s(it->name, strlen(argv[1]) + 1, argv[1]);
	it->quantity = string_to_int(argv[2]);
	it->client_id = string_to_int(argv[3]);
	return 0;
}

void free_item(item* item)
{
	if (item->name != NULL && item->id != -1)
	{
		free(item->name);
	}
	free(item);
}

void free_item_list(item_list* items)
{
	for (int i = 0; i < items->size; i++)
	{
		item** item = &items->list[i];
		free_item(*item);
	}
	free(items);
}