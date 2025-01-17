#pragma once
#include <iostream>
#include "utilities.h"
#include "color.h"
using namespace std;
const Coordinate start_area = {12, 8};
const Coordinate end_area = {116, 25};
const Coordinate footer_area = {12, 29};
string blank_form = R"(
    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║       _______  _____  _______ _______ _______      _____ __   _ _    _ _______ ______  _______  ______ _______       ║
    ║       |______ |_____] |_____| |       |______        |   | \  |  \  /  |_____| |     \ |______ |_____/ |______       ║
    ║       ______| |       |     | |_____  |______      __|__ |  \_|   \/   |     | |_____/ |______ |    \_ ______|       ║
    ║                                                                                                                      ║
    ╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣
    ║                                                                                                                      ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝)";

enum ElementType
{
    BUTTON,
    TEXTBOX,
    CHECKBOX,
    SELECTBOX,
    RANGEBAR,
    TABLE,
    KEYBOX,
    LABEL,
    NULLELEMENT
};
enum MessageboxIcon
{
    NONE,
    INFORMATION,
    WARNING,
    CRITICAL,
};
struct Position
{
    int row;
    int col;
};
struct TableCell
{
    string content;
};
struct Label{
    string text;
    Position position;
};
struct Table
{
    int totalWidth;
    int rows_count;
    int cols_count;
    int start_row;
    int Showed_rows_count;
    int colsLength[5] = {0};
    TableCell Cells[20][5];
    Position position;
};
struct Display
{
    int start_row = 0;
    int end_row = 4;
    int start_col = 0;
    int end_col = 1;
    Position userPosition = {0, 0};
};
struct Button
{
    int id;
    string text;
    Position position;
};
struct SelectboxItem
{
    string text;
    int value;
};
struct Selectbox
{
    SelectboxItem Items[10];
    string title = "";
    int ItemsCount = 0;
    int SelectedIndex = 0;
    Position position;
};
struct Checkbox
{
    string text;
    bool isChecked;
    Position position;
};
struct Rangebar
{
    string text;
    int min = 0;
    int max = 100;
    int value;
    bool UsePercentage = false;
    Position position;
};
struct Textbox
{
    string title;
    string placeholder;
    string validationMessage;
    string value = "";
    bool CanEdit = true;
    bool IsNumberOnly = false;
    Position position;
};
struct Element
{
    void *ptr;
    ElementType type;
};
struct Form
{
    string title;
    int rows_count = 5;
    int cols_count = 1;
    bool renderNullElements = true;
    bool isCenter = true;
    bool isRunning = true;
    Element **ElementsGrid;
};
struct Keybox
{
    string title;
    char value;
    Position position;
};

struct Messagebox
{
    string header = "";
    string lines[10];
    int linesCount = 0;
    MessageboxIcon icon = NONE;
    bool Enabled = false;
};
bool IsElementSelected(Position position, Display display);

void DrawBox(int width, int height, string fg_color);
void RenderBackground();
void RenderButton(Button button, Display display);
void RenderTextbox(Textbox &textbox, Display display);
void RenderRangebar(Rangebar &Rangebar, Display display);
void RenderFooter(string text);
void RenderNullElement(Position position, Display display);
void RenderCheckbox(Checkbox &checkbox, Display display);
void RenderSelectbox(Selectbox &selectbox, Display display);
void RenderForm(Form &form, Display &display);

bool CanAccess(Form &form, Position position);
void UpdateSelectBoxSelection(Selectbox &selectbox, int input);
void UpdateRangebarValue(Rangebar &Rangebar, int input);
void ToggleCheckboxState(Checkbox &checkbox);
void HandleNavigation(char input, Form form, Display &display);
void GetTextboxValue(Textbox &textbox, Display &display);
void OnPress6(void *element, ElementType type, Display &display);
void OnPress5(void *element, ElementType type, Display &display);

void HandleInput(char input, Display &display, Form &form);
string GetKeyHints(ElementType type);

void DeleteElement(Form &form, Position position);
void AddElementToForm(Form &form, Element &element, Position position);
void AddButtonToForm(Form &form, Button *button);
void AddTextboxToForm(Form &form, Textbox *textbox);
void AddRangebarToForm(Form &form, Rangebar *rangebar);
void AddCheckboxToForm(Form &form, Checkbox *checkbox);
void AddSelectboxToForm(Form &form, Selectbox *selectbox);
void InitialElementGrid(Form &form);
void FreeElementGrid(Form &form);
void CloseForm(Form &form);