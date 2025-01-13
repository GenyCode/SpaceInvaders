#pragma once
#include <iostream>
#include "utilities.h"
#include "color.h"
using namespace std;
const Coordinate start_area = {12,8};
const Coordinate end_area = {116,25};
const Coordinate footer_area = {12,29};
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
    NULLELEMENT
};
struct Position{
    int row;
    int col;
};
struct Display{
    int start_row = 0;
    int end_row = 4;
    int start_col = 0;
    int end_col = 1;
    Position userPosition = {0, 0};
};
struct Button{
    string text;
    Position position;
};
struct Label{
    string text;
};
struct SelectboxItem{
    string text;
    int value;
};
struct Selectbox{
    SelectboxItem Items[10];
    string placeholder = "";
    int ItemsCount = 0;
    int SelectedIndex = -1;
    Position position;
};
struct Checkbox{
    string text;
    bool isChecked;
    Position position;
};
struct Rangebar{
    string text;
    int min = 0;
    int max = 100;
    int value;
    bool UsePercentage = false;
    Position position;
};
struct Textbox{
    string placeholder;
    bool IsNumberOnly = false;
    string ValidationMessage;
    string value = "";
    bool CanEdit = true;
    Position position;
};
struct Element{
    void* ptr;
    ElementType type;
};

struct Form{
    string title;
    int rows_count = 5;
    int cols_count = 1;
    Element** ElementsGrid;
};
