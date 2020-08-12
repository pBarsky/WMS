#include "../include/menu.h"

void drawEntryMenu()
{
	int i;
	const char* strings[] = {
		"q) Create a new client.",
		"w) Use an existing client.",
		"Any other key to exit Exit."
	};
	system("cls");
	WHITEBACKGROUND();
	for (i = 0; i < (sizeof(strings) / sizeof(strings[0])); i++)
	{
		puts(strings[i]);
	}
	WHITETEXT();
}

void drawMenu()
{
	int i;
	const char* strings[] = {
		"q) Remove your data from database. (Your account and items asigned to it.)",
		"w) List all clients.",
		"e) Add new item to your inventory.",
		"a) Delete item from your inventory.",
		"s) Update item\'s quantity in inventory.",
		"d) Look for an item.",
		"z) List all items in your inventory.",
		"x) Exit."
	};
	system("cls");
	WHITEBACKGROUND();
	for (i = 0; i < (sizeof(strings) / sizeof(strings[0])); i++)
	{
		puts(strings[i]);
	}
	WHITETEXT();
}

void getChoiceEntry(sqlite3* db, client** cl, int* i_ds)
{
	const char choice = _getch();

	switch (choice)
	{
	case 'q':
		*cl = create_client(i_ds);
		sql_addClient(db, *cl);
		system("pause");
		break;
	case 'w':
		*cl = create_client_from_db(db);
		if (*cl == NULL || (*cl)->NAME == NULL)
		{
			puts("No client found.");
			system("pause");
			exit(0);
		}
		break;
	default:
		exit(0);
	}
}

int getChoice(sqlite3* db, client** cl, int* IDs)
{
	int finished = 0;
	ItemList* items = malloc(sizeof(ItemList));
	if (items == NULL)
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	items->list = NULL;
	items->size = 0;
	Item* it = NULL;
	char* itemsName;
	int amount = 0;
	int i = 0;
	char choice = _getch();

	switch (choice)
	{
	case 'q': //delete account
		system("cls");
		sql_removeAllItems(db, *cl);
		sql_removeClient(db, *cl);
		puts("Data removed. Exiting...");
		finished = 1;
		system("pause");
		break;
	case 'w': //list all clients
		system("cls");
		sql_showAllClients(db);
		puts("No more (or any) data to show.");
		system("pause");
		break;
	case 'e': //add new item
		system("cls");
		it = create_item(*cl, IDs, NULL);
		sql_addItem(db, it, *cl);
		free_item(it);
		system("pause");
		break;
	case 'a': //remove item
		system("cls");
		sql_showAllItemsOfClient(db, *cl, items);
		puts("Please enter items name.: ");
		itemsName = scan_string();
		sql_removeItem(db, itemsName, *cl);
		free(itemsName);
		system("pause");
		break;
	case 's': //update item
		system("cls");
		choice = 0;
		sql_showAllItemsOfClient(db, *cl, items);
		puts("Do you want to:");
		puts("q) Deposit items.");
		puts("w) Withdraw items.");
		choice = _getch();
		switch (choice)
		{
		case 'q':
			puts("Specify name of the item.");
			itemsName = scan_string();
			it = create_item_fromDB(db, *cl, itemsName);
			if (it->ID == -1)
			{
				puts("Item not found in inventory. New item will be created");
				it = create_item(*cl, IDs, itemsName);
				sql_addItem(db, it, *cl);
			}
			else
			{
				puts("Specify amount you want to deposit.");
				amount = scan_int();
				it->QUANTITY += amount;
				sql_updateItem(db, it);
				printf("New balance: %d\n", it->QUANTITY);
			}
			free(itemsName);
			free_item(it);
			break;
		case 'w':
			puts("Specify name of the item.");
			itemsName = scan_string();
			it = create_item_fromDB(db, *cl, itemsName);
			if (it->ID == -1)
			{
				puts("Item not found in inventory.");
			}
			else
			{
				puts("Specify amount you want to withdraw.");
				amount = scan_int();
				if (amount <= it->QUANTITY)
				{
					it->QUANTITY -= amount;
				}
				else
				{
					puts("You dont have enough product.\nReturning to menu...");
					break;
				}
				sql_updateItem(db, it);
				printf("New balance: %d", it->QUANTITY);
			}
			free_item(it);
			free(itemsName);
			break;
		default:
			puts("You didnt specify an option. Returning to menu...");
			break;
		}
		system("pause");
		break;
	case 'd': //look for item
		system("cls");
		puts("Please enter name of item you are looking for.");
		itemsName = scan_string();
		sql_showItem(db, *cl, itemsName);
		system("pause");
		break;
	case 'z': //list all items
		system("cls");
		sql_showAllItemsOfClient(db, *cl, items);
		scroll_items(items);
		free_ItemList(items);
		system("pause");
		break;
	case 'x': //exit
		finished = 1;
		break;
	}
	return finished;
}

void scroll_items(ItemList* items)
{
	int i, offset = 0;
	char dir = '\0';
	for (i = offset; i < offset + 20 && i < items->size; i++)
	{
		printf("%d. NAME: %15s\tQUANTITY: %3d\n", i, items->list[i]->NAME, items->list[i]->QUANTITY);
	}
	puts("W to go up by 20 places, S to go down, X to exit");
	while (dir != 'x')
	{
		dir = _getch();
		switch (dir)
		{
		case 's':
			system("cls");
			offset = offset + 20 < items->size ? offset + 20 : offset;
			for (i = offset; i < offset + 20 && i < items->size; i++)
			{
				printf("%d. NAME: %15s\tQUANTITY: %3d\n", i, items->list[i]->NAME, items->list[i]->QUANTITY);
			}
			puts("W to go up by 20 places, S to go down, X to exit");
			break;
		case 'w':
			system("cls");
			offset = offset - 20 > 0 ? offset - 20 : 0;
			for (i = offset; i < offset + 20 && i < items->size; i++)
			{
				printf("%d. NAME: %15s\tQUANTITY: %3d\n", i, items->list[i]->NAME, items->list[i]->QUANTITY);
			}
			puts("W to go up by 20 places, S to go down, X to exit");
			break;
		default:
			break;
		}
	}
}