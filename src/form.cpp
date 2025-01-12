#include <iostream>
#include <Windows.h>
#include "color.h"
#include "form.h"
#include "utilities.cpp"
using namespace std;

void PrintBlankForm(){
    cout << BG_BLACK << FG_WHITE << blank_form;
}
void PrintBox(int width,int height,string fg_color,string bg_color){

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

        cout << fg_color << bg_color << left;
        for(int j=0;j<width-2;j++){
            cout << inner;
        }
        cout << right;
        Gotoxy(point.x,point.y+i+1);
    }
}
