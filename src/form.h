#pragma once
#include <iostream>
#include "utilities.h"
#include "color.h"
using namespace std;
const Coordinate start_area = {12,8};
const Coordinate end_area = {116,25};
const Coordinate footer_area = {12,28};
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

struct Position{
    int row;
    int col;
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
    int ItemsCount = 0;
    int SelectedIndex = 0;
    Position position;
};
struct Checkbox{
    string text;
    bool isChecked;
    Position position;
};
struct RangeBar{
    string text;
    int value;
    Position position;
};
struct Textbox{
    string text;
    bool IsNumberOnly = false;
    Label ValidationMessage;
    string value = "";
    Position position;
};
struct Form{
    string title;
    int type = 0;
    int rows_count = 5;
    int cols_count = 0;
};
