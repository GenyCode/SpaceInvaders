#include <iostream>
#include <windows.h>
#include "form.cpp"
#include "utilities.h"
using namespace std;
void ChoosePlayer()
{
    Form form = {"Choose Player", 5, 2};
    Display display = {0, 4, 0, 1, {0, 0}};

    RenderBackground();
    InitialElementGrid(form);
}
void MainMenu()
{
    Form form = {"MainMenu", 5, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    Button StartGameButton = {"STARTGAME", {0, 0}};
    Button SettingsButton = {"SETTINGS", {1, 0}};
    Button HowToPlayButton = {"HOWTOPLAY", {2, 0}};
    Button ChangeUserButton = {"CHANGE USER", {3, 0}};
    Button ExitButton = {"Exit", {4, 0}};
    RenderBackground();
    InitialElementGrid(form);
    AddButtonToForm(form, &StartGameButton);
    AddButtonToForm(form, &SettingsButton);
    AddButtonToForm(form, &HowToPlayButton);
    AddButtonToForm(form, &ChangeUserButton);
    AddButtonToForm(form, &ExitButton);
    while (true)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        HandleInput(ch, display, form);
    }
}
void GameModesMenu()
{
    Form form = {"Game Modes", 5, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    Button AdventureButton = {"Adventure", {0, 0}};
    Button SurvivalButton = {"Survival", {1, 0}};
    Button CoopButton = {"Co-op", {2, 0}};

    RenderBackground();
    InitialElementGrid(form);
    AddButtonToForm(form, &AdventureButton);
    AddButtonToForm(form, &SurvivalButton);
    AddButtonToForm(form, &CoopButton);
    while (true)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        HandleInput(ch, display, form);
    }
}
void GameplaySettings()
{
}
void GeneralSettings()
{
    Form form = {"Settings", 10, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    Checkbox MusicCheckbox = {"Music", false, {0, 1}};
    Checkbox SoundCheckbox = {"Sound", false, {0, 0}};
    Button KeyBindingsButton = {"Key Bindings", {1, 0}};
    Rangebar FPSRangebar = {" FPS:", 10, 300, 24, false, {2, 0}};
    Selectbox PrimaryColor ={{{"CYAN", 0}, {"BLUE", 1}, {"PURPLE", 2}, {"WHITE", 4}}, "Primary color", 4, -1, {3, 0}};
    Selectbox SecondaryColor ={{{"CYAN", 0}, {"BLUE", 1}, {"PURPLE", 2}, {"WHITE", 4}}, "Secondary color", 4, -1, {3, 1}};
    Button SaveChangesButton = {"Save Changes", {4, 0}};
    Button ResetSettingsButton = {"ResetSettings", {4, 1}};
    RenderBackground();
    InitialElementGrid(form);
    AddCheckboxToForm(form, &MusicCheckbox);
    AddCheckboxToForm(form, &SoundCheckbox);
    AddButtonToForm(form, &KeyBindingsButton);
    AddRangebarToForm(form, &FPSRangebar);
    AddButtonToForm(form, &ResetSettingsButton);
    AddSelectboxToForm(form,&PrimaryColor);
    AddSelectboxToForm(form,&SecondaryColor);
    AddButtonToForm(form, &SaveChangesButton);
    while (true)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        HandleInput(ch, display, form);
    }
}
void HowToPlay()
{
}
int main()
{
    system("cls");
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    HideCursor();
    GeneralSettings();
    return 0;
}