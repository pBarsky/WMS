#include "menu.h"
void drawMenu(int active) {
	int i;
	const char *strings[8] = {
		"1. Add new client to database.",
		"2. Remove client from database.",
		"3. Update client in database.",
		"4. Show data of one client from database.",
		"5. Show data of all clients.",
		"6. Add new item to database.",
		"7. Remove item from database.",
		"8. Update item in database."
	};
	for (i = 0; i < 8; i++) {
		printf("%s\n", strings[i]);
	}
}

int getChoice(sqlite3* db)
{
	int success = 0;
	char choice;
	Client* cl;
	Item* it;
	choice = _getch();
	(" %d", &choice);
	switch (choice) {
	case '1':
		system("cls");
		cl = create_client();
		sql_addClient(db, cl);
		free(cl);
		break;
	case '2':
		system("cls");
		puts("Specify which client you want to affect.\n(You can leave name and surname blank, only the ID matters.)");
		cl = create_client();
		sql_removeClient(db, cl);
		free(cl);
		break;
	case '3':
		system("cls");
		break;
	case '4':
		system("cls");
		puts("Specify which client you want to show.\n(You can leave name and surname blank, only the ID matters.)");
		cl = create_client();
		sql_showClient(db, cl);
		free(cl);
		break;
	case '5':
		system("cls");
		sql_showAllClients(db);
		break;
	default:
		break;
	}

	return success;
}

