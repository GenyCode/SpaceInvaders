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
#include "utilities.cpp"
#include "game.h"
#include "color.h"
#include "settings.cpp"

void DrawEnemies(EnemiesData &data);
Generalsettings settings;
Enemy normalEnemy = {0, {{1973, 1973, 1973, 1973, 1973}, {1973, 333, 1973, 333, 1973}, {0, 1973, 0, 1973, 0}}, {{1973, 1973, 1973, 1973, 1973}, {1973, 333, 1973, 333, 1973}, {1973, 0,0 ,0 , 1973}},true, true};
Bullet Normal = {50, 5, "╿", 1963, false, true, false};
Ship horned = {1, 3, {{0, 213, 333, 333, 213, 0}, {213, 213, 213, 213, 213, 213}}, 58, 38};
Wall wall = {403, 1123, {{0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0}, {0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0}, {0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0}, {0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0}, {0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0, 0, 403, 403, 403, 403, 403, 403, 403, 403, 0}}, 9, 28};
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
void initialEnemies(EnemiesData &data)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            data.enemies[i][j] = normalEnemy;
            data.enemies[i][j].positionX = 5 + j * 10;
            data.enemies[i][j].positionY = 5 + i * 6;
        }
    }
    SetRightestEnemy(data);
    SetLeftestEnemy(data);
}
GameObjects InitializeGameObjects(GameOptions &game)
{
    GameObjects gameObjects;
    gameObjects.playerShip = horned;
    gameObjects.playerBullet = Normal;
    gameObjects.wall = wall;
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
void Draw(GameObjects &gameObjects)
{
    PrintScreen();
    DrawShip(gameObjects);
    DrawWall(gameObjects);
    DrawEnemies(gameObjects.enemiesData);
}
void MoveShip(GameObjects &gameObjects, bool left)
{
    int i;
    if (gameObjects.playerShip.positionX + 5 < widthScreen - 1 && gameObjects.playerShip.positionX - 1 > 0)
    {
        if (left)
        {
            EraseRight(2, 6, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY);

            gameObjects.playerShip.positionX--;
        }
        else
        {
            EraseLeft(2, 6, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY);

            gameObjects.playerShip.positionX++;
        }
        DrawEntity((int *)gameObjects.playerShip.entity, 2, 6, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY, false);
    }
}
void FirePlayerBullet(GameObjects &gameObjects)
{
    if (!gameObjects.playerBullet.isActive)
    {
        gameObjects.playerBullet = Normal;
        gameObjects.playerBullet.positionX = gameObjects.playerShip.positionX + 2;
        gameObjects.playerBullet.positionY = gameObjects.playerShip.positionY - 1;
        gameObjects.playerBullet.isActive = true;
    }
}
void PlayerMovement(GameObjects &gameObjects)
{
    if (_kbhit())
    {
        char order;
        order = getch();
        order = toupper(order);
        if (order == settings.keybindings.Left_Player1)
        {
            if (!(gameObjects.playerShip.positionX + 5 < widthScreen - 1))
            {
                gameObjects.playerShip.positionX--;
                MoveShip(gameObjects, true);
                for (int i = 0; i < 3; i++)
                {
                    Gotoxy(118, lengthScreen - 2 - i);
                    cout << " ";
                }
            }
            else
                MoveShip(gameObjects, true);
        }
        else if (order == settings.keybindings.Right_Player1)
        {
            if (!(gameObjects.playerShip.positionX - 1 > 0))
            {
                gameObjects.playerShip.positionX++;
                MoveShip(gameObjects, false);
                for (int i = 0; i < 3; i++)
                {
                    Gotoxy(1, lengthScreen - 2 - i);
                    cout << " ";
                }
            }
            else
                MoveShip(gameObjects, false);
        }
        else if (order == settings.keybindings.Shoot_Player1)
        {
            FirePlayerBullet(gameObjects);
        }
    }
}

void MovePlayerBullet(GameObjects &gameObjects)
{
    if (gameObjects.playerBullet.isActive)
    {
        Gotoxy(gameObjects.playerBullet.positionX, gameObjects.playerBullet.positionY);
        cout << " " << FG_WHITE;
        gameObjects.playerBullet.positionY--;
        if (gameObjects.playerBullet.positionY > 0)
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
void CheckWallCollision(GameObjects &gameObjects)
{
    int j = gameObjects.playerBullet.positionX - gameObjects.wall.positionX;
    int i = gameObjects.playerBullet.positionY - gameObjects.wall.positionY;

    if ((i > 0 && j > 0 && j < 100 && i < 5) && gameObjects.wall.entity[i][j])
    {
        gameObjects.playerBullet.isActive = false;
        gameObjects.wall.entity[i][j] = 0;
        Gotoxy(gameObjects.wall.positionX + j, gameObjects.wall.positionY + i);
        cout << " " << FG_WHITE;
        if (j + 1 < 100)
        {
            CollisionWallEntity(gameObjects.wall, i, j + 1);
        }
        if (j - 1 > 0)
        {
            CollisionWallEntity(gameObjects.wall, i, j - 1);
        }
        if (i - 1 > 0)
        {
            CollisionWallEntity(gameObjects.wall, i - 1, j);
        }
    }
}

void MoveEnemies(EnemiesData &data)
{
    bool goDown = false;

    if (((data.dir == 1) && (*data.leftestEnemy).positionX >= 110) || ((data.dir == -1) && (*data.rightestEnemy).positionX <= 5))
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
            if (data.effectdir > 0 || ((data.dir == 1) && (*data.leftestEnemy).positionX >= 110) || ((data.dir == -1) && (*data.rightestEnemy).positionX <= 5))
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

void PlayLevel(GameOptions &game)
{
    GameObjects gameObjects = InitializeGameObjects(game);
    int totalTime = 1;
    Draw(gameObjects);
    bool gameOver = false;
    while (!gameOver)
    {

        PlayerMovement(gameObjects);
        if (clock() % gameObjects.playerBullet.speed == 0)
        {
            MovePlayerBullet(gameObjects);
            CheckWallCollision(gameObjects);
            // CheckEnemyCollision(data);
        }

        // if (clock() % 2000 == 0)
        //{
        //	enemyFireBullet ( data ) ;
        //}

        if (clock() % gameObjects.enemiesData.speed == 0)
        {
            EraseEnemies(gameObjects.enemiesData);
            MoveEnemies(gameObjects.enemiesData);
            DrawEnemies(gameObjects.enemiesData);
        }
    }
}
void RunGame(GameOptions &game)
{
    LoadSettings(settings);
    CreateLevel(game);
    PlayLevel(game);
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