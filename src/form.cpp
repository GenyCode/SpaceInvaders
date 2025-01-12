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
    if (display.SetValueMode && textbox.position.col == display.userPosition.col && textbox.position.row == display.userPosition.row)
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
void PrintRangebar(RangeBar &rangeBar, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (rangeBar.position.col == display.userPosition.col && rangeBar.position.row == display.userPosition.row)
    {
        fg_color = FG_CYAN;
    }
    else
    {
        fg_color = FG_WHITE;
    }
    elementPos.y += (rangeBar.position.row - display.start_row) * 4;
    elementPos.x += (rangeBar.position.col) * 54;
    int width = 50;
    int height = 3;
    Gotoxy(elementPos.x, elementPos.y);
    PrintBox(width, height, fg_color);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    cout << fg_color << rangeBar.text << FG_WHITE;
    Gotoxy(elementPos.x + 14, elementPos.y + (height / 2));
    int dis = rangeBar.max - rangeBar.min;
    int fillCharacterCount = (rangeBar.value % dis) * 29 / dis;
    cout << fg_color;
    for (int i = 0; i < 29; i++)
    {
        if (i < fillCharacterCount)
            cout << "▓";
        else if (i == fillCharacterCount)
            cout << "█";
        else
            cout << "░";
    }
    cout << FG_WHITE;
    Gotoxy(elementPos.x +width-6, elementPos.y + (height / 2));
    if (rangeBar.UsePercentage)
    {
        cout << fg_color << (rangeBar.value % dis) * 100 / dis << "%" << FG_WHITE;
    }
    else
    {
        cout << fg_color << rangeBar.value << FG_WHITE;
    }
}
// TODO: کاربر میتونه روی المنتی که وجود نداره حرکت کنه، این باگ هست
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
        if (display.userPosition.row < row_count - 1)
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
        display.SetValueMode = true;
        break;
    default:
        break;
    }
}
void PrintCheckbox(Checkbox &checkbox, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (checkbox.position.col == display.userPosition.col && checkbox.position.row == display.userPosition.row)
    {
        fg_color = FG_CYAN;
    }
    else
    {
        fg_color = FG_WHITE;
    }
    elementPos.y += (checkbox.position.row - display.start_row) * 4;
    elementPos.x += (checkbox.position.col) * 54;
    int width = 50;
    int height = 3;
    Gotoxy(elementPos.x, elementPos.y);
    PrintBox(width, height, fg_color);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    cout << fg_color << checkbox.text << FG_WHITE;
    Gotoxy(elementPos.x + width - 4, elementPos.y + (height / 2));
    if (checkbox.isChecked)
    {
        cout << fg_color << "▒█" << FG_WHITE;
    }
    else
    {
        cout << fg_color << "█░" << FG_WHITE;
    }
}
void PrintSelectbox(Selectbox &selectbox, Display display)
{

    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (selectbox.position.col == display.userPosition.col && selectbox.position.row == display.userPosition.row)
    {
        fg_color = FG_CYAN;
    }
    else
    {
        fg_color = FG_WHITE;
    }
    elementPos.y += (selectbox.position.row - display.start_row) * 4;
    elementPos.x += (selectbox.position.col) * 54;
    int width = 50;
    int height = 3;
    Gotoxy(elementPos.x, elementPos.y);
    PrintBox(width, height, fg_color);
    Gotoxy(elementPos.x + 2, elementPos.y + 1);
    cout << fg_color << "<";
    Gotoxy(elementPos.x + width - 3, elementPos.y + 1);
    cout << fg_color << ">";
    Gotoxy(elementPos.x + 4, elementPos.y + 1);
    if (selectbox.SelectedIndex == -1)
    {
        cout << fg_color << selectbox.placeholder << FG_WHITE;
    }
    else
    {
        cout << fg_color << selectbox.Items[selectbox.SelectedIndex].text << FG_WHITE;
    }
}
// TODO: Create Action function for Modified Elements depends on User Input
int main()
{
    system("cls");
    Display display;
    int row_count = 5;
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    HideCursor();
    PrintBlankForm();
    Checkbox checkbox[5] = {
        {"Feature 01", false, {0, 0}},
        {"Feature 02", false, {1, 0}},
        {"Feature 03", true, {2, 0}},
        {"Feature 04", false, {3, 0}},
        {"Feature 05", false, {4, 0}}};
    RangeBar rangebar[5] = {
        {"Sound:", 0, 100, 50, false, {0, 1}},
        {"Range 02", 0, 200, 50, true, {1, 1}},
        {"Range 03", 100, 150, 110, false, {2, 1}},
        {"Range 04", 0, 100, 30, true ,{3, 1}},
        {"Range 05", 0, 100, 0, false, {4, 1}}};
    while (true)
    {
        int selectedElementIndex = 0;
        ElementType selectedElementType;

        for (int i = display.start_row; i <= display.end_row; i++)
        {
            if ((rangebar[i].position.col == display.userPosition.col) && (rangebar[i].position.row == display.userPosition.row))
            {
                selectedElementIndex = i;
                selectedElementType = RANGEBAR;
            }
            PrintRangebar(rangebar[i], display);
        }
        for (int i = display.start_row; i <= display.end_row; i++)
        {
            if ((checkbox[i].position.col == display.userPosition.col) && (checkbox[i].position.row == display.userPosition.row))
            {
                selectedElementIndex = i;
                selectedElementType = CHECKBOX;
            }
            PrintCheckbox(checkbox[i], display);
        }
        if (display.SetValueMode)
            display.SetValueMode = !display.SetValueMode;
        else
        {
            char ch = getch();
            if (ch == 'x')
            {
                switch (selectedElementType)
                {
                case CHECKBOX:
                    checkbox[selectedElementIndex].isChecked = !checkbox[selectedElementIndex].isChecked;
                    break;
                }
            }
            else
            {
                NavigateForm(ch, display, row_count);
            }
        }
    }
    return 0;
}
