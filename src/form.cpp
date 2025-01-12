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
void PrintButton(Button button, Position userPosition)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (button.position.col == userPosition.col && button.position.row == userPosition.row)
    {
        fg_color = FG_CYAN;
    }
    else
    {
        fg_color = FG_WHITE;
    }
    elementPos.y += button.position.row * 4;
    elementPos.x += button.position.col * 54;
    int width = 50;
    int height = 3;
    Gotoxy(elementPos.x, elementPos.y);
    PrintBox(width, height, fg_color);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    cout << fg_color << button.text << FG_WHITE;
}
void PrintTextbox(Textbox &textbox, Position userPosition, bool isEditing)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (isEditing && textbox.position.col == userPosition.col && textbox.position.row == userPosition.row)
    {
        fg_color = FG_YELLOW;
        int width = 50;
        int height = 3;
        elementPos.y += textbox.position.row * 4;
        elementPos.x += textbox.position.col * 54;
        Gotoxy(elementPos.x, elementPos.y);
        PrintBox(width, height, fg_color);
        Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
        textbox.value = GetInput(width - 4);
    }
    else
    {
        if (!textbox.value.empty())
        {
            PrintButton({textbox.value, textbox.position}, userPosition);
        }
        else
        {
            PrintButton({textbox.placeholder, textbox.position}, userPosition);
        }
    }
}
void NavigateForm(Position &userPosition, char input,bool &isEditing)
{
    if (isupper(input))
    {
        input = tolower(input);
    }

    switch (input)
    {
    case 'w':
        userPosition.row--;
        break;
    case 's':
        userPosition.row++;
        break;
    case 'a':
        userPosition.col--;
        if(userPosition.col < 0){
            userPosition.col = 1;
        }
        break;
    case 'd':
        userPosition.col++;
        if(userPosition.col > 1){
            userPosition.col = 0;
        }
        break;
    case '\r':
        isEditing = true;
        break;
    default:
        break;
    }
}
int main()
{

    system("cls");
    Position userPosition = {0, 0};
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    HideCursor();
    PrintBlankForm();
    Textbox txt1 = {"New User", false, "", "", true, {0, 0}};
    Textbox txt2 = {"New User", false, "", "", true, {1, 0}};
    Textbox txt3 = {"New User", false, "", "", true, {2, 0}};
    Textbox txt4 = {"New User", false, "", "", true, {3, 0}};
    Textbox txt5 = {"New User", false, "", "", true, {4, 0}};
    Textbox txt6 = {"New User", false, "", "", true, {0, 1}};
    Textbox txt7 = {"New User", false, "", "", true, {1, 1}};
    Textbox txt8 = {"New User", false, "", "", true, {2, 1}};
    Textbox txt9 = {"New User", false, "", "", true, {3, 1}};
    Textbox txt10 = {"New User", false, "", "", true, {4, 1}};
    bool isEditing = false;
    while (true)
    {

        PrintTextbox(txt1, userPosition, isEditing);
        PrintTextbox(txt2, userPosition, isEditing);
        PrintTextbox(txt3, userPosition, isEditing);
        PrintTextbox(txt4, userPosition, isEditing);
        PrintTextbox(txt5, userPosition, isEditing);
        PrintTextbox(txt6, userPosition, isEditing);
        PrintTextbox(txt7, userPosition, isEditing);
        PrintTextbox(txt8, userPosition, isEditing);
        PrintTextbox(txt9, userPosition, isEditing);
        PrintTextbox(txt10, userPosition, isEditing);
        if (isEditing)
            isEditing = !isEditing;
        else
        {
            char ch = getch();
            NavigateForm(userPosition,ch,isEditing);
        }
    }

    return 0;
}