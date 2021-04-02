#include "../include/menu.h"

void draw_entry_menu()
{
	const char* strings[] = {
		"q) Create a new client.",
		"w) Use an existing client.",
		"Any other key to exit Exit."
	};
	system("cls");
	WHITEBACKGROUND();
	for (int i = 0; i < (int)(sizeof(strings) / sizeof(strings[0])); i++) { puts(strings[i]); }
	WHITETEXT();
}

void draw_menu()
{
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
	for (int i = 0; i < (int)(sizeof(strings) / sizeof(strings[0])); i++) { puts(strings[i]); }
	WHITETEXT();
}

void get_choice_entry(sqlite3* db, client** cl, int* ids)
{
	const char choice = (char)_getch();

	switch (choice)
	{
	case 'q':
		register_client(db, cl, ids);
		break;
	case 'w':
		login_client(db, cl, ids);
		break;
	default: exit(0);
	}
}

void register_client(sqlite3* db, client** cl, int* ids)
{
	*cl = create_client(ids);
	sql_add_client(db, *cl);
	system("pause");
}

void login_client(sqlite3* db, client** cl, int* ids)
{
	*cl = create_client_from_db(db);
	if (*cl == NULL || (*cl)->name == NULL)
	{
		puts("No client found.");
		system("pause");
		exit(0);
	}
}

int get_choice(sqlite3* db, client** cl, int* ids)
{
	int finished = 0;
	const char choice = (char)_getch();

	switch (choice)
	{
	case 'q': //delete account
		delete_account(db, cl);
		handle_exit(&finished);
		// system("pause");
		break;
	case 'w': //list all clients
		get_clients(db);
		// system("pause");
		break;
	case 'e': //add new item
		post_item(db, cl, ids);
		system("pause");
		break;
	case 'a': //remove item
		delete_item(db, cl);
		system("pause");
		break;
	case 's': //update item
		handle_edit_item(db, cl, ids);
		system("pause");
		break;
	case 'd': //look for item
		find_item(db, cl);
		system("pause");
		break;
	case 'z': //list all items
		get_items(db, cl);
		system("pause");
		break;
	case 'x': //exit
		handle_exit(&finished);
		break;
	default: break;
	}
	return finished;
}

void delete_account(sqlite3* db, client** cl)
{
	system("cls");
	sql_remove_all_items(db, *cl);
	sql_remove_client(db, *cl);
	puts("Data removed. Exiting...");
}

void get_clients(sqlite3* db)
{
	system("cls");
	sql_show_all_clients(db);
	puts("No more (or any) data to show.");
}

void post_item(sqlite3* db, client** cl, int* ids)
{
	system("cls");
	item* it = create_item(*cl, ids, NULL);
	sql_add_item(db, it, *cl);
	free_item(it);
}

void delete_item(sqlite3* db, client** cl)
{
	system("cls");
	item_list* items = new_item_list();
	sql_show_all_items_of_client(db, *cl, items);
	puts("Please enter items name.: ");
	char* items_name = scan_string();
	sql_remove_item(db, items_name, *cl);
	free(items_name);
}

void handle_edit_item(sqlite3* db, client** cl, int* ids)
{
	system("cls");
	item_list* items = new_item_list();
	sql_show_all_items_of_client(db, *cl, items);
	puts("Do you want to:");
	puts("q) Deposit items.");
	puts("w) Withdraw items.");
	const char choice = (char)_getch();
	switch (choice)
	{
	case 'q':
		deposit_item(db, cl, ids);
		break;
	case 'w':
		withdraw_item(db, cl, ids);
		break;
	default:
		puts("You didnt specify an option. Returning to menu...");
		break;
	}
}

void deposit_item(sqlite3* db, client** cl, int* ids)
{
	puts("Specify name of the item.");
	char* items_name = scan_string();
	item* it = create_item_from_db(db, *cl, items_name);
	if (it->id == -1)
	{
		handle_no_item_found_deposit(db, cl, ids, items_name);
		return;
	}
	handle_item_found_deposit(db, it);
}

void handle_no_item_found_deposit(sqlite3* db, client** cl, int* ids, char* items_name)
{
	puts("Item not found in inventory. New item will be created");
	item* it = create_item(*cl, ids, items_name);
	sql_add_item(db, it, *cl);
	free(items_name);
	free_item(it);
}

void handle_item_found_deposit(sqlite3* db, item* it)
{
	puts("Specify amount you want to deposit.");
	const int amount = scan_int();
	it->quantity += amount;
	sql_update_item(db, it);
	printf("New balance: %d\n", it->quantity);
	free_item(it);
}

void withdraw_item(sqlite3* db, client** cl, int* ids)
{
	puts("Specify name of the item.");
	char* items_name = scan_string();
	item* it = create_item_from_db(db, *cl, items_name);
	if (it->id == -1)
	{
		handle_no_item_found_withdraw(items_name, it);
		return;
	}
	handle_item_found_withdraw(db, items_name, it);
}

void handle_no_item_found_withdraw(char* items_name, item* it)
{
	puts("Item not found in inventory.");
	free_item(it);
	free(items_name);
}

void handle_item_found_withdraw(sqlite3* db, char* items_name, item* it)
{
	puts("Specify amount you want to withdraw.");
	const int amount = scan_int();
	if (amount <= it->quantity)
	{
		handle_sufficient_amount(db, it, items_name, amount);
		return;
	}
	handle_insufficient_amount(it, items_name);
}

void handle_sufficient_amount(sqlite3* db, item* it, char* items_name, int amount)
{
	it->quantity -= amount;
	sql_update_item(db, it);
	printf("New balance: %d", it->quantity);
	free_item(it);
}

void handle_insufficient_amount(item* it, char* items_name)
{
	puts("You dont have enough product.\nReturning to menu...");
	free_item(it);
	free(items_name);
}

void find_item(sqlite3* db, client** cl)
{
	system("cls");
	puts("Please enter name of item you are looking for.");
	char* items_name = scan_string();
	sql_show_item(db, *cl, items_name);
}

void get_items(sqlite3* db, client** cl)
{
	system("cls");
	item_list* items = new_item_list();
	sql_show_all_items_of_client(db, *cl, items);
	scroll_items(items);
	free_item_list(items);
}

void handle_exit(int* exit_flag) { *exit_flag = 1; }

void scroll_items(item_list* items)
{
	const int offset = 0;
	for (int i = offset; i < offset + 20 && i < items->size; i++)
	{
		printf("%d. NAME: %15s\tQUANTITY: %3d\n", i, items->list[i]->name, items->list[i]->quantity);
	}
	scroll_loop(items, offset);
}

void scroll_loop(item_list* items, const int offset)
{
	puts("W to go up by 20 places, S to go down, X to exit");
	char dir = 0;
	while (dir != 'x')
	{
		dir = (char)_getch();
		switch (dir)
		{
		case 's':
			scroll_up(items, dir, offset);
			break;
		case 'w':
			scroll_down(items, dir, offset);
			break;
		default: break;
		}
	}
}

void scroll_up(item_list* items, char dir, int offset)
{
	system("cls");
	offset = offset + 20 < items->size ? offset + 20 : offset;
	for (int i = offset; i < offset + 20 && i < items->size; i++)
	{
		printf("%d. NAME: %15s\tQUANTITY: %3d\n", i, items->list[i]->name, items->list[i]->quantity);
	}
	puts("W to go up by 20 places, S to go down, X to exit");
}

void scroll_down(item_list* items, char dir, int offset)
{
	system("cls");
	offset = offset - 20 > 0 ? offset - 20 : 0;
	for (int i = offset; i < offset + 20 && i < items->size; i++)
	{
		printf("%d. NAME: %15s\tQUANTITY: %3d\n", i, items->list[i]->name, items->list[i]->quantity);
	}
	puts("W to go up by 20 places, S to go down, X to exit");
}