//
// Created by yuanliheng on 4/11/24.
//

#include "functions.h"
#include <sstream>

vector<int> readConfigFile(const string& filename) {
    vector<int> gameData;

    // Open the file
    ifstream configFile(filename);
    if (!configFile.is_open()) {
        cerr << "Error: Unable to open config file '" << filename << "'" << endl;
        return gameData;
    }

    // Read each line of the file
    string line;
    while (getline(configFile, line)) {

        int num = stoi(line);
        gameData.push_back(num);
    }
    // Close the file
    configFile.close();

    return gameData;
}

map<string,string> readTxtFile(const string& filename){

    map<string,string> leaderboardMap;

    ifstream txtFile(filename);
    if(!txtFile.is_open()){
        cerr << "Error: Unable to open txt file '" << filename << "'" << endl;
        return leaderboardMap;
    }

    // Read each line of the file
    string read;
    while (getline(txtFile, read, ',')) {
        string time = read;
        getline(txtFile, read);
        string name = read;
        leaderboardMap[name] = time;




    }

    return leaderboardMap;
}

void writeTxtFile(const string& filename, map<string,string> content_map){
    ofstream file;
    file.open(filename);
    if (!file) {
        throw runtime_error("File failed to open.");
    }

    map<int, string> time_int_to_str;
    vector<int> time_in_sec;

    for (auto pair : content_map){
        string time_in_string = pair.second;

        // Parse the seconds and seconds from the string
        int minutes, seconds;

        std::istringstream ss(time_in_string);
        char colon;
        ss >> minutes >> colon >> seconds;

        // Calculate total seconds
        int totalSeconds = minutes * 60 + seconds;
        time_in_sec.push_back(totalSeconds);

        // store the integer and time string together
        time_int_to_str[totalSeconds] = time_in_string;
    }

    sort(time_in_sec.begin(), time_in_sec.end());


    // find the corresponding name in the map
    for (int i = 0; i < 5; i++){
        string target_str_time = time_int_to_str[time_in_sec[i]];
        for (auto pair : content_map){
            if (pair.second == target_str_time){
                file << target_str_time << "," << pair.first;
                if (i != 4){
                    file << "\n";
                }
            }
        }
    }




}

bool compareTime(const string& time1, const string& time2) {
    // Extract hours and minutes from time strings
    int hours1 = stoi(time1.substr(0, 2));
    int minutes1 = stoi(time1.substr(3, 2));
    int hours2 = stoi(time2.substr(0, 2));
    int minutes2 = stoi(time2.substr(3, 2));

    // Compare hours
    if (hours1 != hours2) {
        return hours1 < hours2;
    }

    // If hours are equal, compare minutes
    return minutes1 < minutes2;
}