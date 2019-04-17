#include "menu.h"
void drawEntryMenu() {
	int i;
	const char* strings[] = {
		"q) Create a new client.",
		"w) Use an existing client.",
		"e) Exit."
	};
	system("cls");
	WHITEBACKGROUND();
	for (i = 0; i < (sizeof(strings) / sizeof(strings[0])); i++) {
		puts(strings[i]);
	}
	WHITETEXT();
}
void drawMenu() {
	int i;
	const char* strings[] = {
		"q) Add new client to database.",
		"w) Remove client from database.",
		"e) Update client in database. (NOT IMPLEMENTED YET)",
		"r) Show data of one client from database.",
		"a) Show data of all clients.",
		"s) Add new item to database.",
		"d) Remove item from database.",
		"f) Update item in database. (NOT IMPLEMENTED YET)",
		"z) Show data of one item. (NOT IMPLEMENTED YET)",
		"x) Show all items of a client.",
		"c) Exit."
	};
	system("cls");
	WHITEBACKGROUND();
	for (i = 0; i < (sizeof(strings) / sizeof(strings[0])); i++) {
		puts(strings[i]);
	}
	WHITETEXT();
}

void getChoiceEntry(sqlite3* db, Client** cl) {
	char choice;
	choice = _getch();

	switch (choice) {
	case 'q':
		*cl = create_client();
		sql_addClient(db, *cl);
		system("pause");
		break;
	case 'w':
		*cl = create_client_fromDB();
		break;
	case 'e':
		exit(0);
	default:
		exit(0);
		break;
	}
}

int getChoice(sqlite3* db, Client** cl)
{
	char choice;
	int exit = 0;
	Item* it = NULL;
	choice = _getch();
	switch (choice) {
	case 'q':
		system("cls");
		if (*cl != NULL) *cl = create_client();
		sql_addClient(db, *cl);
		free_client(*cl);
		system("pause");
		break;
	case 'w':
		system("cls");
		sql_removeItem(db, *cl);
		sql_removeClient(db, *cl);
		free_client(cl);
		system("pause");
		break;
	case 'e':
		system("cls");
		puts("NOT IMPLEMENTED YET");
		system("pause");
		break;
	case 'r':
		system("cls");
		sql_showClient(db, cl);
		system("pause");
		break;
	case 'a':
		system("cls");
		sql_showAllClients(db);
		puts("No more (or any) data to show.");
		system("pause");
		break;
	case 's':
		system("cls");
		it = create_item(*cl);
		sql_addItem(db, it, *cl);
		free_item(it);
		system("pause");
		break;
	case 'd':
		system("cls");
		sql_removeClient(db, *cl);
		system("pause");
		break;
	case 'f':
		system("cls");
		puts("NOT IMPLEMENTED YET");
		system("pause");
		break;
	case 'z':
		system("cls");
		puts("NOT IMPLEMENTED YET");
		system("pause");
		break;
	case 'x':
		system("cls");
		sql_showAllItemsOfClient(db, *cl);
		system("pause");
		break;
	default:
		exit = 1;
		free_client(*cl);
		break;
	}
	return exit;
}
