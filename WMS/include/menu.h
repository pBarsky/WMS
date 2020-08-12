#pragma once
#define WHITEBACKGROUND()                                  \
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                          BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
#define WHITETEXT()                                        \
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), \
                          FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include "sql_manager.h"

void drawMenu();
void drawEntryMenu();
void scroll_items(ItemList* items);
int getChoice(sqlite3*, client**, int* IDs);
void getChoiceEntry(sqlite3*, client**, int* i_ds);
