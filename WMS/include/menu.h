#pragma once
#define WHITEBACKGROUND() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
#define WHITETEXT() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

#include <Windows.h>
#include <stdio.h>
#include "sql_manager.h"
#include <conio.h>

void drawMenu();
int getChoice(sqlite3*, Client**);
void getChoiceEntry(sqlite3*, Client**);
