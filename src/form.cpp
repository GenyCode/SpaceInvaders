#include <iostream>
#include <Windows.h>
#include "color.h"
#include "form.h"
#include "utilities.cpp"
#include <conio.h>
using namespace std;
bool IsElementSelected(Position position,Display display){
    return position.row == display.userPosition.row && position.col == display.userPosition.col;
}
void RenderBackground()
{
    cout << BG_BLACK << FG_WHITE << blank_form;
}
void DrawBox(int width, int height, string fg_color)
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
void RenderButton(Button button, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (IsElementSelected(button.position,display))
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
    DrawBox(width, height, fg_color);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    cout << fg_color << button.text << FG_WHITE;
}
void RenderTextbox(Textbox &textbox, Display display)
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
        DrawBox(width, height, fg_color);
        Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
        textbox.value = GetInput(width - 4);
    }
    else
    {
        if (!textbox.value.empty())
        {
            RenderButton({textbox.value, textbox.position}, display);
        }
        else
        {
            RenderButton({textbox.placeholder, textbox.position}, display);
        }
    }
}
void RenderRangebar(RangeBar &rangeBar, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (IsElementSelected(rangeBar.position,display))
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
    DrawBox(width, height, fg_color);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    cout << fg_color << rangeBar.text << FG_WHITE;
    Gotoxy(elementPos.x + 14, elementPos.y + (height / 2));
    int dis = rangeBar.max - rangeBar.min;
    float ProgressRate = (rangeBar.value - rangeBar.min) * 1.0 / dis;

    int fillCharacterCount = ProgressRate * 28;
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
    Gotoxy(elementPos.x + width - 6, elementPos.y + (height / 2));
    if (rangeBar.UsePercentage)
    {
        int percentage = ProgressRate * 100;
        cout << fg_color << percentage << "%" << FG_WHITE;
    }
    else
    {
        cout << fg_color << rangeBar.value << FG_WHITE;
    }
}
void RenderFooter(string text)
{
    Gotoxy(footer_area.x, footer_area.y);
    cout << FG_WHITE << text;
    for (int i = footer_area.x + text.length(); i < end_area.x; i++)
    {
        cout << " ";
    }
}
// TODO: کاربر میتونه روی المنتی که وجود نداره حرکت کنه، این باگ هست
void HandleNavigation(char input, Display &display, int row_count)
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
void RenderCheckbox(Checkbox &checkbox, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (IsElementSelected(checkbox.position,display))
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
    DrawBox(width, height, fg_color);
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
void RenderSelectbox(Selectbox &selectbox, Display display)
{

    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (IsElementSelected(selectbox.position,display))
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
    DrawBox(width, height, fg_color);
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
void UpdateSelectBoxSelection(Selectbox &selectbox, int input)
{
    if (input == 5)
    {
        selectbox.SelectedIndex--;
        if (selectbox.SelectedIndex < 0)
            selectbox.SelectedIndex = selectbox.ItemsCount - 1;
    }
    else if (input == 6)
    {
        selectbox.SelectedIndex++;
        if (selectbox.SelectedIndex > selectbox.ItemsCount - 1)
            selectbox.SelectedIndex = 0;
    }
}
void UpdateRangeBarValue(RangeBar &rangeBar, int input)
{
    int dis = rangeBar.max - rangeBar.min;
    int step = dis / 28;
    if (input == 5 && rangeBar.value != 0)
    {
        rangeBar.value -= step;
        if (rangeBar.value < 0)
            rangeBar.value = 0;
    }
    else if (input == 6 && rangeBar.value != rangeBar.max)
    {
        rangeBar.value += step;
        if (rangeBar.value > rangeBar.max)
            rangeBar.value = rangeBar.max;
    }
}
void ToggleCheckboxState(Checkbox &checkbox)
{
    checkbox.isChecked = !checkbox.isChecked;
}
void OnPress6(void *element, ElementType type)
{
    switch (type)
    {
    case CHECKBOX:
        ToggleCheckboxState(*((Checkbox *)element));
        break;
    case SELECTBOX:
        UpdateSelectBoxSelection(*((Selectbox *)element), 6);
        break;
    case RANGEBAR:
        UpdateRangeBarValue(*((RangeBar *)element), 6);
        break;
    }
}
void OnPress5(void *element, ElementType type)
{
    switch (type)
    {
    case SELECTBOX:
        UpdateSelectBoxSelection(*((Selectbox *)element), 5);
        break;
    case RANGEBAR:
        UpdateRangeBarValue(*((RangeBar *)element), 5);
        break;
    }
}
void HandleInput(char input, Display &display, ElementType type, void *element, int row_count)
{
    if (input == 'x')
    {
        OnPress6(element, type);
    }
    else if (input == 'z')
    {
        OnPress5(element, type);
    }
    else
    {
        HandleNavigation(input, display, row_count);
    }
}
string GetKeyHints(ElementType type)
{
    string result = "";
    switch (type)
    {
    case CHECKBOX:
        result = "[X]: Toggle Checkbox";
        break;
    case SELECTBOX:
        result = "[Z]: Previous Option  [X]: Next Option";
        break;
    case RANGEBAR:
        result = "[Z]: Decrease Value  [X]: Increase Value";
        break;
    default:
        result = "Use [W], [A], [S], [D] to Navigate, [Enter] to Select.";
        break;
    }
    return result;
}

int main()
{
    system("cls");
    Display display;
    int row_count = 5;
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    HideCursor();
    RenderBackground();
    Checkbox checkbox = {"Feature 01", false, {0, 0}};
    RangeBar rangebar[5] = {
        {"Sound:", 0, 100, 50, false, {0, 1}},
        {"Range 02", 0, 200, 50, true, {1, 1}},
        {"Range 03", 100, 150, 110, false, {2, 1}},
        {"Range 04", 0, 100, 30, true, {3, 1}},
        {"Range 05", 0, 100, 0, false, {4, 1}}};
    Selectbox selectbox = {{{"item1", 0}, {"item2", 1}, {"item3", 2}, {"item4", 4}}, "Enter Selectbox 01", 4, -1, {3, 0}};
    //  Selectbox selectbox[5] = {
    //    ,
    //     {{{"item1",0},{"item2",1},{"item3",2},{"item4",4}},"Enter Selectbox 02",4, -1, {1, 1}},
    //     {{{"item1",0},{"item2",1},{"item3",2},{"item4",4}},"Enter Selectbox 03",4, -1, {2, 1}},
    //     {{{"item1",0},{"item2",1},{"item3",2},{"item4",4}},"Enter Selectbox 04",4, -1, {3, 1}},
    //     {{{"item1",0},{"item2",1},{"item3",2},{"item4",4}},"Enter Selectbox 05",4, -1, {4, 1}}
    //};
    while (true)
    {
        void *selectedElement;
        ElementType selectedElementType;

        for (int i = display.start_row; i <= display.end_row; i++)
        {
            if (IsElementSelected(rangebar[i].position,display))
            {
                selectedElement = &rangebar[i];
                selectedElementType = RANGEBAR;
            }
            RenderRangebar(rangebar[i], display);
        }
        if (IsElementSelected(selectbox.position,display))
        {
            selectedElement = &selectbox;
            selectedElementType = SELECTBOX;
        }
        RenderSelectbox(selectbox, display);
        /* for (int i = display.start_row; i <= display.end_row; i++)
        {
            if ((selectbox[i].position.col == display.userPosition.col) && (selectbox[i].position.row == display.userPosition.row))
            {
                selectedElementIndex = i;
                selectedElementType = SELECTBOX;
            }
            PrintSelectbox(selectbox[i], display);
        } */


            if (IsElementSelected(checkbox.position,display))
            {
                selectedElement = &checkbox;
                selectedElementType = CHECKBOX;
            }
            RenderCheckbox(checkbox, display);
        
        RenderFooter(GetKeyHints(selectedElementType));
        if (display.SetValueMode)
            display.SetValueMode = !display.SetValueMode;
        else
        {
            char ch = getch();
            HandleInput(ch, display, selectedElementType, selectedElement, row_count);
        }
    }
    return 0;
}
