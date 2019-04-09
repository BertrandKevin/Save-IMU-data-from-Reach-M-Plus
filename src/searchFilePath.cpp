//
//  searchFilePath.cpp
//  Save IMU data from Reach M+
//
//  Created by Kevin Bertrand on 09/04/11.
//  Copyright © 2019 KevinBertrand. All rights reserved.
//

#include <string>
#include <iostream>

#include "../includes/searchFilePath.h"

using namespace std;

string dateFormatting(string dateRaw)
{
    // Delete the "\n" at the end of the string
    dateRaw.erase(dateRaw.length()-1, 1);
    
    string day = "";
    if(dateRaw[8] == ' ')
    {
     	day += '0';
    }
    else
    {
     	day += dateRaw[8];
    }
    day += dateRaw[9];
    
    string month = "";
    switch(dateRaw[4])
    {
        case 'J':
            switch(dateRaw[5])
        {
            case 'a': month = "01";
                break;
            case 'u':
                switch(dateRaw[6])
            {
                case 'n': month = "06";
                    break;
                case 'l': month = "07";
                    break;
                default: month = "00";
            }
                break;
            default: month = "00";
        }
            break;
        case 'F': month = "02";
            break;
        case 'M':
            switch(dateRaw[6])
        {
            case 'r': month = "03";
                break;
            case 'y': month = "05";
                break;
            default: month = "00";
        }
            break;
        case 'A':
            switch(dateRaw[5])
        {
            case 'p': month = "04";
                break;
            case 'u': month = "08";
                break;
            default: month ="00";
        }
            break;
        case 'S': month = "09";
            break;
        case 'O': month = "10";
            break;
        case 'N': month = "11";
            break;
        case 'D': month = "12";
            break;
        default: month = "00";
    }
    
    
    string year = "";
    year += dateRaw[20];
    year += dateRaw[21];
    year += dateRaw[22];
    year += dateRaw[23];
    
    string hour = "";
    hour += dateRaw[11];
    hour += dateRaw[12];
    
    string dateFormated = year;
    dateFormated += "-" + month;
    dateFormated += "-" + day;
    dateFormated += "_" + hour;
    
    return dateFormated;
}

string searchPath()
{
    string path = "";
    
    time_t startProgram = time(0);
    char* temp = ctime(&startProgram);
    
    string timeFile = temp;
    
    string dateFormated = dateFormatting(timeFile);
    
    path = "/home/root/Save-IMU-data-from-Reach-M-Plus-master/TXT-Files/Reach_IMU_" + dateFormated;
    path += "h.txt";

    cout << path << endl;
    
    return path;
}

