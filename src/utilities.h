#pragma once
#include <string>
struct Coordinate{
    int x;
    int y;
};
using namespace std;
void HideCursor();
void ShowCursor();
void ClearScreen();
void Gotoxy(int x, int y);
void MoveCursorToTopLeft();
string GetNumberInput(int maxLength, int cursorX, int cursorY);
string GetInput(int maxLength);
string IntToString(int number);