#include <iostream>
#include <windows.h>
#include "form.cpp"
#include "utilities.h"
using namespace std;

void LoadGameMenu(){
    int GameId = 0;
    Form form = {"Load Game", 20, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    InitialElementGrid(form);
    Button LoadGameButtons[20];
    for(int i = 0;i<20;i++){
        string text = "Game " + IntToString(i+1);
        LoadGameButtons[i] ={i,text,{i,0}};
        AddButtonToForm(form,&LoadGameButtons[i]);
    }
    RenderBackground();
    while (form.isRunning)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            Button *button = (Button *)(SelectedElement.ptr);
            GameId = (*button).id;
            break;
        }
        else
        {
            HandleInput(ch, display, form);
        }
    }
    CloseForm(form);
    //LoadGame(GameId);
}
void SurvivalGameplaySettings()
{
    Form form = {"Gameplay Settings", 6, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    Textbox PlayerName = {"Name:", "Enter Your Name", "", "", true, false, {0, 0}};
    Selectbox Level = {{{"Easy", 0}, {"Medium", 1}, {"Hard", 2}}, "Level:", 3, 0, {1, 0}};
    Label Spaceship = {"Spaceship Settings", {2, 0}};
    Selectbox SpaceshipType = {{{"A", 0}, {"B", 1}, {"C", 2}}, "Type:", 3, 0, {3, 0}};
    Selectbox SpaceshipColor = {{{"CYAN", 0}, {"BLUE", 1}, {"GREEN", 2}, {"RED", 2}, {"YELLOW", 3}}, "Color:", 5, 0, {4, 0}};
    Button StartButton = {0, "Start", {5, 0}};
    RenderBackground();
    InitialElementGrid(form);
    AddTextboxToForm(form, &PlayerName);
    AddLabelToForm(form, &Spaceship);
    AddSelectboxToForm(form, &Level);
    AddSelectboxToForm(form, &SpaceshipType);
    AddSelectboxToForm(form, &SpaceshipColor);
    AddButtonToForm(form, &StartButton);
    while (form.isRunning)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        HandleInput(ch, display, form);
    }
    CloseForm(form);
}
void CoopGameplaySettings()
{
    Form form = {"Gameplay Settings", 6, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    Selectbox Level = {{{"Easy", 0}, {"Medium", 1}, {"Hard", 2}}, "Level:", 3, 0, {0, 0}};
    Label Spaceship1 = {"Player1", {1, 0}};
    Selectbox SpaceshipType1 = {{{"A", 0}, {"B", 1}, {"C", 2}}, "Type:", 3, 0, {3, 0}};
    Selectbox SpaceshipColor1 = {{{"CYAN", 0}, {"BLUE", 1}, {"GREEN", 2}, {"RED", 2}, {"YELLOW", 3}}, "Color:", 5, 0, {4, 0}};
    Textbox PlayerName1 = {"Name:", "Enter Your Name", "", "", true, false, {2, 0}};
    Label Spaceship2 = {"Player2", {1, 1}};
    Selectbox SpaceshipType2 = {{{"A", 0}, {"B", 1}, {"C", 2}}, "Type:", 3, 0, {3, 1}};
    Selectbox SpaceshipColor2 = {{{"CYAN", 0}, {"BLUE", 1}, {"GREEN", 2}, {"RED", 2}, {"YELLOW", 3}}, "Color:", 5, 0, {4, 1}};
    Textbox PlayerName2 = {"Name:", "Enter Your Name", "", "", true, false, {2, 1}};
    Button StartButton = {0, "Start", {5, 0}};
    RenderBackground();
    InitialElementGrid(form);
    AddTextboxToForm(form, &PlayerName1);
    AddTextboxToForm(form, &PlayerName2);
    AddLabelToForm(form, &Spaceship1);
    AddLabelToForm(form, &Spaceship2);
    AddSelectboxToForm(form, &Level);
    AddSelectboxToForm(form, &SpaceshipType1);
    AddSelectboxToForm(form, &SpaceshipColor1);
    AddSelectboxToForm(form, &SpaceshipType2);
    AddSelectboxToForm(form, &SpaceshipColor2);
    AddButtonToForm(form, &StartButton);
    while (form.isRunning)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        HandleInput(ch, display, form);
    }
    CloseForm(form);
}
void CustomGameplaySettings()
{
    Form form = {"Gameplay Settings", 8, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    Textbox PlayerName = {"Name:", "Enter Your Name", "", "", true, false, {0, 0}};
    Label Spaceship = {"Spaceship Settings", {1, 0}};
    Selectbox SpaceshipType = {{{"A", 0}, {"B", 1}, {"C", 2}}, "Type:", 3, 0, {2, 0}};
    Selectbox SpaceshipColor = {{{"CYAN", 0}, {"BLUE", 1}, {"GREEN", 2}, {"RED", 2}, {"YELLOW", 3}}, "Color:", 5, 0, {3, 0}};
    Label Level = {"Level Settings", {1, 1}};
    Rangebar Time = {"Time:", 0, 10, 5, false, {4, 1}};
    Rangebar Health = {"Health:", 100, 300, 150, false, {2, 1}};
    Rangebar Bullets = {"Bullets:", 25, 100, 50, false, {3, 1}};
    Button StartButton = {0, "Start", {4, 0}};
    RenderBackground();
    InitialElementGrid(form);
    AddTextboxToForm(form, &PlayerName);
    AddLabelToForm(form, &Spaceship);
    AddLabelToForm(form, &Level);
    AddSelectboxToForm(form, &SpaceshipType);
    AddSelectboxToForm(form, &SpaceshipColor);
    AddRangebarToForm(form, &Time);
    AddRangebarToForm(form, &Health);
    AddRangebarToForm(form, &Bullets);
    AddButtonToForm(form, &StartButton);
    while (form.isRunning)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        HandleInput(ch, display, form);
    }
    CloseForm(form);
}
void GameModesMenu()
{
    Form form = {"Game Modes", 5, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    Button SurvivalButton = {0, "Survival", {0, 0}};
    Button CustomGameButton = {1, "Custom Game", {1, 0}};
    Button CoopButton = {2, "Co-op", {2, 0}};

    RenderBackground();
    InitialElementGrid(form);
    AddButtonToForm(form, &SurvivalButton);
    AddButtonToForm(form, &CustomGameButton);
    AddButtonToForm(form, &CoopButton);
    while (form.isRunning)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            Button *button = (Button *)(SelectedElement.ptr);
            switch ((*button).id)
            {
            case 0:
                SurvivalGameplaySettings();
                break;
            case 1:
                CustomGameplaySettings();
                break;
            case 2:
                CoopGameplaySettings();
                break;
            }
        }
        else
        {
            HandleInput(ch, display, form);
        }
    }
}
void KeyBindings()
{
    Form form = {"Key Bindings", 5, 2};
    Label Player1 = {"Player1", {0, 0}};
    Label Player2 = {"Player2", {0, 1}};
    Display display = {0, 4, 0, 1, {1, 0}};
    Keybox Left_Player1 = {"Move Left:", 'A', {1, 0}};
    Keybox Right_Player1 = {"Move Right:", 'D', {2, 0}};
    Keybox Shoot_Player1 = {"Shoot:", ' ', {3, 0}};
    Keybox Left_Player2 = {"Move Left:", 'J', {1, 1}};
    Keybox Right_Player2 = {"Move Right:", 'L', {2, 1}};
    Keybox Shoot_Player2 = {"Shoot:", '\r', {3, 1}};

    RenderBackground();
    InitialElementGrid(form);
    AddKeyboxToForm(form, &Left_Player1);
    AddKeyboxToForm(form, &Right_Player1);
    AddKeyboxToForm(form, &Shoot_Player1);
    AddKeyboxToForm(form, &Left_Player2);
    AddKeyboxToForm(form, &Right_Player2);
    AddKeyboxToForm(form, &Shoot_Player2);
    AddLabelToForm(form, &Player1);
    AddLabelToForm(form, &Player2);
    while (form.isRunning)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        HandleInput(ch, display, form);
    }
    CloseForm(form);
}
void GeneralSettings()
{
    Form form = {"Settings", 10, 2};
    Display display = {0, 4, 0, 1, {1, 0}};
    Label AudioSettings = {"Audio Settings", {0, 0}};
    Checkbox MusicCheckbox = {"Music", false, {1, 1}};
    Checkbox SoundCheckbox = {"Sound", false, {1, 0}};
    Button KeyBindingsButton = {0, "Key Bindings", {2, 0}};
    Label Colors = {"Colors", {3, 0}};
    Selectbox PrimaryColor = {{{"CYAN", 0}, {"BLUE", 1}, {"PURPLE", 2}, {"WHITE", 4}}, "Primary", 4, 0, {4, 0}};
    Selectbox SecondaryColor = {{{"CYAN", 0}, {"BLUE", 1}, {"PURPLE", 2}, {"WHITE", 4}}, "Secondary", 4, 0, {4, 1}};
    Button SaveChangesButton = {1, "Save Changes", {5, 0}};
    Button ResetSettingsButton = {2, "ResetSettings", {5, 1}};
    RenderBackground();
    InitialElementGrid(form);
    AddCheckboxToForm(form, &MusicCheckbox);
    AddCheckboxToForm(form, &SoundCheckbox);
    AddLabelToForm(form, &AudioSettings);
    AddLabelToForm(form, &Colors);
    AddButtonToForm(form, &KeyBindingsButton);
    AddButtonToForm(form, &ResetSettingsButton);
    AddSelectboxToForm(form, &PrimaryColor);
    AddSelectboxToForm(form, &SecondaryColor);
    AddButtonToForm(form, &SaveChangesButton);
    while (form.isRunning)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            Button *button = (Button *)(SelectedElement.ptr);
            switch ((*button).id)
            {
            case 0:
                KeyBindings();
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            }
        }
        else
        {
            HandleInput(ch, display, form);
        }
    }
    CloseForm(form);
}
void HowToPlay()
{
    Messagebox howToPlay = {"How To Play",
                            {"Objective: Shoot all aliens before they reach you.",
                             "Controls: Move with arrow keys, shoot with spacebar.",
                             "Tips: Use shields for cover and shoot bonus UFOs for extra points.",
                             "Game Over: Lose if aliens reach your base or you run out of lives."},
                            4,
                            INFORMATION,
                            true};
    ShowMessageBox(howToPlay);
}
void MainMenu()
{
    Form form = {"Main Menu", 5, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    Button NewGameButton = {0, "New Game", {0, 0}};
    Button LoadGameButton = {1, "Load Game", {1, 0}};
    Button SettingsButton = {2, "Settings", {2, 0}};
    Button HowToPlayButton = {3, "How to play", {3, 0}};
    Button ExitButton = {4, "Exit", {4, 0}};
    RenderBackground();
    InitialElementGrid(form);
    AddButtonToForm(form, &NewGameButton);
    AddButtonToForm(form, &LoadGameButton);
    AddButtonToForm(form, &SettingsButton);
    AddButtonToForm(form, &HowToPlayButton);
    AddButtonToForm(form, &ExitButton);
    while (form.isRunning)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));

        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            Button *button = (Button *)(SelectedElement.ptr);
            switch ((*button).id)
            {
            case 0:
                GameModesMenu();
                break;
            case 1:
            LoadGameMenu();
                break;
            case 2:
                GeneralSettings();
                break;
            case 3:
                HowToPlay();
                RenderBackground();
                continue;
                break;
            case 4:
                form.isRunning = false;
                break;
            }
        }
        else
        {
            HandleInput(ch, display, form);
        }
    }
    CloseForm(form);
}
int main()
{
    system("cls");
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    HideCursor();
    MainMenu();
    return 0;
}