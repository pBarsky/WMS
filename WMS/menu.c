#include "menu.h"
void drawMenu() {
	BLUETEXT();
	puts("1. Add client to db.");
	REDTEXT();
	puts("2. Remove client from db.");
	WHITETEXT();
	puts("3. Update client in db.");
	puts("4. Add item to db.");
	puts("5. Remove item from db.");
	puts("6. Update item in db.");
}

int getChoice()
{
	int success = 0;
	int choice;
	Client* cl = NULL;
	Item* it = NULL;
	scanf_s(" %d", &choice);
	getchar();
	switch (choice) {
	case 1:
		system("cls");
		
		break;
	case 2:
		break;
	default:
		break;
	}

	return success;
}

