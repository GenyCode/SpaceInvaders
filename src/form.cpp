#include <iostream>
#include <Windows.h>
#include "color.h"
#include "form.h"
#include "utilities.cpp"
#include <conio.h>
using namespace std;

void PrintBlankForm()
{
    cout << BG_BLACK << FG_WHITE << blank_form;
}
void PrintBox(int width, int height, string fg_color)
{
    Coordinate point = GetCursorPosition();
    for (int i = 0; i < height; i++)
    {
        string right;
        string inner;
        string left;
        if (i == 0)
        {
            right = "╗";
            left = "╔";
            inner = "═";
        }
        else if (i == height - 1)
        {
            right = "╝";
            left = "╚";
            inner = "═";
        }
        else
        {
            right = "║";
            left = "║";
            inner = " ";
        }

        cout << fg_color << left;
        for (int j = 0; j < width - 2; j++)
        {
            cout << inner;
        }
        cout << right;
        Gotoxy(point.x, point.y + i + 1);
    }
    cout << FG_WHITE;
}
void PrintButton(Button button, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (button.position.col == display.userPosition.col && button.position.row == display.userPosition.row)
    {
        fg_color = FG_CYAN;
    }
    else
    {
        fg_color = FG_WHITE;
    }
    elementPos.y += (button.position.row - display.start_row) * 4;
    elementPos.x += (button.position.col) * 54;
    int width = 50;
    int height = 3;
    Gotoxy(elementPos.x, elementPos.y);
    PrintBox(width, height, fg_color);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    cout << fg_color << button.text << FG_WHITE;
}
void PrintTextbox(Textbox &textbox, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (display.isEditing && textbox.position.col == display.userPosition.col && textbox.position.row == display.userPosition.row)
    {
        fg_color = FG_YELLOW;
        int width = 50;
        int height = 3;
        elementPos.y += (textbox.position.row - display.start_row) * 4;
        elementPos.x += (textbox.position.col) * 54;
        Gotoxy(elementPos.x, elementPos.y);
        PrintBox(width, height, fg_color);
        Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
        textbox.value = GetInput(width - 4);
    }
    else
    {
        if (!textbox.value.empty())
        {
            PrintButton({textbox.value, textbox.position}, display);
        }
        else
        {
            PrintButton({textbox.placeholder, textbox.position}, display);
        }
    }
}
void NavigateForm(char input, Display &display, int row_count)
{
    if (isupper(input))
    {
        input = tolower(input);
    }
    int distance = display.end_row - display.start_row;
    switch (input)
    {
    case 'w':
        if (display.userPosition.row > 0)
        {
            display.userPosition.row--;
            if (display.userPosition.row < display.start_row)
            {
                display.start_row--;
                display.end_row--;
            }
        }

        break;
    case 's':
        if (display.userPosition.row < row_count-1)
        {
            display.userPosition.row++;
            if (display.userPosition.row > display.end_row)
            {
                display.start_row++;
                display.end_row++;
            }
        }

        break;
    case 'a':
        display.userPosition.col--;
        if (display.userPosition.col < 0)
        {
            display.userPosition.col = 1;
        }
        break;
    case 'd':
        display.userPosition.col++;
        if (display.userPosition.col > 1)
        {
            display.userPosition.col = 0;
        }
        break;
    case '\r':
        display.isEditing = true;
        break;
    default:
        break;
    }
}
int main()
{
    system("cls");
    Display display;
    int row_count = 17;
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    HideCursor();
    PrintBlankForm();
    Textbox txt[17] = {
        {"New User0", false, "", "", true, {0, 0}},
        {"New User1", false, "", "", true, {1, 0}},
        {"New User2", false, "", "", true, {2, 0}},
        {"New User3", false, "", "", true, {3, 0}},
        {"New User4", false, "", "", true, {4, 0}},
        {"New User5", false, "", "", true, {5, 0}},
        {"New User6", false, "", "", true, {6, 0}},
        {"New User7", false, "", "", true, {7, 0}},
        {"New User8", false, "", "", true, {8, 0}},
        {"New User9", false, "", "", true, {9, 0}},
        {"New User10", false, "", "", true, {10, 0}},
        {"New User11", false, "", "", true, {11, 0}},
        {"New User12", false, "", "", true, {12, 0}},
        {"New User13", false, "", "", true, {13, 0}},
        {"New User14", false, "", "", true, {14, 0}},
        {"New User15", false, "", "", true, {15, 0}},
        {"New User16", false, "", "", true, {16, 0}}};
    while (true)
    {
        for (int i = display.start_row; i <= display.end_row; i++)
        {
            PrintTextbox(txt[i], display);
        }
        if (display.isEditing)
            display.isEditing = !display.isEditing;
        else
        {
            char ch = getch();
            NavigateForm(ch, display, row_count);
        }
    }

    return 0;
}
