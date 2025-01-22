#include <iostream>
#include <windows.h>
#include "form.cpp"
#include "utilities.h"
#include "Settings.h"
#include "Settings.cpp"
using namespace std;

void LoadGameMenu()
{
    int GameId = 0;
    Form form = {"Load Game", 20, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    InitialElementGrid(form);
    Button LoadGameButtons[20];
    for (int i = 0; i < 20; i++)
    {
        string text = "Game " + IntToString(i + 1);
        LoadGameButtons[i] = {text, {i, 0}, true, i};
        AddButtonToForm(form, &LoadGameButtons[i]);
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
    // LoadGame(GameId);
}
void SurvivalGameplaySettings()
{
    Form form = {"Gameplay Settings", 7, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    Textbox PlayerName = {"Name:", "Enter Your Name", "", "", true, false, {0, 0}};
    Selectbox Level = {{{"Easy", 0}, {"Medium", 1}, {"Hard", 2}}, "Level:", 3, 0, {1, 0}};
    Label SpaceshipLabel = {{"Spaceship Settings", 18}, 1, {2, 0}};
    Label Spaceship1 = {{{"█   █", 5}, {"█▄▄▄█", 5}}, 2, {3, 0}, 2};
    Label Spaceship2 = {{{"▲ ▲ ▲", 5}, {"█▄█▄█", 5}}, 2, {3, 0}, 2};
    Label Spaceship3 = {{{"≶ ⭻ ≷", 5}, {"█▒█▒█", 5}}, 2, {3, 0}, 2};
    Label SelectedSpaceship = Spaceship1;
    Selectbox SpaceshipType = {{{"A", 0}, {"B", 1}, {"C", 2}}, "Type:", 3, 0, {5, 0}};
    Selectbox SpaceshipColor = {{{"CYAN", 0}, {"BLUE", 1}, {"GREEN", 2}, {"RED", 2}, {"YELLOW", 3}}, "Color:", 5, 0, {6, 0}};
    Button StartButton = {"Start", {5, 0}, true, 0};
    InitialElementGrid(form);
    AddTextboxToForm(form, &PlayerName);
    AddLabelToForm(form, &SpaceshipLabel);
    AddLabelToForm(form, &SelectedSpaceship);
    AddSelectboxToForm(form, &Level);
    AddSelectboxToForm(form, &SpaceshipType);
    AddSelectboxToForm(form, &SpaceshipColor);
    AddButtonToForm(form, &StartButton);
    while (form.isRunning)
    {
        if (form.renderBackground)
        {
            RenderBackground();
            form.renderBackground = false;
        }
        switch (SpaceshipType.SelectedIndex)
        {
        case 0:
            SelectedSpaceship = Spaceship1;
            break;
        case 1:
            SelectedSpaceship = Spaceship2;
            break;
        case 2:
            SelectedSpaceship = Spaceship3;
            break;
        }
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
    Label Spaceship1 = {{"Player1", 7}, 1, {1, 0}};
    Selectbox SpaceshipType1 = {{{"A", 0}, {"B", 1}, {"C", 2}}, "Type:", 3, 0, {3, 0}};
    Selectbox SpaceshipColor1 = {{{"CYAN", 0}, {"BLUE", 1}, {"GREEN", 2}, {"RED", 2}, {"YELLOW", 3}}, "Color:", 5, 0, {4, 0}};
    Textbox PlayerName1 = {"Name:", "Enter Your Name", "", "", true, false, {2, 0}};
    Label Spaceship2 = {{"Player2", 7}, 1, {1, 1}};
    Selectbox SpaceshipType2 = {{{"A", 0}, {"B", 1}, {"C", 2}}, "Type:", 3, 0, {3, 1}};
    Selectbox SpaceshipColor2 = {{{"CYAN", 0}, {"BLUE", 1}, {"GREEN", 2}, {"RED", 2}, {"YELLOW", 3}}, "Color:", 5, 0, {4, 1}};
    Textbox PlayerName2 = {"Name:", "Enter Your Name", "", "", true, false, {2, 1}};
    Button StartButton = {"Start", {5, 0}, true, 0};
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
        if (form.renderBackground)
        {
            RenderBackground();
            form.renderBackground = false;
        }
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
    Label Spaceship = {{"Spaceship Settings", 18}, 1, {1, 0}};
    Selectbox SpaceshipType = {{{"A", 0}, {"B", 1}, {"C", 2}}, "Type:", 3, 0, {2, 0}};
    Selectbox SpaceshipColor = {{{"CYAN", 0}, {"BLUE", 1}, {"GREEN", 2}, {"RED", 2}, {"YELLOW", 3}}, "Color:", 5, 0, {3, 0}};
    Label Level = {{"Level Settings", 14}, 1, {1, 1}};
    Rangebar Time = {"Time:", 0, 10, 5, false, {4, 1}};
    Rangebar Health = {"Health:", 100, 300, 150, false, {2, 1}};
    Rangebar Bullets = {"Bullets:", 25, 100, 50, false, {3, 1}};
    Button StartButton = {"Start", {4, 0}, true, 0};
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
        if (form.renderBackground)
        {
            RenderBackground();
            form.renderBackground = false;
        }
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
    Button SurvivalButton = {"Survival", {0, 0}, true, 0};
    Button CustomGameButton = {"Custom Game", {1, 0}, true, 1};
    Button CoopButton = {"Co-op", {2, 0}, true, 2};

    InitialElementGrid(form);
    AddButtonToForm(form, &SurvivalButton);
    AddButtonToForm(form, &CustomGameButton);
    AddButtonToForm(form, &CoopButton);
    while (form.isRunning)
    {
        if (form.renderBackground)
        {
            RenderBackground();
            form.renderBackground = false;
        }
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
                form.renderBackground = true;
                break;
            case 1:
                CustomGameplaySettings();
                form.renderBackground = true;
                break;
            case 2:
                CoopGameplaySettings();
                form.renderBackground = true;
                break;
            }
        }
        else
        {
            HandleInput(ch, display, form);
        }
    }
}
void KeyBindings(Keybindings &keybindings)
{
    Form form = {"Key Bindings", 5, 2};
    Label Player1 = {{"Player1", 7}, 1, {0, 0}};
    Label Player2 = {{"Player2", 7}, 1, {0, 1}};
    Display display = {0, 4, 0, 1, {1, 0}};
    Keybox Left_Player1 = {"Move Left:", keybindings.Left_Player1, {1, 0}};
    Keybox Right_Player1 = {"Move Right:", keybindings.Right_Player1, {2, 0}};
    Keybox Shoot_Player1 = {"Shoot:", keybindings.Shoot_Player1, {3, 0}};
    Keybox Left_Player2 = {"Move Left:", keybindings.Left_Player2, {1, 1}};
    Keybox Right_Player2 = {"Move Right:", keybindings.Right_Player2, {2, 1}};
    Keybox Shoot_Player2 = {"Shoot:", keybindings.Shoot_Player2, {3, 1}};
    Button BackButton = {"Back", {4, 0}, true, 0};
    InitialElementGrid(form);
    AddKeyboxToForm(form, &Left_Player1);
    AddKeyboxToForm(form, &Right_Player1);
    AddKeyboxToForm(form, &Shoot_Player1);
    AddKeyboxToForm(form, &Left_Player2);
    AddKeyboxToForm(form, &Right_Player2);
    AddKeyboxToForm(form, &Shoot_Player2);
    AddLabelToForm(form, &Player1);
    AddLabelToForm(form, &Player2);
    AddButtonToForm(form, &BackButton);
    while (form.isRunning)
    {
        if (form.renderBackground)
        {
            RenderBackground();
            form.renderBackground = false;
        }
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type));
        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            break;
        }
        HandleInput(ch, display, form);
    }

    keybindings.Left_Player1 = Left_Player1.value;
    keybindings.Right_Player1 = Right_Player1.value;
    keybindings.Shoot_Player1 = Shoot_Player1.value;
    keybindings.Left_Player2 = Left_Player2.value;
    keybindings.Right_Player2 = Right_Player2.value;
    keybindings.Shoot_Player2 = Shoot_Player2.value;

    CloseForm(form);
}
void GeneralSettings()
{
    Generalsettings generalsettings;
    LoadSettings(generalsettings);
    Form form = {"Settings", 10, 2};
    Display display = {0, 4, 0, 1, {1, 0}};
    Label AudioSettings = {{"Audio Settings", 14}, 1, {0, 0}};
    Checkbox MusicCheckbox = {"Music", false, {1, 1}};
    Checkbox SoundCheckbox = {"Sound", false, {1, 0}};
    Button KeyBindingsButton = {"Key Bindings", {2, 0}, true, 0};
    Label Colors = {{"Colors", 6}, 1, {3, 0}};
    Selectbox PrimaryColor = {{{"CYAN", 0}, {"BLUE", 1}, {"PURPLE", 2}, {"WHITE", 3}}, "Primary", 4, 0, {4, 0}};
    Selectbox SecondaryColor = {{{"CYAN", 0}, {"BLUE", 1}, {"PURPLE", 2}, {"WHITE", 3}}, "Secondary", 4, 0, {4, 1}};
    Button SaveChangesButton = {"Save Changes", {5, 0}, true, 1};
    Button ResetSettingsButton = {"ResetSettings", {5, 1}, true, 2};
    MusicCheckbox.isChecked = generalsettings.Music;
    SoundCheckbox.isChecked = generalsettings.Sound;
    PrimaryColor.SelectedIndex = GetItemIndexByValue(PrimaryColor, generalsettings.PrimaryColor);
    SecondaryColor.SelectedIndex = GetItemIndexByValue(SecondaryColor, generalsettings.SecondaryColor);
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
        if (form.renderBackground)
        {
            RenderBackground();
            form.renderBackground = false;
        }
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
                KeyBindings(generalsettings.keybindings);
                break;
            case 1:
                generalsettings.Music = MusicCheckbox.isChecked;
                generalsettings.Sound = SoundCheckbox.isChecked;
                generalsettings.PrimaryColor = PrimaryColor.Items[PrimaryColor.SelectedIndex].value;
                generalsettings.SecondaryColor = SecondaryColor.Items[SecondaryColor.SelectedIndex].value;
                SaveSettings(generalsettings);

                form.isRunning = false;
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
    Button NewGameButton = {"New Game", {0, 0}, true, 0};
    Button LoadGameButton = {"Load Game", {1, 0}, true, 1};
    Button SettingsButton = {"Settings", {2, 0}, true, 2};
    Button HowToPlayButton = {"How to play", {3, 0}, true, 3};
    Button ExitButton = {"Exit", {4, 0}, true, 4};
    InitialElementGrid(form);
    AddButtonToForm(form, &NewGameButton);
    AddButtonToForm(form, &LoadGameButton);
    AddButtonToForm(form, &SettingsButton);
    AddButtonToForm(form, &HowToPlayButton);
    AddButtonToForm(form, &ExitButton);
    while (form.isRunning)
    {
        if (form.renderBackground)
        {
            RenderBackground();
            form.renderBackground = false;
        }
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
                form.renderBackground = true;
                break;
            case 1:
                LoadGameMenu();
                form.renderBackground = true;
                break;
            case 2:
                GeneralSettings();
                form.renderBackground = true;
                break;
            case 3:
                HowToPlay();
                form.renderBackground = true;
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