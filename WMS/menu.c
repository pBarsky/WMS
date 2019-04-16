#include "menu.h"
void drawEntryMenu() {
	int i;
	const char* strings[] = {
		"1.Create a new client.",
		"2.Use an existing client.",
		"3.Exit."
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
		"1. Add new client to database.",
		"2. Remove client from database.",
		"3. Update client in database.",
		"4. Show data of one client from database.",
		"5. Show data of all clients.",
		"6. Add new item to database.",
		"7. Remove item from database.",
		"8. Update item in database.",
		"9. Show data of one item",
		"10. show data of all items"
	};
	system("cls");
	WHITEBACKGROUND();
	for (i = 0; i < (sizeof(strings) / sizeof(strings[0])); i++) {
		puts(strings[i]);
	}
	WHITETEXT();
}

void getChoiceEntry(Client* cl) {
	char choice;
	choice = _getch();

	switch (choice) {
	case '1':
		cl = create_client();
		break;
	case '2':
		cl = create_client_fromDB();
		break;
	case '3':
		exit(0);
	default:
		break;
	}
}

void getChoice(sqlite3* db, Client* cl)
{
	char choice;
	Item* it = NULL;
	choice = _getch();
	(" %d", &choice);
	switch (choice) {
	case '1':
		system("cls");
		cl = create_client();
		sql_addClient(db, cl);
		free_client(cl);
		break;
	case '2':
		system("cls");
		puts("Specify which client you want to affect.\n(You can leave name and surname blank, only the ID matters.)");
		cl = create_client();
		sql_removeClient(db, cl);
		free_client(cl);
		break;
	case '3':
		system("cls");
		break;
	case '4':
		system("cls");
		puts("Specify which client you want to show.\n(You can leave name and surname blank, only the ID matters.)");
		cl = create_client();
		sql_showClient(db, cl);
		free_client(cl);
		puts("No more (or any) data to show.");
		break;
	case '5':
		system("cls");
		sql_showAllClients(db);
		puts("No more (or any) data to show.");
		break;
	case '6':
		system("cls");
		it = create_item(cl);
		sql_addItem(db, it, cl);
		free_item(it);
		free_client(cl);
	case '7':
		system("cls");
	case '8':
		system("cls");
	case '9':
		system("cls");
	case '10':
		system("cls");

		break;
	default:
		break;
	}

}
