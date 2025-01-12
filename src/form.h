#pragma once
#include <iostream>
#include <Windows.h>
#include "color.h"
using namespace std;
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


struct Button{
    string text;
    int row;
    int col;
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
    int row;
    int col;
};
struct Checkbox{
    string text;
    bool isChecked;
    int row;
    int col;
};
struct RangeBar{
    string text;
    int value;
    int row;
    int col;
};
struct Textbox{
    string text;
    bool IsNumberOnly = false;
    Label ValidationMessage;
    string value = "";
    int row;
    int col;
};
struct Form{
    string title;
    int type = 0;
    int rows_count = 5;
    int cols_count = 0;
};
struct UserState{
    int row;
    int col;
};
