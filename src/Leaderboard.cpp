#include <fstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "color.h"
#include "Leaderboard.h"
#include "player.h"
#include "form.h"
#include "utilities.h"
using namespace std;

string GetDefaultFileName(){
    return "scoreBoard.txt"; 
}
void bubbleSort(Player players[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}

void ReadPlayersFromFile(string Filename, Player players[], int &counter) {
    fstream dataFile;
    dataFile.open(Filename, ios::in);
    if (!dataFile) {
        cerr << "Error opening file!" << endl;
        return;
    }
    while (dataFile >> players[counter].name >> players[counter].score) {
        counter++;
        if (counter == 10) {
            break;
        }
    }
    dataFile.close();
}

void WritePlayersToFile(string Filename, Player players[], int counter) {
    fstream dataFile;
    dataFile.open(Filename, ios::out);
    if (!dataFile) {
        cerr << "Error writing to file!" << endl;
        return;
    }
    for (int i = 0; i < counter; i++) {
        dataFile << players[i].name << " " << players[i].score;
    }
    dataFile.close();
}
void Leaderboard(string Filename)
{
    
};
void UpdateLeaderboard(string Filename,Player player){
    Player players[20];
    int counter = 0;
    ReadPlayersFromFile(Filename,players,counter);
    players[counter] = player;
    counter++;
    bubbleSort(players, counter);
    if (counter > 20) {
        counter = 20;
    }
    WritePlayersToFile(Filename, players, counter);
}
void UpdateLeaderboard(Player player){
    UpdateLeaderboard(GetDefaultFileName(),player);
}
