#include "../include/menu.h"
void drawEntryMenu() {
  int i;
  const char *strings[] = {
      "q) Create a new client.",
      "w) Use an existing client.",
      "e) Exit."};
  system("cls");
  WHITEBACKGROUND();
  for (i = 0; i < (sizeof(strings) / sizeof(strings[0])); i++) {
    puts(strings[i]);
  }
  WHITETEXT();
}
void drawMenu() {
  int i;
  const char *strings[] = {
      "q) Remove your data from database. (Your account and items asigned to it.)",
      "w) List all clients.",
      "e) Add new item to your inventory.",
      "a) Delete item from your inventory.",
      "s) Update item\'s quantity in inventory.",
      "d) Look for an item.",
      "z) List all items in your inventory.",
      "x) Exit."};
  system("cls");
  WHITEBACKGROUND();
  for (i = 0; i < (sizeof(strings) / sizeof(strings[0])); i++) {
    puts(strings[i]);
  }
  WHITETEXT();
}

void getChoiceEntry(sqlite3 *db, Client **cl, int *IDs) {
  char choice;
  choice = _getch();

  switch (choice) {
  case 'q':
    *cl = create_client(IDs);
    sql_addClient(db, *cl);
    system("pause");
    break;
  case 'w':
    *cl = create_client_fromDB(db);
    if (*cl == NULL || (*cl)->NAME == NULL) {
      puts("No client found.");
      system("pause");
      exit(0);
    }
    break;
  case 'e':
    exit(0);
  }
}

int getChoice(sqlite3 *db, Client **cl, int *IDs) {
  char choice;
  int exit = 0;
  Item *it = NULL;
  char *itemsName;
  int amount = 0;
  choice = _getch();

  switch (choice) {
  case 'q': //delete account
    system("cls");
    sql_removeAllItems(db, *cl);
    sql_removeClient(db, *cl);
    puts("Data removed. Exiting...");
    exit = 1;
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
    sql_showAllItemsOfClient(db, *cl);
    puts("Please enter items name.: ");
    itemsName = scanString();
    sql_removeItem(db, itemsName, *cl);
    free(itemsName);
    system("pause");
    break;
  case 's': //update item
    system("cls");
    choice = 0;
    sql_showAllItemsOfClient(db, *cl);
    puts("Do you want to:");
    puts("q) Deposit items.");
    puts("w) Withdraw items.");
    choice = _getch();
    switch (choice) {
    case 'q':
      puts("Specify name of the item.");
      itemsName = scanString();
      it = create_item_fromDB(db, *cl, itemsName);
      if (it->ID == -1) {
        puts("Item not found in inventory. New item will be created");
        it = create_item(*cl, IDs, itemsName);
        sql_addItem(db, it, *cl);
      } else {
        puts("Specify amount you want to deposit.");
        amount = scanInt();
        it->QUANTITY += amount;
        sql_updateItem(db, it);
        printf("New balance: %d\n", it->QUANTITY);
      }
      free(itemsName);
      free_item(it);
      break;
    case 'w':
      puts("Specify name of the item.");
      itemsName = scanString();
      it = create_item_fromDB(db, *cl, itemsName);
      if (it->ID == -1) {
        puts("Item not found in inventory.");
      } else {
        puts("Specify amount you want to withdraw.");
        amount = scanInt();
        if (amount <= it->QUANTITY) {
          it->QUANTITY -= amount;
        } else {
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
    itemsName = scanString();
    sql_showItem(db, *cl, itemsName);
    system("pause");
    break;
  case 'z': //list all items
    system("cls");
    sql_showAllItemsOfClient(db, *cl);
    system("pause");
    break;
  case 'x': //exit
    exit = 1;
    break;
  }
  return exit;
}
