#pragma once
#define WHITEBACKGROUND() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)

#include <Windows.h>
#include <stdio.h>
#include "sql_manager.h"
#include <conio.h>

void drawMenu(int);
int getChoice(sqlite3*);