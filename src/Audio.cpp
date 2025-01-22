#include <windows.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void PlayEffectSound(const string& filePath) {
    PlaySoundA(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void PlaySoundFile(const string& alias, const string& filePath, bool loop = false) {
    string command = "open \"" + filePath + "\" type mpegvideo alias " + alias;
    if (mciSendStringA(command.c_str(), NULL, 0, NULL) != 0) {
        cerr << "Error: Could not open file " << filePath << endl;
        return;
    }

    command = "play " + alias + (loop ? " repeat" : "");
    if (mciSendStringA(command.c_str(), NULL, 0, NULL) != 0) {
        cerr << "Error: Could not play file " << filePath << endl;
        return;
    }
}

void StopSoundFile(const string& alias) {
    string command = "stop " + alias;
    if (mciSendStringA(command.c_str(), NULL, 0, NULL) != 0) {
        cerr << "Error: Could not stop " << alias << endl;
    }

    command = "close " + alias;
    if (mciSendStringA(command.c_str(), NULL, 0, NULL) != 0) {
        cerr << "Error: Could not close " << alias << endl;
    }
}
int GetSoundFileDuration(const string& alias) {
    char buffer[128];
    string command = "status " + alias + " length";
    if (mciSendStringA(command.c_str(), buffer, sizeof(buffer), NULL) == 0) {
        return stoi(buffer);
    }
    cerr << "Error: Could not get duration for " << alias << endl;
    return 0;
}

void PlayBackgroundMusic(){
    PlaySoundFile("background", "Theme1.wav", true);
}
void StopBackgroundMusic(){
    StopSoundFile("background");
}
void PlayNavigateSound() {
    PlayEffectSound("Navigate.wav");
}

void PlayAlertSound() {
    PlayEffectSound("Alert.wav");
}