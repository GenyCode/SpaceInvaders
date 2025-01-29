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
Coordinate GetCursorPosition();
string GetNumberInput(int maxLength, int cursorX, int cursorY);
string GetInput(int maxLength);
string IntToString(int number);
int CalculateCenterIndex(int totalLength,int itemLength);
string GenerateANSI(int code);