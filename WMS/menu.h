#pragma once
#define BLUETEXT() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1)
#define REDTEXT() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4)
#define WHITETEXT() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7)

#include <Windows.h>
#include <stdio.h>
#include "client.h"
#include "items.h"

void drawMenu();
int getChoice();