#pragma once
#define WHITEBACKGROUND()                                  \
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                          BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
#define WHITETEXT()                                        \
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                          FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

#include <Windows.h>
#include <conio.h>
#include "sql_manager.h"

void draw_menu(void);
void draw_entry_menu(void);
void get_choice_entry(sqlite3*, client**, int* ids);
void register_client(sqlite3* db, client** cl, int* ids);
void login_client(sqlite3* db, client** cl, int* ids);

int get_choice(sqlite3* db, client** cl, int* ids);
void delete_account(sqlite3* db, client** cl);
void get_clients(sqlite3* db);
void post_item(sqlite3* db, client** cl, int* ids);
void delete_item(sqlite3* db, client** cl);

void handle_edit_item(sqlite3* db, client** cl, int* ids);
void deposit_item(sqlite3* db, client** cl, int* ids);
void handle_no_item_found_deposit(sqlite3* db, client** cl, int* ids, char* items_name);
void handle_item_found_deposit(sqlite3* db, item* it);

void withdraw_item(sqlite3* db, client** cl, int* ids);
void handle_no_item_found_withdraw(char* items_name, item* it);
void handle_item_found_withdraw(sqlite3* db, char* items_name, item* it);
void handle_sufficient_amount(sqlite3* db, item* it, char* items_name, int amount);
void handle_insufficient_amount(item* it, char* items_name);

void find_item(sqlite3* db, client** cl);
void get_items(sqlite3* db, client** cl);

void handle_exit(int* exit_flag);

void scroll_items(item_list* items);
void scroll_loop(item_list* items, int offset);
void scroll_up(item_list* items, char dir, int offset);
void scroll_down(item_list* items, char dir, int offset);
