#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include "color.h"
#include "form.h"
#include "utilities.cpp"
using namespace std;
bool IsElementSelected(Position position, Display display)
{
    return position.row == display.userPosition.row && position.col == display.userPosition.col;
}
Coordinate GetCenteredCoordinates(int width, int height)
{
    const int mainFormWidth = 120;
    const int mainFormHeight = 30;
    int x = CalculateCenterIndex(mainFormWidth, width) + 3;
    int y = CalculateCenterIndex(mainFormHeight, height) + 1;
    return {x, y};
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
void RenderTable(Table &table, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    elementPos.y += (table.position.row - display.start_row) * 4;
    elementPos.x += (table.position.col) * 54;
    int remainingWidth = table.totalWidth;
    int unassignedColsCount = 0;

    for (int i = 0; i < table.cols_count; i++)
    {
        if (table.colsLength[i] == 0)
        {
            unassignedColsCount++;
        }
        remainingWidth -= table.colsLength[i] + 1;
    }
    remainingWidth--;

    if (unassignedColsCount != 0)
    {
        int defaultColWidth = remainingWidth / unassignedColsCount;
        for (int i = 0; i < table.cols_count; i++)
        {
            if (table.colsLength[i] == 0)
            {
                table.colsLength[i] = defaultColWidth;
            }
        }
    }

    for (int row = table.start_row; row - table.start_row < table.Showed_rows_count && row <= table.rows_count; row++)
    {
        Gotoxy(elementPos.x, elementPos.y + (row-table.start_row) * 2);

        for (int col = 0; col < table.cols_count; col++)
        {
            if (col == 0)
            {
                cout << (row == table.start_row ? "╔" : "╠");
            }
            else
            {
                cout << (row == table.start_row ? "╦" : "╬");
            }

            for (int i = 0; i < table.colsLength[col]; i++)
            {
                cout << "═";
            }
        }
        cout << (row == table.start_row ? "╗" : "╣");

        if (row < table.rows_count)
        {
            Gotoxy(elementPos.x, elementPos.y + (row-table.start_row) * 2 + 1);
            for (int col = 0; col < table.cols_count; col++)
            {
                if (col == 0)
                {
                    cout << "║";
                }

                int contentStart = CalculateCenterIndex(table.colsLength[col], table.Cells[row][col].content.length());
                cout << string(contentStart, ' ') << table.Cells[row][col].content
                     << string(table.colsLength[col] - contentStart - table.Cells[row][col].content.length(), ' ');
                cout << "║";
            }
        }
    }

    Gotoxy(elementPos.x, elementPos.y + table.Showed_rows_count * 2);
    for (int col = 0; col < table.cols_count; col++)
    {
        if (col == 0)
        {
            cout << "╚";
        }
        else
        {
            cout << "╩";
        }
        for (int i = 0; i < table.colsLength[col]; i++)
        {
            cout << "═";
        }
    }
    cout << "╝";
}

void RenderBackground()
{
    Gotoxy(0, 0);
    cout << BG_BLACK << FG_WHITE << blank_form;
}
void RenderButton(Button button, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (IsElementSelected(button.position, display))
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
    if (IsElementSelected(textbox.position, display))
    {
        fg_color = FG_CYAN;
    }
    else
    {
        fg_color = FG_WHITE;
    }
    elementPos.y += (textbox.position.row - display.start_row) * 4;
    elementPos.x += (textbox.position.col) * 54;
    int width = 50;
    int height = 3;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));

    string title = textbox.title.substr(0, 10);
    cout << fg_color << setw(10) << left << title;
    string placeholder;
    if (!textbox.value.empty())
    {
        placeholder = textbox.value;
    }
    else
    {
        placeholder = textbox.placeholder;
    }
    placeholder = placeholder.substr(0, 28);
    cout << fg_color << " " << setw(28) << left << placeholder << FG_WHITE;
}
void RenderRangebar(Rangebar &Rangebar, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (IsElementSelected(Rangebar.position, display))
    {
        fg_color = FG_CYAN;
    }
    else
    {
        fg_color = FG_WHITE;
    }
    elementPos.y += (Rangebar.position.row - display.start_row) * 4;
    elementPos.x += (Rangebar.position.col) * 54;
    int width = 50;
    int height = 3;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    cout << fg_color << Rangebar.text << FG_WHITE;
    Gotoxy(elementPos.x + 14, elementPos.y + (height / 2));
    int dis = Rangebar.max - Rangebar.min;
    float ProgressRate = (Rangebar.value - Rangebar.min) * 1.0 / dis;

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
    if (Rangebar.UsePercentage)
    {
        int percentage = ProgressRate * 100;
        cout << fg_color << percentage << "%" << FG_WHITE;
    }
    else
    {
        cout << fg_color << Rangebar.value << FG_WHITE;
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
void RenderNullElement(Position position, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    elementPos.y += (position.row - display.start_row) * 4;
    elementPos.x += (position.col) * 54;
    int width = 50;
    int height = 3;
    for (int j = 0; j < height; j++)
    {
        Gotoxy(elementPos.x, elementPos.y + j);
        for (int i = 0; i < width; i++)
        {
            cout << " ";
        }
    }
}
void RenderCheckbox(Checkbox &checkbox, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    if (IsElementSelected(checkbox.position, display))
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
    if (IsElementSelected(selectbox.position, display))
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
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    string title = selectbox.title.substr(0, 12);
    cout << fg_color << setw(12) << left << title;
    Gotoxy(elementPos.x + 18, elementPos.y + 1);
    cout << fg_color << "<";
    Gotoxy(elementPos.x + width - 3, elementPos.y + 1);
    cout << fg_color << ">";
    string itemTitle = selectbox.Items[selectbox.SelectedIndex].text.substr(0, 20);
    int x = CalculateCenterIndex(26, itemTitle.length()) + 20;
    Gotoxy(elementPos.x + x, elementPos.y + 1);
    cout << fg_color << selectbox.Items[selectbox.SelectedIndex].text << FG_WHITE;
}
void RenderForm(Form &form, Display &display)
{
    for (int i = display.start_col; i <= display.end_col; i++)
    {
        for (int j = display.start_row; j <= display.end_row; j++)
        {
            Element element = form.ElementsGrid[j][i];
            if (element.ptr != nullptr)
            {
                switch (element.type)
                {
                case CHECKBOX:
                    RenderCheckbox(*((Checkbox *)element.ptr), display);
                    break;
                case SELECTBOX:
                    RenderSelectbox(*((Selectbox *)element.ptr), display);
                    break;
                case RANGEBAR:
                    RenderRangebar(*((Rangebar *)element.ptr), display);
                    break;
                case TEXTBOX:
                    RenderTextbox(*((Textbox *)element.ptr), display);
                    break;
                case BUTTON:
                    RenderButton(*((Button *)element.ptr), display);
                    break;
                case TABLE:
                    RenderTable(*((Table *)element.ptr), display);
                    break;
                }
            }
            else if(form.renderNullElements)
            {
                RenderNullElement({j, i}, display);
            }
        }
    }
}
void ShowMessagebox(Messagebox &messagebox)
{
    int width = 40;
    int height = 10 + messagebox.linesCount;
    int centerIndex;
    Coordinate elementPos = GetCenteredCoordinates(width, height);
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, FG_WHITE);
    switch (messagebox.icon)
    {
    case INFORMATION:
        centerIndex = CalculateCenterIndex(width - 2, 20);
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 1);
        cout << FG_BLUE << R"( ___ _  _ ___ ___  )";
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 2);
        cout << FG_BLUE << R"(|_ _| \| | __/ _ \ )";
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 3);
        cout << FG_BLUE << R"( | || .` | _| (_) |)";
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 4);
        cout << FG_BLUE << R"(|___|_|\_|_| \___/ )";
        break;
    case WARNING:
        centerIndex = CalculateCenterIndex(width - 2, 37);
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 1);
        cout << FG_YELLOW << R"(__      ___   ___ _  _ ___ _  _  ___ )" << FG_WHITE;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 2);
        cout << FG_YELLOW << R"(\ \    / /_\ | _ \ \| |_ _| \| |/ __|)" << FG_WHITE;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 3);
        cout << FG_YELLOW << R"( \ \/\/ / _ \|   / .` || || .` | (_ |)" << FG_WHITE;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 4);
        cout << FG_YELLOW << R"(  \_/\_/_/ \_\_|_\_|\_|___|_|\_|\___|)" << FG_WHITE;
        break;
    case CRITICAL:
        centerIndex = CalculateCenterIndex(width - 2, 23);
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 1);
        cout << FG_RED << R"( ___ ___ ___  ___  ___ )" << FG_WHITE;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 2);
        cout << FG_RED << R"(| __| _ \ _ \/ _ \| _ \)" << FG_WHITE;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 3);
        cout << FG_RED << R"(| _||   /   / (_) |   /)" << FG_WHITE;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 4);
        cout << FG_RED << R"(|___|_|_\_|_\\___/|_|_\)" << FG_WHITE;
        break;
    }
    centerIndex = CalculateCenterIndex(width - 2, messagebox.header.length());
    Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 6);
    cout << FG_WHITE << messagebox.header << FG_WHITE;
    for (int i = 0; i < messagebox.linesCount; i++)
    {
        string text = messagebox.lines[i];
        centerIndex = CalculateCenterIndex(width - 2, text.length());
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 8 + i);
        cout << FG_WHITE << text << FG_WHITE;
    }
    RenderFooter("[Any Key]: Close Messagebox");
    char ch = getch();
}
bool CanAccess(Form &form, Position position)
{
    return position.row >= 0 && position.row < form.rows_count &&
           position.col >= 0 && position.col < form.cols_count;
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
void UpdateRangebarValue(Rangebar &Rangebar, int input)
{
    int dis = Rangebar.max - Rangebar.min;
    int step = (dis < 28) ? 1 : dis / 28;
    if (input == 5 && Rangebar.value > Rangebar.min)
    {
        Rangebar.value -= step;
        if (Rangebar.value < Rangebar.min)
            Rangebar.value = Rangebar.min;
    }
    else if (input == 6 && Rangebar.value < Rangebar.max)
    {
        Rangebar.value += step;
        if (Rangebar.value > Rangebar.max)
            Rangebar.value = Rangebar.max;
    }
}

void ScrollTable(Table &table, int input)
{
    if (input == 5 && table.start_row > 0)
    {
        table.start_row--;
    }
    else if (input == 6 && table.rows_count - table.start_row >= table.Showed_rows_count)
    {
        table.start_row++;
    }
}
void ToggleCheckboxState(Checkbox &checkbox)
{
    checkbox.isChecked = !checkbox.isChecked;
}
void HandleNavigation(char input, Form form, Display &display)
{
    input = tolower(input);
    int visibleRows = display.end_row - display.start_row;
    int visibleCols = display.end_col - display.start_col;
    Position newUserPosition = display.userPosition;
    switch (input)
    {
    case 'w':
        while (newUserPosition.row > 0)
        {
            newUserPosition.row--;
            if (form.ElementsGrid[newUserPosition.row][newUserPosition.col].ptr != nullptr)
                break;
        }
        break;

    case 's':
        while (newUserPosition.row < form.rows_count - 1)
        {
            newUserPosition.row++;
            if (form.ElementsGrid[newUserPosition.row][newUserPosition.col].ptr != nullptr)
                break;
        }
        break;

    case 'a':
        while (newUserPosition.col > 0)
        {
            newUserPosition.col--;
            if (form.ElementsGrid[newUserPosition.row][newUserPosition.col].ptr != nullptr)
                break;
        }
        break;

    case 'd':
        while (newUserPosition.col < form.cols_count - 1)
        {
            newUserPosition.col++;
            if (form.ElementsGrid[newUserPosition.row][newUserPosition.col].ptr != nullptr)
                break;
        }
        break;

    default:
        return;
    }
    if (form.ElementsGrid[newUserPosition.row][newUserPosition.col].ptr != nullptr)
    {
        if (newUserPosition.row < display.start_row)
        {
            display.start_row = max(0, display.start_row - (display.userPosition.row - newUserPosition.row));
            display.end_row = display.start_row + visibleRows;
        }
        else if (newUserPosition.row > display.end_row)
        {
            display.end_row = min(form.rows_count - 1, display.end_row + (newUserPosition.row - display.userPosition.row));
            display.start_row = display.end_row - visibleRows;
        }

        if (newUserPosition.col < display.start_col)
        {
            display.start_col = max(0, display.start_col - (display.userPosition.col - newUserPosition.col));
            display.end_col = display.start_col + visibleCols;
        }
        else if (newUserPosition.col > display.end_col)
        {
            display.end_col = min(form.cols_count - 1, display.end_col + (newUserPosition.col - display.userPosition.col));
            display.start_col = display.end_col - visibleCols;
        }

        display.userPosition = newUserPosition;
    }
}

void GetTextboxValue(Textbox &textbox, Display &display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    string fg_color = "";
    fg_color = FG_YELLOW;
    int width = 50;
    int height = 3;
    elementPos.y += (textbox.position.row - display.start_row) * 4;
    elementPos.x += (textbox.position.col) * 54;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color);
    RenderFooter("[Enter]: Set Value");
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    string title = textbox.title.substr(0, 10);
    cout << fg_color << setw(10) << left << title;
    Gotoxy(elementPos.x + 15, elementPos.y + (height / 2));
    ShowCursor();
    textbox.value = GetInput(30);
    HideCursor();
}
void OnPress6(void *element, ElementType type, Display &display)
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
        UpdateRangebarValue(*((Rangebar *)element), 6);
        break;
    case TEXTBOX:
        GetTextboxValue(*((Textbox *)element), display);
        break;
    case TABLE:
        ScrollTable(*((Table *)element), 6);
        break;
    }
}
void OnPress5(void *element, ElementType type, Display &display)
{
    switch (type)
    {
    case SELECTBOX:
        UpdateSelectBoxSelection(*((Selectbox *)element), 5);
        break;
    case RANGEBAR:
        UpdateRangebarValue(*((Rangebar *)element), 5);
        break;
    case TABLE:
        ScrollTable(*((Table *)element), 5);
        break;
    }
}
void HandleInput(char input, Display &display, Form form)
{
    Element element = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
    if (input == 'x')
    {
        OnPress6(element.ptr, element.type, display);
    }
    else if (input == 'z')
    {
        OnPress5(element.ptr, element.type, display);
    }
    else
    {
        HandleNavigation(input, form, display);
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
    case TEXTBOX:
        result = "[X]: Enter Value";
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

void DeleteElement(Form &form, Position position)
{
    switch (form.ElementsGrid[position.row][position.col].type)
    {
    case CHECKBOX:
        delete (Checkbox *)form.ElementsGrid[position.row][position.col].ptr;
        form.ElementsGrid[position.row][position.col].ptr = nullptr;
        form.ElementsGrid[position.row][position.col].type = NULLELEMENT;
        break;
    case SELECTBOX:
        delete (Selectbox *)form.ElementsGrid[position.row][position.col].ptr;
        form.ElementsGrid[position.row][position.col].ptr = nullptr;
        form.ElementsGrid[position.row][position.col].type = NULLELEMENT;
        break;
    case RANGEBAR:
        delete (Rangebar *)form.ElementsGrid[position.row][position.col].ptr;
        form.ElementsGrid[position.row][position.col].ptr = nullptr;
        form.ElementsGrid[position.row][position.col].type = NULLELEMENT;
        break;
    }
}
void AddElementToForm(Form &form, Element &element, Position position)
{
    if (form.ElementsGrid[position.row][position.col].ptr == nullptr)
    {
        DeleteElement(form, position);
    }
    form.ElementsGrid[position.row][position.col] = element;
};
void AddButtonToForm(Form &form, Button *button)
{
    Element element = {button, BUTTON};
    AddElementToForm(form, element, (*button).position);
}
void AddTextboxToForm(Form &form, Textbox *textbox)
{
    Element element = {textbox, TEXTBOX};
    AddElementToForm(form, element, (*textbox).position);
}
void AddRangebarToForm(Form &form, Rangebar *rangebar)
{
    Element element = {rangebar, RANGEBAR};
    AddElementToForm(form, element, (*rangebar).position);
}
void AddCheckboxToForm(Form &form, Checkbox *checkbox)
{
    Element element = {checkbox, CHECKBOX};
    AddElementToForm(form, element, (*checkbox).position);
}
void AddSelectboxToForm(Form &form, Selectbox *selectbox)
{
    Element element = {selectbox, SELECTBOX};
    AddElementToForm(form, element, (*selectbox).position);
}
void AddTableToForm(Form &form, Table *table)
{
    Element element = {table, TABLE};
    AddElementToForm(form, element, (*table).position);
}
void InitialElementGrid(Form &form)
{
    form.ElementsGrid = new Element *[form.rows_count];
    for (int i = 0; i < form.rows_count; i++)
    {
        form.ElementsGrid[i] = new Element[form.cols_count];
        for (int j = 0; j < form.cols_count; j++)
        {
            form.ElementsGrid[i][j].ptr = nullptr;
            form.ElementsGrid[i][j].type = NULLELEMENT;
        }
    }
}
void FreeElementGrid(Form &form)
{
    for (int i = 0; i < form.rows_count; i++)
    {
        delete[] form.ElementsGrid[i];
    }
    delete[] form.ElementsGrid;
};
void CloseForm(Form &form)
{
    FreeElementGrid(form);
}
/* int main()
{
    system("cls");
    Form form = {"Main", 15, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    HideCursor();
    RenderBackground();
    InitialElementGrid(form);

    Rangebar rangebar = {"FPS:", 10, 30, 24, false, {0, 0}};
    Rangebar rangebar1 = {"Music:", 0, 100, 80, true, {0, 1}};
    Checkbox checkbox = {"VSync", false, {1, 0}};
    Checkbox checkbox1 = {"Motions", false, {1, 1}};
    Checkbox checkbox2 = {"CHeck1", false, {4, 0}};
    Checkbox checkbox3 = {"CHeck2", false, {5, 0}};
    Checkbox checkbox4 = {"CHeck3", false, {6, 0}};
    Checkbox checkbox5 = {"CHeck4", false, {7, 0}};
    Checkbox checkbox6 = {"CHeck5", false, {8, 0}};
    Textbox textbox = {"Username:", "12345678910111213wwwwwwwwwwwwwwwwwww141516171819", "Please Enter Your number", "", false, true, {2, 0}};
    Selectbox selectbox = {{{"Easy", 0}, {"Medium", 1}, {"Hard", 2}, {"Legend", 4}}, "Game Level", 4, 0, {3, 0}};
    Button back = {"Back", {8, 1}};
    AddRangebarToForm(form, &rangebar);
    AddRangebarToForm(form, &rangebar1);
    AddCheckboxToForm(form, &checkbox);
    AddCheckboxToForm(form, &checkbox1);
    // AddCheckboxToForm(form,&checkbox2);
    // AddCheckboxToForm(form,&checkbox3);
    AddCheckboxToForm(form, &checkbox4);
    AddCheckboxToForm(form, &checkbox5);
    AddCheckboxToForm(form, &checkbox6);

    AddTextboxToForm(form, &textbox);
    AddSelectboxToForm(form, &selectbox);
    AddButtonToForm(form, &back);
    Messagebox msg = {"TITLE", {"loermro r r w e ew s gdss gdg sd", "loermro rdddddddw s gdss gdg sd", "loezsfdhdfhdfhw e ew s gdss gdg sd", "loesdfhsdhddhg sd"}, 4, INFORMATION};
    while (true)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        HandleInput(ch, display, form);
    }
    CloseForm(form);
    return 0;
} */
int main()
{
    system("cls");
    Form form = {"Main", 15, 2,false};
    Display display = {0, 4, 0, 1, {0, 0}};
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    HideCursor();
    RenderBackground();
    InitialElementGrid(form);

    Checkbox checkbox = {"VSync", false, {0, 0}};
    Selectbox selectbox = {{{"Easy", 0}, {"Medium", 1}, {"Hard", 2}, {"Legend", 4}}, "Game Level", 4, 0, {0, 1}};
    Table table = {
        104, 17, 3, 0, 7, {0, 50, 0}, {{{"Id"}, {"Name"}, {"Family"}}, {{"1"}, {"mdi"}, {"os"}}, {{"2"}, {"33"}, {"343"}}, {{"3"}, {"mdi"}, {"os"}}, {{"4"}, {"33"}, {"343"}}, {{"5"}, {"mdi"}, {"os"}}, {{"6"}, {"33"}, {"343"}}, {{"7"}, {"mdi"}, {"os"}}, {{"8"}, {"33"}, {"343"}}, {{"9"}, {"mdi"}, {"os"}}, {{"10"}, {"33"}, {"343"}}, {{"11"}, {"mdi"}, {"os"}}, {{"12"}, {"33"}, {"343"}}, {{"13"}, {"mdi"}, {"os"}}, {{"14"}, {"33"}, {"343"}}, {{"15"}, {"mdi"}, {"os"}}, {{"16"}, {"33"}, {"343"}}}, {1, 0}};
    AddCheckboxToForm(form, &checkbox);
    AddSelectboxToForm(form, &selectbox);
    AddTableToForm(form, &table);
    while (true)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        HandleInput(ch, display, form);
    }
    CloseForm(form);
    return 0;
}
