#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

string GetUrl(const string& city)
{
    string url = "https://sinoptik.ua/pohoda/" + city;
    return url;
}

void GetWeather(const string& city, const char* destFile)
{
    const string url = GetUrl(city);
    const char* srcURL = url.c_str();


    if (S_OK == URLDownloadToFileA(NULL, srcURL, destFile, 0, NULL))
    {
        cout << "Saved to " << destFile << "\n";
    }

    ifstream file(destFile);
    if (!file)
    {
        cout << "Failed to open file!" << endl;
        return;
    }

    string html((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    cout << "Temperature " << city << ": " << ExtractTemperature(html.c_str()) << endl << endl;
}

int main()
{
    vector<string> cities = { "kyiv", "odesa", "lviv", "kharkiv", "paryzh", "london", "mykolaiv", "varshava", "biliaivskyi-raion-avhustivka", "seul"};
    const char* destFile = "weather.txt";
    cout << "\t Favourite cities\n\n";
    for (const auto& city : cities)
    {
        GetWeather(city, destFile);
    }
    
    string user_city;
    cout << "Enter city: ";
    cin >> user_city;
    GetWeather(user_city, destFile);


    return 0;
}