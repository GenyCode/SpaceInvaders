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

struct bullets
{
	unsigned short int speed;
	char shape;
	bool isLaser;
	bool direction;
	bool isSpreadable;
	int positionX;
	int positionY;
	bool isActive;
};

struct ship
{
	unsigned short int bulletSpeed;
	unsigned short int health;
	string shape[2];
	char color;
	unsigned short int leftSide;
};
struct Enemy
{
	unsigned short int speed;
	bool entity[2][5];
	string shape[2];
	bool isAlive;
	int positionX;
	int positionY;
};
struct EnemiesData
{
	Enemy enemies[4][10];
	Enemy *leftestEnemy = nullptr;
	Enemy *rightestEnemy = nullptr;
	int dir = 1;
};
struct Shield{
	bool entity[5][6];
	int PositionX;
	int PositionY;
};

void shipControl();
void moveShip(char);
void printScreen();
void firePlayerBullet();
void movePlayerBullet();
void hideCursor();
void gotoXY(int, int);
void unicode(int, int);
void color(char);
void setColor(const string &);

char back[lengthScreen][widthScreen];
char front[lengthScreen][widthScreen];

bullets Normal = {0, 'n', false, true, false};
bullets Reverse = {0, 'r', false, false, false};
bullets Laser = {0, 'l', true, true, false};
bullets Bomb = {0, 'b', false, true, false};
bullets Spreadable = {0, 's', false, true, true};
bullets MainBullet = Normal;

ship terminator = {3, 1, {{"▲ ▲ ▲"}, {"█▄█▄█"}}, 'r', 58};
ship feisty = {2, 2, {{"≶ ⭻ ≷"}, {"█▒█▒█"}}, 'b', 58};
ship horned = {1, 3, {{"█🙪🙪🙪█"}, {"█▅▅▅█"}}, 'm', 58};
ship selected;

Enemy normalEnemy = {0, {{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}}, {{"█████"}, {"█▄█▄█"}}, true};
Shield normalShield = {{{1,1,1,1,1,1},{1,1,1,1,1,1},{1,1,0,0,1,1},{1,1,0,0,1,1},{1,1,0,0,1,1}}};
Shield shields[4];
void SetRightestEnemy(EnemiesData &data)
{
	for (int i = 9; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
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
		for (int j = 0; j < 4; j++)
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
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			data.enemies[i][j] = normalEnemy;
			data.enemies[i][j].positionX = 5 + j * 10;
			data.enemies[i][j].positionY = 5 + i * 4;
		}
	}
	SetRightestEnemy(data);
	SetLeftestEnemy(data);
}
void initialShields(Shield Shields[4])
{
	for (int i = 0; i < 4; i++)
	{
		Shields[i] = normalShield;
		Shields[i].PositionX = 5 + i * 12;
		Shields[i].PositionY = lengthScreen - 10;
	}
}
void printShields(Shield Shields[4]){
	for (int i = 0; i < 4; i++)
	{
		for(int j = 0;j<5;j++){
			for(int k = 0;k<6;k++){
				if(Shields[i].entity){
								gotoXY(Shields[i].PositionY+k,Shields[i].PositionX+j);
					cout <<"█";
				}
			}
		}
	}
}
void moveEnemies(EnemiesData &data)
{
	bool goDown = false;

	if (((data.dir == 1) && (*data.leftestEnemy).positionX >= 110) || ((data.dir == -1) && (*data.rightestEnemy).positionX <= 5))
	{
		goDown = true;
		data.dir = -data.dir;
	}

	for (int i = 0; i < 4; i++)
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
		}
	}
}
void eraseEnemies(EnemiesData &data)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for(int k = 0;k<2;k++){
			gotoXY(data.enemies[i][j].positionY, data.enemies[i][j].positionX);
			cout << "     ";
			}
		}
	}
}
void printEnemies(EnemiesData &data)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for(int k = 0;k<2;k++){
			gotoXY(data.enemies[i][j].positionY, data.enemies[i][j].positionX);
			cout << data.enemies[i][j].shape[k];
			}
		}
	}
}
string shipEraser[3] = {{"     "}, {"     "}, {"     "}};

int main()
{
	system("cls");
	hideCursor();
	EnemiesData data;
	initialEnemies(data);

	SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	int i, j;
	unsigned short int shipType = 3;

	if (shipType == 1)
		selected = terminator;
	else if (shipType == 2)
		selected = feisty;
	else
		selected = horned;

	for (i = 0; i < lengthScreen; i++)
		for (j = 0; j < widthScreen; j++)
			if (i == 0 || i == lengthScreen - 1)
			{
				back[i][j] = 'w';
				front[i][j] = '_';
			}
			else if (j == 0 || j == widthScreen - 1)
			{
				back[i][j] = 'w';
				front[i][j] = '|';
			}
			else
			{
				back[i][j] = ' ';
				front[i][j] = ' ';
			}
	front[0][0] = '`';
	front[0][widthScreen - 1] = '^';
	front[lengthScreen - 1][0] = '~';
	front[lengthScreen - 1][widthScreen - 1] = ',';

	printScreen();

	for (i = 0; i < 2; i++)
	{
		gotoXY(lengthScreen - 2 - i, selected.leftSide);
		color(selected.color);
		cout << selected.shape[1 - i];
	}

	// for (i = lengthScreen - 3; i < lengthScreen - 1; i++)
	// 	for (j = widthScreen / 2 - 2; j < widthScreen / 2 + 3; j++)
	// 		back[i][j] = '1';
	/*
	gotoXY ( 0 , 0 ) ;
	for ( i = 0 ; i < lengthScreen ; i++ )
	{
		for ( j = 0 ; j < widthScreen ; j++ )
			cout << back [ i ] [ j ] ;
		cout << endl ;
	}
	*/
	initialShields(shields);
	printShields(shields);
	MainBullet.isActive = false;
	while (1)
	{
		shipControl();
		movePlayerBullet();
		if (clock() % 200 == 0)
		{
			eraseEnemies(data);
			moveEnemies(data);
			printEnemies(data);
		}
	}

	getch();
	system("cls");
	return 0;
}

void shipControl()
{
	if (_kbhit())
	{
		char order;
		order = getch();
		switch (order)
		{
		case 'a':
		case 'A':
			if (!(selected.leftSide + 5 < widthScreen - 1))
			{
				selected.leftSide--;
				moveShip(order);
				for (int i = 0; i < 3; i++)
				{
					gotoXY(lengthScreen - 2 - i, 118);
					cout << " ";
				}
			}
			else
				moveShip(order);
			break;
		case 'd':
		case 'D':
			if (!(selected.leftSide - 1 > 0))
			{
				selected.leftSide++;
				moveShip(order);
				for (int i = 0; i < 3; i++)
				{
					gotoXY(lengthScreen - 2 - i, 1);
					cout << " ";
				}
			}
			else
				moveShip(order);
			break;
			//	case 'w' : case 'W' :

			//	case 's' : case 'S' :

		case ' ':
			firePlayerBullet();
			break;
		}
	}
}

void moveShip(char moveOrder)
{
	int i;
	if (selected.leftSide + 5 < widthScreen - 1 && selected.leftSide - 1 > 0)
	{
		for (i = 0; i < 2; i++)
		{
			gotoXY(lengthScreen - 2 - i, selected.leftSide);
			cout << shipEraser[1 - i];
		}
		if (moveOrder == 'a' || moveOrder == 'A')
		{
			selected.leftSide--;
			for (i = 0; i < 2; i++)
			{
				gotoXY(lengthScreen - 2 - i, selected.leftSide);
				color(selected.color);
				cout << selected.shape[1 - i];
			}
		}
		else
		{
			selected.leftSide++;
			for (i = 0; i < 2; i++)
			{
				gotoXY(lengthScreen - 2 - i, selected.leftSide);
				color(selected.color);
				cout << selected.shape[1 - i];
			}
		}
	}
}
void firePlayerBullet()
{
	if (!MainBullet.isActive)
	{
		MainBullet = Normal;
		MainBullet.positionX = selected.leftSide + 2;
		MainBullet.positionY = lengthScreen - 4;
		MainBullet.isActive = true;
	}
}
void movePlayerBullet()
{
	if (clock() % 50 == 0)
	{
		if (MainBullet.isActive)
		{
			gotoXY(MainBullet.positionY, MainBullet.positionX);
			cout << " ";
			MainBullet.positionY--;
			if (MainBullet.positionY > 0)
			{
				gotoXY(MainBullet.positionY, MainBullet.positionX);
				cout << MainBullet.shape;
			}
			else
			{
				MainBullet.isActive = false;
			}
		}
	}
}
void setColor(const string &colorCode)
{
	cout << "\033[" << colorCode << "m";
}

void color(char c) // This function uses the setColor function based on the first character of each color
{
	switch (c)
	{
	case 'r':
		setColor("31");
		break;
	case 'g':
		setColor("32");
		break;
	case 'o':
		setColor("33");
		break;
	case 'b':
		setColor("34");
		break;
	case 'm':
		setColor("35");
		break;
	case 'c':
		setColor("36");
		break;
	case 'w':
		setColor("97");
		break;
	case 'p':
		setColor("91");
		break;
	case 'l':
		setColor("92");
		break;
	case 'y':
		setColor("93");
		break;
	case 'a':
		setColor("94");
		break;
	case 'v':
		setColor("95");
		break;
	case 't':
		setColor("96");
		break;
	case 's':
		setColor("90");
	}
}

void printScreen() // this function print & refresh screen based on front array
{
	int i, j;
	for (i = 0; i < lengthScreen; i++)
		for (j = 0; j < widthScreen; j++)
			unicode(i, j);
}

void unicode(int x, int y) // This function prints the Unicode state of each element of the array onto the screen
{
	gotoXY(x, y);
	switch (front[x][y])
	{
	case '_':
		cout << "═";
		break;
	case '|':
		cout << "║";
		break;
	case '`':
		cout << "╔";
		break;
	case '~':
		cout << "╚";
		break;
	case ',':
		cout << "╝";
		break;
	case '^':
		cout << "╗";
		break;
	case ' ':
		cout << " ";
		break;
	case 'n':
		cout << "╽";
		break;
	case 'r':
		cout << "╿";
		break;
	case 'l':
		cout << "┃";
		break;
	case 'b':
		cout << "💣";
		break;
	case 's':
		cout << "🢁";
		break;
	}
}

void gotoXY(int x, int y) // This function moves the cursor to the location specified in the input arguments
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorCoord;
	cursorCoord.X = y;
	cursorCoord.Y = x;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

void hideCursor()
{
	cout << "\033[?25l";
}
