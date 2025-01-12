#pragma once
#include <string>

using namespace std;
void HideCursor();
void ShowCursor();
void ClearScreen();
void Gotoxy(int x, int y);
void MoveCursorToTopLeft();
string GetNumberInput(int maxLength, int cursorX, int cursorY);
string GetInput(int maxLength, int cursorX, int cursorY);
string IntToString(int number);