#pragma ones
#include <iostream>
#include <cmath>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const unsigned short int lengthScreen = 41;
const unsigned short int widthScreen = 120;

enum GameDifficulty{
    EASY,
    MEDIUM,
    HARD,
    CUSTOM
};


struct LevelOptions{
    int id;
    int enemyShotsPerSec;
    int wallIndex;
};

struct GameOptions{
    string playerName;
    GameDifficulty difficulty;
    int SpaceshipType;
    int time;
    int maxHealth;
    int bulletsCount;
    LevelOptions currentLevel;
};

struct Bullet
{
	unsigned short int speed;
	unsigned short int damage;
	string shape;
	int colorCode;
	bool direction;
	int positionX;
	int positionY;
	bool isActive;
};

struct Ship
{
	unsigned short int health;
	unsigned short int bulletsCount;
	int entity[2][6];
	int positionX;
	int positionY;
};

struct Enemy
{
	unsigned short int health;
	int entity1[3][5];
	int entity2[3][5];
	bool IsOne = 0;
	bool isAlive;
	int positionX;
	int positionY;
};

struct EnemiesData
{
	Enemy enemies[3][10];
	Enemy *leftestEnemy = nullptr;
	Enemy *rightestEnemy = nullptr;
	int dir = 1;
	int effectdir = 1;
	int speed = 500;
};

struct Wall
{
	int PrimaryColor;
	int SecondaryColor;
	int entity[5][100];
	int positionX;
	int positionY;
};

struct GameObjects{
    Ship playerShip;
    Bullet playerBullet;
    EnemiesData enemiesData;
    Wall wall;
};