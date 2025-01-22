#include <iostream>
#include <fstream>
#include <string>
#include "Settings.h"
using namespace std;
const string filename = "settings.bin";
void SaveSettings(const Generalsettings &settings)
{
    ofstream file(filename, ios::binary);
    if (file.is_open())
    {
        file.write(reinterpret_cast<const char *>(&settings), sizeof(settings));
        file.close();
    }
}
void LoadSettings(Generalsettings &settings)
{
    ifstream file(filename, ios::binary);
    if (file.is_open())
    {
        file.read(reinterpret_cast<char *>(&settings), sizeof(settings));
        file.close();
    }
}