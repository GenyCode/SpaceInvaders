#pragma once
#include <iostream>
#include "color.h"
using namespace std;
struct Keybindings {
    char Left_Player1 = 'A';
    char Right_Player1 = 'D';
    char Shoot_Player1 = ' ';
    char Left_Player2 = 'J';
    char Right_Player2 = 'L';
    char Shoot_Player2 = '\r';
};

struct Generalsettings {
    bool Music = true;
    bool Sound = true;
    int PrimaryColor = 333;
    int SecondaryColor = 2553;
    Keybindings keybindings;
};

void SaveSettings(const Generalsettings &settings);
void LoadSettings(Generalsettings &settings);