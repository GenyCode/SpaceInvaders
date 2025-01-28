#include <iostream>
#include <cmath>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>
#include <chrono>
//#include "utilities.cpp"
#include "game.h"
#include "color.h"
#include "settings.cpp"
#include "form.cpp"
void DrawEnemies(EnemiesData &data);
Generalsettings settings;
EnemySpaceship enemyspaceship = {1, 1, {{0, 2023, 1973, 1973, 1973, 1973, 2023, 0}, {2023, 2023, 2023, 2023, 2023, 2023, 2023, 2023}}, 500, 5, 5};
Enemy normalEnemy = {5, {{1973, 1973, 1973, 1973, 1973}, {1973, 333, 1973, 333, 1973}, {0, 1973, 0, 1973, 0}}, {{1973, 1973, 1973, 1973, 1973}, {1973, 333, 1973, 333, 1973}, {1973, 0, 0, 0, 1973}}, true, true, 100};
Bullet EnemyBullet = {50, 5, "╽", 333, false, true, false};
Bullet NormalBullet = {50, 5, "╿", 1963, false, true, false};
Ship horned = {0, 3, {{0, 213, 333, 333, 213, 0}, {213, 213, 213, 213, 213, 213}}, 58, 38};
Wall wall = {403, 1123, {{0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0}, {0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0}, {0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0}, {0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0}, {0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0}}, 14, 30, true};
void EraseFill(int row, int col, int cursorX, int cursorY)
{
    for (int i = 0; i < row; i++)
    {
        Gotoxy(cursorX, cursorY + i);
        for (int j = 0; j < col; j++)
        {
            cout << " " << FG_WHITE;
        }
    }
}
void EraseDown(int row, int col, int cursorX, int cursorY)
{
    Gotoxy(cursorX, cursorY + row - 1);
    for (int j = 0; j < col; j++)
    {
        cout << " " << FG_WHITE;
    }
}
void EraseUp(int col, int cursorX, int cursorY)
{
    Gotoxy(cursorX, cursorY);
    for (int j = 0; j < col; j++)
    {
        cout << " " << FG_WHITE;
    }
}
void EraseLeft(int row, int col, int cursorX, int cursorY)
{

    for (int j = 0; j < row; j++)
    {
        Gotoxy(cursorX, cursorY + j);
        cout << " " << FG_WHITE;
    }
}
void EraseRight(int row, int col, int cursorX, int cursorY)
{

    for (int j = 0; j < row; j++)
    {
        Gotoxy(cursorX + col - 1, cursorY + j);
        cout << " " << FG_WHITE;
    }
}
void DrawEntity(int *entity, int row, int col, int cursorX, int cursorY, bool isErase)
{
    int *currentEntity = entity;
    string lastColor = "";
    for (int i = 0; i < row; i++)
    {
        Gotoxy(cursorX, cursorY + i);
        for (int j = 0; j < col; j++)
        {
            int value = *currentEntity++;
            if (!isErase && value > 0)
            {
                string color = GenerateANSI(value);
                if (color != lastColor)
                {
                    lastColor = color;
                }
                cout << lastColor << "█";
            }
            else
            {
                cout << " ";
            }
        }
        cout << FG_WHITE;
    }
}

void CreateLevel(GameOptions &game)
{
    LevelOptions startLevel;
    switch (game.difficulty)
    {
    case EASY:
        break;
    case MEDIUM:
        break;
    case HARD:
        break;
    case CUSTOM:
        break;
    }
    game.maxHealth = 20;
    game.bulletsCount = 40;
    game.currentLevel = startLevel;
}
void SetRightestEnemy(EnemiesData &data)
{
    for (int i = 9; i >= 0; i--)
    {
        for (int j = 0; j < 3; j++)
        {
            if (data.enemies[j][i].isAlive)
            {
                data.rightestEnemy = &data.enemies[j][i];
                break;
            }
        }
    }
}

void SetLeftestEnemy(EnemiesData &data)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (data.enemies[j][i].isAlive)
            {
                data.leftestEnemy = &data.enemies[j][i];
                break;
            }
        }
    }
}
void SetBottomEnemies(EnemiesData &data,bool initialMode)
{
    for (int i = 0; i < 10; i++)
    {
        bool check = (initialMode || data.bottomEnemy[i] != nullptr) && (data.bottomEnemy[i] == nullptr || data.bottomEnemy[i]->isAlive) ;
        for (int j = 2; j >= -1 && check; j--)
        {
            if (j == -1)
                data.bottomEnemy[i] = nullptr;
            else
            {
                if (data.enemies[j][i].isAlive)
                {
                    data.bottomEnemy[i] = &data.enemies[j][i];
                    break;
                }
            }
        }
    }
}
void SetBottomestEnemy(EnemiesData &data)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 2; j >= 0; j--)
        {
            if (data.enemies[j][i].isAlive)
            {
                data.bottomestEnemy = &data.enemies[j][i];
                break;
            }
        }
    }
}
void initialEnemies(EnemiesData &data)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            data.enemies[i][j] = normalEnemy;
            data.enemies[i][j].positionX = 15 + j * 10;
            data.enemies[i][j].positionY = 8 + i * 6;
            data.aliveEnemyCount++;
            /*if (!(i == 2))
            {
                data.enemies[i][j].isAlive = false;
                data.aliveEnemyCount--;
            }*/
        }
    }
    SetRightestEnemy(data);
    SetLeftestEnemy(data);
    SetBottomestEnemy(data);
    SetBottomEnemies(data,true);
}
GameObjects InitializeGameObjects(GameOptions &game)
{
    GameObjects gameObjects;
    gameObjects.playerShip = horned;
    gameObjects.playerShip.health = game.maxHealth;
    gameObjects.playerBullet = NormalBullet;
    gameObjects.EnemyBullet = EnemyBullet;
    gameObjects.wall = wall;
    gameObjects.wall.isActive = false;
    gameObjects.EnemySpaceship = enemyspaceship;
    initialEnemies(gameObjects.enemiesData);
    // Set Spaceship
    // set Enemies
    // set wall
    return gameObjects;
}
void PrintScreen()
{
    string screen = R"(
    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║   Level:      Health:      Score:                                                                                    ║  
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝)";
    cout << screen;
}
void DrawShip(GameObjects &gameObjects)
{
    DrawEntity((int *)gameObjects.playerShip.entity, 2, 6, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY, false);
}
void DrawWall(GameObjects &gameObjects)
{
    DrawEntity((int *)gameObjects.wall.entity, 5, 100, gameObjects.wall.positionX, gameObjects.wall.positionY, false);
}
void DrawLevel(GameOptions &game)
{
    Gotoxy(14, 2);
    cout << FG_WHITE << game.currentLevel.id << "-" << game.currentLevel.subId;
}
void DrawHealth(GameObjects &gameObjects, GameOptions &game)
{
    Gotoxy(27, 2);
    string health = IntToString((gameObjects.playerShip.health * 100) / game.maxHealth) + "%";
    cout << FG_WHITE << "    ";
        Gotoxy(27, 2);
    cout << FG_WHITE << health;
}
void DrawScore(GameObjects &gameObjects)
{
    Gotoxy(40, 2);
    cout << FG_WHITE << setw(10) << left << gameObjects.Score;
}
void Draw(GameObjects &gameObjects, GameOptions &game)
{
    DrawLevel(game);
    DrawHealth(gameObjects, game);
    DrawScore(gameObjects);
    DrawShip(gameObjects);
    DrawWall(gameObjects);
    DrawEnemies(gameObjects.enemiesData);
}
void MoveShip(GameObjects &gameObjects, bool left)
{
    int i;
    if (left)
    {
        EraseRight(2, 6, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY);
        gameObjects.playerShip.positionX--;
    }
    else if (!left)
    {
        EraseLeft(2, 6, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY);
        gameObjects.playerShip.positionX++;
    }
    DrawEntity((int *)gameObjects.playerShip.entity, 2, 6, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY, false);
}
void FirePlayerBullet(GameObjects &gameObjects)
{
    if (!gameObjects.playerBullet.isActive)
    {
        gameObjects.playerBullet = NormalBullet;
        gameObjects.playerBullet.positionX = gameObjects.playerShip.positionX + 2;
        gameObjects.playerBullet.positionY = gameObjects.playerShip.positionY - 1;
        gameObjects.playerBullet.isActive = true;
    }
}
void ShowPauseMenu(){
bool MusicIsPlay = false;
    Form form = {"Main Menu", 5, 2};
    Display display = {0, 4, 0, 0, {0, 0}};
    InitialDisplay(display);
    RenderMinimalBackground(display);
    Generalsettings generalsettings;
    LoadSettings(generalsettings);
    form.isSoundEnabled = generalsettings.Sound;
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
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type), display.secondaryColor);

        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            Button *button = (Button *)(SelectedElement.ptr);
            switch ((*button).id)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
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
void InputHandle(GameObjects &gameObjects)
{
    if (_kbhit())
    {
        char order;
        order = getch();
        order = toupper(order);
        if (order == settings.keybindings.Left_Player1 && gameObjects.playerShip.positionX > 6)
        {
            MoveShip(gameObjects, true);
        }
        else if (order == settings.keybindings.Right_Player1 && gameObjects.playerShip.positionX < widthScreen - 4)
        {
            MoveShip(gameObjects, false);
        }
        else if (order == settings.keybindings.Shoot_Player1)
        {
            FirePlayerBullet(gameObjects);
        }
        else if (order == 27){
            ShowPauseMenu();
            EraseFill(25,112,8,6);
        }
    }
}

void MovePlayerBullet(GameObjects &gameObjects)
{

    Gotoxy(gameObjects.playerBullet.positionX, gameObjects.playerBullet.positionY);
    cout << " " << FG_WHITE;
    gameObjects.playerBullet.positionY--;
    if (gameObjects.playerBullet.positionY > 4)
    {
        Gotoxy(gameObjects.playerBullet.positionX, gameObjects.playerBullet.positionY);
        string color = GenerateANSI(gameObjects.playerBullet.colorCode);
        cout << color << gameObjects.playerBullet.shape << FG_WHITE;
    }
    else
    {
        gameObjects.playerBullet.isActive = false;
    }
}
void CollisionWallEntity(Wall &wall, int row, int col)
{
    Gotoxy(wall.positionX + col, wall.positionY + row);
    if (wall.entity[row][col] != wall.PrimaryColor)
    {
        wall.entity[row][col] = 0;
        cout << " " << FG_WHITE;
    }
    else
    {
        wall.entity[row][col] = wall.SecondaryColor;
        cout << GenerateANSI(wall.entity[row][col]) << "█" << FG_WHITE;
    }
}
void CheckShipCollision(GameObjects &gameObjects, GameOptions &game)
{
    int j = gameObjects.EnemyBullet.positionX - gameObjects.playerShip.positionX;
    int i = gameObjects.EnemyBullet.positionY - gameObjects.playerShip.positionY;
    if ((i >= 0 && j >= 0 && j < 6 && i < 2) && gameObjects.playerShip.entity[i][j])
    {
        gameObjects.EnemyBullet.isActive = false;
        gameObjects.playerShip.health -= gameObjects.EnemyBullet.damage;
        DrawHealth(gameObjects, game);
        DrawEntity((int *)gameObjects.playerShip.entity, 2, 6, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY, false);
    }
}
void CheckWallCollision(GameObjects &gameObjects, Bullet &bullet)
{
    int j = bullet.positionX - gameObjects.wall.positionX;
    int i = bullet.positionY - gameObjects.wall.positionY;

    if (gameObjects.wall.isActive && (i >= 0 && j >= 0 && j < 100 && i < 5) && gameObjects.wall.entity[i][j])
    {
        bullet.isActive = false;
        gameObjects.wall.entity[i][j] = 0;
        CollisionWallEntity(gameObjects.wall, i, j);
    }
}

void MoveEnemies(GameObjects &gameObjects)
{
    bool goDown = false;
    EnemiesData &data = gameObjects.enemiesData;
    if (((data.dir == 1) && (*data.leftestEnemy).positionX >= 110) || ((data.dir == -1) && (*data.rightestEnemy).positionX <= 11))
    {
        goDown = true;
        data.dir = -data.dir;
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (!goDown)
            {
                data.enemies[i][j].positionX += data.dir;
            }
            else
            {
                data.enemies[i][j].positionY += 1;
                if (gameObjects.wall.isActive && data.enemies[i][j].positionY >= gameObjects.wall.positionY)
                {
                    gameObjects.wall.isActive = false;
                    EraseFill(5, 100, gameObjects.wall.positionX, gameObjects.wall.positionY);
                }
            }
            data.enemies[i][j].positionY += data.effectdir;
            data.enemies[i][j].IsOne = !data.enemies[i][j].IsOne;
        }
    }
    data.effectdir = -data.effectdir;
}

void EraseEnemies(EnemiesData &data)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (data.enemies[i][j].isAlive)
            {
                if ((data.effectdir > 0 || ((data.dir == 1) && (*data.leftestEnemy).positionX >= 110) || ((data.dir == -1) && (*data.rightestEnemy).positionX <= 5)))
                {
                    EraseUp(5, data.enemies[i][j].positionX, data.enemies[i][j].positionY);
                }
                else
                {
                    EraseDown(3, 5, data.enemies[i][j].positionX, data.enemies[i][j].positionY);
                }
                if (data.dir > 0)
                {
                    EraseLeft(3, 5, data.enemies[i][j].positionX, data.enemies[i][j].positionY);
                }
                else
                {
                    EraseRight(3, 5, data.enemies[i][j].positionX, data.enemies[i][j].positionY);
                }
            }
        }
    }
}

void DrawEnemies(EnemiesData &data)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (data.enemies[i][j].isAlive)
            {
                int *entity = nullptr;
                if (data.enemies[i][j].IsOne)
                {
                    entity = (int *)data.enemies[i][j].entity1;
                }
                else
                {
                    entity = (int *)data.enemies[i][j].entity2;
                }
                DrawEntity(entity, 3, 5, data.enemies[i][j].positionX, data.enemies[i][j].positionY, false);
            }
        }
    }
}
void CheckEnemyCollision(GameObjects &gameObjects)
{
    for (int i = 2; i >= 0; i--)
    {
        for (int j = 0; j < 10; j++)
        {
            Enemy &enemy = gameObjects.enemiesData.enemies[i][j];
            if (enemy.isAlive &&
                gameObjects.playerBullet.positionX >= enemy.positionX &&
                gameObjects.playerBullet.positionX < enemy.positionX + 5 &&
                gameObjects.playerBullet.positionY >= enemy.positionY &&
                gameObjects.playerBullet.positionY < enemy.positionY + 3)
            {
                enemy.health -= gameObjects.playerBullet.damage;
                gameObjects.playerBullet.isActive = false;
                Gotoxy(gameObjects.playerBullet.positionX, gameObjects.playerBullet.positionY);
                cout << " ";
                if (enemy.health <= 0)
                {
                    enemy.isAlive = false;
                    gameObjects.enemiesData.aliveEnemyCount--;

                    gameObjects.Score += enemy.Score;
                    DrawScore(gameObjects);
                    EraseFill(3, 5, enemy.positionX, enemy.positionY);
                }
                if (!(*gameObjects.enemiesData.rightestEnemy).isAlive)
                {
                    SetRightestEnemy(gameObjects.enemiesData);
                }
                if (!(*gameObjects.enemiesData.leftestEnemy).isAlive)
                {
                    SetLeftestEnemy(gameObjects.enemiesData);
                }
                if (!(*gameObjects.enemiesData.bottomestEnemy).isAlive)
                {
                    SetBottomestEnemy(gameObjects.enemiesData);
                }
                SetBottomEnemies(gameObjects.enemiesData,false);

                return;
            }
        }
    }
}
bool WinCheck(GameObjects &gameObjects)
{
    return gameObjects.enemiesData.aliveEnemyCount == 0;
}

void FireEnemyBullet(GameObjects &gameObjects)
{
    EnemiesData &data = gameObjects.enemiesData;
    if (!gameObjects.EnemyBullet.isActive)
    {
        srand(static_cast<unsigned int>(time(NULL)));
        int i = rand() % 10;
        gameObjects.EnemyBullet = EnemyBullet;
        while (data.bottomEnemy[i] == nullptr)
        {
            i = rand() % 10;
        }
        gameObjects.EnemyBullet.positionX = (*data.bottomEnemy[i]).positionX + 2;
        gameObjects.EnemyBullet.positionY = (*data.bottomEnemy[i]).positionY + 3;
        gameObjects.EnemyBullet.isActive = true;
    }
}
void MoveEnemyBullet(GameObjects &gameObjects)
{
    Gotoxy(gameObjects.EnemyBullet.positionX, gameObjects.EnemyBullet.positionY);
    cout << " ";
    gameObjects.EnemyBullet.positionY++;
    if (gameObjects.EnemyBullet.positionY < lengthScreen - 1)
    {
        Gotoxy(gameObjects.EnemyBullet.positionX, gameObjects.EnemyBullet.positionY);
        string color = GenerateANSI(gameObjects.EnemyBullet.colorCode);
        cout << color << gameObjects.EnemyBullet.shape << FG_WHITE;
    }
    else
    {
        gameObjects.EnemyBullet.isActive = false;
    }
}
bool CheckEnemyCatchShip(GameObjects &gameObjects)
{
    return (*gameObjects.enemiesData.bottomestEnemy).positionY + 3 >= gameObjects.playerShip.positionY;
}
bool CheckShipAlive(GameObjects &gameObjects)
{
    return gameObjects.playerShip.health <= 0;
}
void CheckEnemySpaceshipCollision(GameObjects &gameObjects)
{
    int j = gameObjects.playerBullet.positionX - gameObjects.EnemySpaceship.positionX;
    int i = gameObjects.playerBullet.positionY - gameObjects.EnemySpaceship.positionY;
    if ((i >= 0 && j >= 0 && j < 8 && i < 2) && gameObjects.EnemySpaceship.entity[i][j])
    {
        gameObjects.EnemySpaceship.isAlive = false;
        gameObjects.Score += gameObjects.EnemySpaceship.Score;
        DrawScore(gameObjects);
                    EraseFill(2, 8, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY);
    }
}
void MoveEnemySpaceship(GameObjects &gameObjects)
{
    if (gameObjects.EnemySpaceship.direction)
        if (gameObjects.EnemySpaceship.positionX - 7 < widthScreen - 4)
        {
            EraseLeft(2, 6, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY);
            gameObjects.EnemySpaceship.positionX++;
            DrawEntity((int *)gameObjects.EnemySpaceship.entity, 2, 8, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY, false);
        }
        else
        {
            gameObjects.EnemySpaceship.isAlive = false;
            gameObjects.EnemySpaceship.direction = false;
            EraseFill(2, 8, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY);
        }
    else
    {
        if (gameObjects.EnemySpaceship.positionX > 4)
        {
            EraseRight(2, 6, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY);
            gameObjects.EnemySpaceship.positionX--;
            DrawEntity((int *)gameObjects.EnemySpaceship.entity, 2, 8, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY, false);
        }
        else
        {

            gameObjects.EnemySpaceship.isAlive = false;
            gameObjects.EnemySpaceship.direction = true;
            EraseFill(2, 8, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY);
        }
    }
}
bool PlayLevel(GameOptions &game)
{
    GameObjects gameObjects = InitializeGameObjects(game);
    int totalTime = 1;
    Draw(gameObjects, game);
    bool isRunning = true;
    bool &isWin = game.isWin;
    bool isLose = false;
    while (isRunning)
    {

        InputHandle(gameObjects);

        if (clock() % 100 == 0)
        {
            FireEnemyBullet(gameObjects);
        }

        if (clock() % gameObjects.enemiesData.speed == 0)
        {
            EraseEnemies(gameObjects.enemiesData);
            MoveEnemies(gameObjects);
            DrawEnemies(gameObjects.enemiesData);
            isLose = CheckEnemyCatchShip(gameObjects);
        }
        if (clock() % 20000 == 0)
        {
            gameObjects.EnemySpaceship = enemyspaceship;
        }
        if (clock() % 100 == 0 && gameObjects.EnemySpaceship.isAlive)
        {
            MoveEnemySpaceship(gameObjects);
        }
        if (gameObjects.EnemyBullet.isActive && clock() % gameObjects.EnemyBullet.speed == 0)
        {
            MoveEnemyBullet(gameObjects);
            CheckWallCollision(gameObjects, gameObjects.EnemyBullet);
            CheckShipCollision(gameObjects, game);
            isLose = CheckShipAlive(gameObjects);
        }
        if (gameObjects.playerBullet.isActive && clock() % gameObjects.playerBullet.speed == 1)
        {
            MovePlayerBullet(gameObjects);
            CheckWallCollision(gameObjects, gameObjects.playerBullet);
            CheckEnemyCollision(gameObjects);
            CheckEnemySpaceshipCollision(gameObjects);
            isWin = WinCheck(gameObjects);
        }

        if (isWin)
            isRunning = false;
        if (isLose)
            isRunning = false;
    }

    return gameObjects.Score;
}
void NextLevel(GameOptions &game)
{
    LevelOptions startLevel;
    switch (game.difficulty)
    {
    case EASY:
        break;
    case MEDIUM:
        break;
    case HARD:
        break;
    case CUSTOM:
        break;
    }
    game.currentLevel = startLevel;
}
void ShowGameOver(int fgcolor, int bgcolor)
{
    int x = 35;
    int y = 18;
    string fg_color = GenerateANSI(fgcolor);
    string bg_color = GenerateANSI(bgcolor);
    Gotoxy(x, y);
    cout << fg_color << bg_color << "   _____                         ____                 _ ";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"(  / ____|                       / __ \               | |)";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __| |";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__| |)";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |  |_|)";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"(  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|  (_))";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"(                                                        )";
}
void LoseAnimation()
{
    for (int i = 0; i < 12; i++)
    {
        ShowGameOver(03, 1964);
        Sleep(150);
        ShowGameOver(04, 1963);
        Sleep(150);
    }
    Sleep(1000);
}
void RunGame(GameOptions &game)
{
    HideCursor();
    LoadSettings(settings);
    PrintScreen();
    CreateLevel(game);
    int Score = 0;
    while (1)
    {
        Score += PlayLevel(game);
        if (game.isWin)
            NextLevel(game);
        else
        {
            LoseAnimation();
            break;
        }
    }
}
int main()
{
    system("cls");
    HideCursor();
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    GameOptions game;
    RunGame(game);
    return 0;
}