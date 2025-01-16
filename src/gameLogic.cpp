#include <iostream>
#include <cmath>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std ;

const unsigned short int lengthScreen = 41 ;
const unsigned short int widthScreen = 120 ;

struct bullets
{
	unsigned short int speed ;
	char shape ;
	bool isLaser ;
	bool direction ;
	bool isSpreadable ;
} ;

struct ship
{
	unsigned short int bulletSpeed ;
	unsigned short int health ;
	string shape [ 2 ] ;
	char color ;
	unsigned short int leftSide ;
} ;

void shipControl (  ) ;
void moveShip ( char  ) ;
void printScreen (  ) ;

void hideCursor (  ) ;
void gotoXY ( int  , int  ) ;
void unicode ( int  , int  ) ;
void color ( char  ) ;
void setColor ( const string&  ) ;

char back [ lengthScreen ] [ widthScreen ] ;
char front [ lengthScreen ] [ widthScreen ] ;

bullets N = { 0 , 'n' , false , true , false } ;
bullets R = { 0 , 'r' , false , false , false } ;
bullets L = { 0 , 'l' , true , true , false } ;
bullets B = { 0 , 'b' , false , true , false } ;
bullets S = { 0 , 's' , false , true , true } ;

ship terminator = { 3 , 1 , { { "▲ ▲ ▲" } , { "█▄█▄█" } } , 'r' , 58 } ;
ship feisty     = { 2 , 2 , { { "≶ ⭻ ≷" } , { "█▒█▒█" } } , 'b' , 58 } ;
ship horned     = { 1 , 3 , { { "█🙪🙪🙪█" } , { "█▅▅▅█" } } , 'm' , 58 } ;
ship selected ;

string shipEraser [ 3 ] = { { "     " } , { "     " } , { "     " } } ;

int main (  )
{
	int i , j ;
	unsigned short int shipType = 3 ;
	
	if ( shipType == 1 )
		selected = terminator ;
	else if ( shipType == 2 )
		selected = feisty ;
	else
		selected = horned ;
	
	for ( i = 0 ; i < lengthScreen ; i++ )
		for ( j = 0 ; j < widthScreen ; j++ )
			if ( i == 0 || i == lengthScreen - 1 )
			{
				back [ i ] [ j ] = 'w' ;
				front [ i ] [ j ] = '_' ;
			}
			else if ( j == 0 || j == widthScreen - 1 )
			{
				back [ i ] [ j ] = 'w' ;
				front [ i ] [ j ] = '|' ;
			}
			else
			{
				back [ i ] [ j ] = ' ' ;		
				front [ i ] [ j ] = ' ' ;
			}
	front [ 0 ] [ 0 ] = '`' ;
	front [ 0 ] [ widthScreen - 1 ] = '^' ;
	front [ lengthScreen - 1 ] [ 0 ] = '~' ;
	front [ lengthScreen - 1 ] [ widthScreen - 1 ] = ',' ;
	
	printScreen (  ) ;
	
	for ( i = 0 ; i < 2 ; i++ )
	{
		gotoXY ( lengthScreen - 2 - i , selected . leftSide ) ;
		color ( selected . color ) ;
		cout << selected . shape [ 1 - i ] ;
	}
	
	for ( i = lengthScreen - 3 ; i < lengthScreen - 1 ; i++ )
		for ( j = widthScreen / 2 - 2 ; j < widthScreen / 2 + 3 ; j++ )
			back [ i ] [ j ] = '1' ; 
	/*
	gotoXY ( 0 , 0 ) ;
	for ( i = 0 ; i < lengthScreen ; i++ )
	{
		for ( j = 0 ; j < widthScreen ; j++ )
			cout << back [ i ] [ j ] ; 
		cout << endl ;
	}
	*/
	
	while ( 1 )
	{
		shipControl (  ) ;
		
	}
	
	getch (  ) ;
	system ( "cls" ) ;
    return 0 ;
}

void shipControl (  )
{
	if ( _kbhit (  ) )
	{
		char order ;
		order = getch (  ) ;
		switch ( order )
		{
			case 'a' : case 'A' :
				if ( ! ( selected . leftSide + 5 < widthScreen - 1 ) )
				{
					selected . leftSide-- ;
					moveShip ( order ) ;
					for ( int i = 0 ; i < 3 ; i++ )
					{
						gotoXY ( lengthScreen - 2 - i , 118 ) ;
						cout << " " ;
					}
				}
				else
					moveShip ( order ) ;
				break ;
			case 'd' : case 'D' :
				if ( ! ( selected . leftSide - 1 > 0 ) )
				{
					selected . leftSide++ ;
					moveShip ( order ) ;
					for ( int i = 0 ; i < 3 ; i++ )
					{
						gotoXY ( lengthScreen - 2 - i , 1 ) ;
						cout << " " ;
					}
				}
				else
					moveShip ( order ) ;
				break ;
		//	case 'w' : case 'W' :
						
		//	case 's' : case 'S' :
						
		}
				
				
				
	}
}

void moveShip ( char moveOrder )
{
	int i ;
	if ( selected . leftSide + 5 < widthScreen - 1 && selected . leftSide - 1 > 0 )
	{
		for ( i = 0 ; i < 2 ; i++ )
		{
			gotoXY ( lengthScreen - 2 - i , selected . leftSide ) ;
			cout << shipEraser [ 1 - i ] ;
		}
		if ( moveOrder == 'a' || moveOrder == 'A' )
		{
			selected . leftSide-- ;
			for ( i = 0 ; i < 2 ; i++ )
			{
				gotoXY ( lengthScreen - 2 - i , selected . leftSide ) ;
				color ( selected . color ) ;
				cout << selected . shape [ 1 - i ] ;
			}
		}
		else
		{
			selected . leftSide++ ;
			for ( i = 0 ; i < 2 ; i++ )
			{
				gotoXY ( lengthScreen - 2 - i , selected . leftSide ) ;
				color ( selected . color ) ;
				cout << selected . shape [ 1 - i ] ;
			}
		}
	}
}

void setColor ( const string& colorCode )
{
    cout << "\033[" << colorCode << "m" ;
}

void color ( char c ) // This function uses the setColor function based on the first character of each color
{
	switch ( c )
	{
		case 'r' :
			setColor ( "31" ) ;
			break ;
		case 'g' :
			setColor ( "32" ) ;
			break ;
		case 'o' :
			setColor ( "33" ) ;
			break ;
		case 'b' :
			setColor ( "34" ) ;
			break ;
		case 'm' :
			setColor ( "35" ) ;
			break ;
		case 'c' :
			setColor ( "36" ) ;
			break ;
		case 'w' :
			setColor ( "97" ) ;
			break ;
		case 'p' :
			setColor ( "91" ) ;
			break ;
		case 'l' :
			setColor ( "92" ) ;
			break ;
		case 'y' :
			setColor ( "93" ) ;
			break ;
		case 'a' :
			setColor ( "94" ) ;
			break ;
		case 'v' :
			setColor ( "95" ) ;
			break ;
		case 't' :
			setColor ( "96" ) ;
			break ;
		case 's' :
			setColor ( "90" ) ;
	}
}

void printScreen (  ) // this function print & refresh screen based on front array 
{
	int i , j ;
	for ( i = 0 ; i < lengthScreen ; i++ )
		for ( j = 0 ; j < widthScreen ; j++ )
			unicode ( i , j ) ;
}

void unicode ( int x , int y ) // This function prints the Unicode state of each element of the array onto the screen
{
	gotoXY ( x , y ) ;
	switch ( front [ x ] [ y ] )
	{
		case '_' :
			cout << "═" ;
			break ;
		case '|' :
			cout << "║" ;
			break ;
		case '`' :
			cout << "╔" ;
			break ;
		case '~' :
			cout << "╚" ;
			break ;
		case ',' :
			cout << "╝" ;
			break ;
		case '^' :
			cout << "╗" ;
			break ;
		case ' ' :
			cout << " " ;
			break ;
		case 'n' :
			cout << "╽" ;
			break ;
		case 'r' :
			cout << "╿" ;
			break ;
		case 'l' :
			cout << "┃" ;
			break ;
		case 'b' :
			cout << "💣" ;
			break ;
		case 's' :
			cout << "🢁" ;
			break ;
	}
}

void gotoXY ( int x , int y ) // This function moves the cursor to the location specified in the input arguments
{
	HANDLE consoleHandle = GetStdHandle ( STD_OUTPUT_HANDLE ) ;
	COORD cursorCoord ;
	cursorCoord . X = y ;
	cursorCoord . Y = x ;
	SetConsoleCursorPosition ( consoleHandle , cursorCoord ) ;
}

void hideCursor (  )
{
    cout << "\033[?25l" ;
}
