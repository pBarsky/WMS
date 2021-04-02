#include "../include/menu.h"

int main(int argc, char* argv[])
{
	sqlite3* db;
	client* cl = malloc(sizeof(client));
	int last_ids[2] = { 0 };
	char finished;
	const int rc = sqlite3_open("test.db", &db);

	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	fprintf(stderr, "Opened database successfully\n");
	sql_init(db);
	sql_set_last_ids(db, last_ids);
	draw_entry_menu();
	get_choice_entry(db, &cl, last_ids);
	do
	{
		draw_menu();
		finished = (char)get_choice(db, &cl, last_ids);
	} while (finished == 0);
	if (cl != NULL)
	{
		free_client(cl);
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	sql_dump_last_ids(db, last_ids);
	sqlite3_close(db);
	system("pause");
	return 0;
}