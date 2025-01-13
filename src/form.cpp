#include <iostream>
#include <Windows.h>
#include "color.h"
#include "form.h"
#include "utilities.cpp"
#include <conio.h>
using namespace std;
bool IsElementSelected(Position position, Display display)
{
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
// TODO: کاربر میتونه روی المنتی که وجود نداره حرکت کنه، این باگ هست
bool CanAccess(Form &form, Position position){
    return position.row >= 0 && position.row < form.rows_count &&
    position.col >= 0 && position.col < form.cols_count;
}
void HandleNavigation(char input, Form form, Display &display)
{
    if (isupper(input))
    {
        input = tolower(input);
    }
    int distance = display.end_row - display.start_row;
    Position newUserPosition = display.userPosition;
    switch (input)
    {
    case 'w':
        if (display.userPosition.row > 0)
        {
            do
            {
                newUserPosition.row--;
            } while (newUserPosition.row > 0 && form.ElementsGrid[newUserPosition.row][newUserPosition.col].ptr == nullptr);
            if (form.ElementsGrid[newUserPosition.row][newUserPosition.col].ptr != nullptr)
            {
                if (newUserPosition.row < display.start_row)
                {
                    display.start_row--;
                    display.end_row--;
                }
                display.userPosition = newUserPosition;
            }
        }

        break;
    case 's':
        if (display.userPosition.row < form.rows_count - 1)
        {
            do
            {
                newUserPosition.row++;
            } while (display.userPosition.row < form.rows_count - 1 && form.ElementsGrid[newUserPosition.row][newUserPosition.col].ptr == nullptr);
            if (form.ElementsGrid[newUserPosition.row][newUserPosition.col].ptr != nullptr)
            {
                if (display.userPosition.row > display.end_row)
                {
                    display.start_row++;
                    display.end_row++;
                }
                display.userPosition = newUserPosition;
            }
        }

        break;
    case 'a':
        if (display.userPosition.col > 0)
        {
            do
            {
                newUserPosition.col--;
            } while (newUserPosition.col > 0 && form.ElementsGrid[newUserPosition.col][newUserPosition.col].ptr == nullptr);
            if (form.ElementsGrid[newUserPosition.col][newUserPosition.col].ptr != nullptr)
            {
                if (newUserPosition.col < display.start_col)
                {
                    display.start_col--;
                    display.end_col--;
                }
                display.userPosition = newUserPosition;
            }
        }
        break;
    case 'd':
        if (display.userPosition.col < form.cols_count - 1)
        {
            do
            {
                newUserPosition.col++;
            } while (display.userPosition.col < form.cols_count - 1 && form.ElementsGrid[newUserPosition.col][newUserPosition.col].ptr == nullptr);
            if (form.ElementsGrid[newUserPosition.col][newUserPosition.col].ptr != nullptr)
            {
                if (display.userPosition.col > display.end_col)
                {
                    display.start_col++;
                    display.end_col++;
                }
                display.userPosition = newUserPosition;
            }
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
void UpdateRangebarValue(Rangebar &Rangebar, int input)
{
    int dis = Rangebar.max - Rangebar.min;
    int step = dis / 28;
    if (input == 5 && Rangebar.value != 0)
    {
        Rangebar.value -= step;
        if (Rangebar.value < 0)
            Rangebar.value = 0;
    }
    else if (input == 6 && Rangebar.value != Rangebar.max)
    {
        Rangebar.value += step;
        if (Rangebar.value > Rangebar.max)
            Rangebar.value = Rangebar.max;
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
        UpdateRangebarValue(*((Rangebar *)element), 6);
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
        UpdateRangebarValue(*((Rangebar *)element), 5);
        break;
    }
}
void HandleInput(char input, Display &display, Form form)
{
    Element element = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
    if (input == 'x')
    {
        OnPress6(element.ptr, element.type);
    }
    else if (input == 'z')
    {
        OnPress5(element.ptr, element.type);
    }
    else
    {
        HandleNavigation(input, form ,display);
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
                }
            }
        }
    }
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
void AddButtonToForm(Form &form, Button* button, Position position)
{
    (*button).position = position;
    Element element = {button, BUTTON};
    AddElementToForm(form, element, position);
}
void AddTextboxToForm(Form &form, Textbox* textbox, Position position)
{
    (*textbox).position = position;
    Element element = {textbox, TEXTBOX};
    AddElementToForm(form, element, position);
}
void AddRangebarToForm(Form &form, Rangebar* rangebar, Position position)
{
    (*rangebar).position = position;
    Element element = {rangebar, RANGEBAR};
    AddElementToForm(form, element, position);
}
void AddCheckboxToForm(Form &form, Checkbox* checkbox, Position position)
{
    (*checkbox).position = position;
    Element element = {checkbox, CHECKBOX};
    AddElementToForm(form, element, position);
}
void AddSelectboxToForm(Form &form, Selectbox* selectbox, Position position)
{
(*selectbox).position = position;
    Element element = {selectbox, SELECTBOX};
    AddElementToForm(form, element, position);
}
void InitialElementGrid(Form &form){
    form.ElementsGrid = new Element*[form.rows_count];
    for(int i = 0;i<form.rows_count;i++){
        form.ElementsGrid[i] = new Element[form.cols_count];
        for(int j = 0; j <form.cols_count;j++){
            form.ElementsGrid[i][j].ptr = nullptr;
            form.ElementsGrid[i][j].type = NULLELEMENT;
        }
    }
    
}
int main()
{
    system("cls");
     Form form ={"Main",10,2};
    Display display = {0,4,0,1,false,{0,0}};
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    HideCursor();
    RenderBackground();
    InitialElementGrid(form);
    //AddCheckboxToForm(form,new Checkbox{"Feature 01", false}, {0, 0});
    Rangebar* rangebar= new Rangebar{"Sound2:", 0, 200, 50, true};
    Checkbox* checkboxs[5] = {
        {new Checkbox{"Feature 00", false}},
        {new Checkbox{"Feature 01", false}},
        {new Checkbox{"Feature 02", false}},
        {new Checkbox{"Feature 03", false}},
        {new Checkbox{"Feature 04", false}}
    };
    Selectbox* selectbox = new Selectbox{{{"item1", 0}, {"item2", 1}, {"item3", 2}, {"item4", 4}}, "Enter Selectbox 01", 4, -1, {3, 0}};
    AddRangebarToForm(form,rangebar,{1,0});
    AddCheckboxToForm(form,checkboxs[0], {0, 0});
    AddCheckboxToForm(form,checkboxs[2], {2, 0});
    //AddCheckboxToForm(form,checkboxs[3], {3, 0});
    AddCheckboxToForm(form,checkboxs[4], {4, 0});
    AddSelectboxToForm(form,selectbox,{0, 1});
    while (true)
    {
       
        RenderForm(form,display);
    Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        if (display.SetValueMode)
            display.SetValueMode = !display.SetValueMode;
        else
        {
            char ch = getch();
            HandleInput(ch, display, form);
        }
    }
    return 0;
}
