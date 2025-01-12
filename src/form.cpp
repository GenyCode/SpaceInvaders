#include <iostream>
#include <Windows.h>
#include "color.h"
#include "form.h"
#include "utilities.cpp"
#include <conio.h>
using namespace std;

void PrintBlankForm(){
    cout << BG_BLACK << FG_WHITE << blank_form;
}
void PrintBox(int width,int height,string fg_color){

    Coordinate point = GetCursorPosition();
    for(int i=0;i<height;i++){
        string right;
        string inner;
        string left;
        if(i==0){
            right = "╗";
            left = "╔";
            inner = "═";
        }
        else if(i==height-1){
            right = "╝";
            left = "╚";
            inner = "═";
        }
        else{
            right = "║";
            left = "║";
            inner = " ";
        }

        cout << fg_color << left;
        for(int j=0;j<width-2;j++){
            cout << inner;
        }
        cout << right;
        Gotoxy(point.x,point.y+i+1);
    }
    cout << FG_WHITE;
}
void PrintButton(Button button,Position userPosition){
    Coordinate elementPos = {start_area.x,start_area.y};
    string fg_color = "";
    if(button.position.col == userPosition.col && button.position.row == userPosition.row){
        fg_color = FG_CYAN;
    }else{
        fg_color = FG_WHITE;
    }
    elementPos.y += button.position.row * 4;
    elementPos.x += button.position.col * 54;
    int button_width = 50;
    int button_height = 3;
    Gotoxy(elementPos.x,elementPos.y);
    PrintBox(button_width,button_height,fg_color);
    Gotoxy(elementPos.x + 4,elementPos.y + (button_height/2));
    cout << fg_color << button.text << FG_WHITE;
}

int main(){
    system("cls");
    PrintBlankForm();
    PrintButton({"START GAME",{0,0}},{0,0});
    PrintButton({"SETTINGS",{1,0}},{0,0});
    PrintButton({"HOW TO PLAY",{2,0}},{0,0});
    PrintButton({"CHANGE PLAYER",{3,0}},{0,0});
    PrintButton({"EXIT",{4,0}},{0,0});
    char ch = getch();
    return 0;
}