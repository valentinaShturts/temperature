#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#pragma comment(lib, "urlmon.lib")

using namespace std;


string ExtractTemperature(const char* html) 
{
    const char* marker = "<p class=\"_6fYCPKSx\">";
    char* start = strstr((char*)html, marker);
    if (start) 
    {
        start += strlen(marker);
        char* end = strstr(start, "</p>");
        if (end) 
        {
            return string(start, end - start-3);
        }
    }
    return "Not found";
}

int main() 
{
    const char* srcURL = "https://sinoptik.ua/pohoda/odesa"; 
    const char* destFile = "weather.txt";

    if (S_OK == URLDownloadToFileA(NULL, srcURL, destFile, 0, NULL)) 
    {
        cout << "Saved to " << destFile << "\n";
    }

    ifstream file(destFile); 
    if (!file) 
    {
        cout << "Failed to open file!" << endl;
        return 1;
    }

    string html((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    cout << "Temperature Odesa: " << ExtractTemperature(html.c_str()) << endl;

    return 0;
}