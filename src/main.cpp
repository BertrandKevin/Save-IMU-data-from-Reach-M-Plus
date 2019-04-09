//
//  main.cpp
//  Save IMU data from Reach M+
//
//  Created by Kevin Bertrand on 09/04/11.
//  Copyright © 2019 KevinBertrand. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>

#include "../includes/getData.h"
#include "../includes/MPU9250.h"
#include "../includes/searchFilePath.h"

using namespace std;

int main()
{
    // Initialisation et configuration de l'IMU
    MPU9250 imu;
    imu.initialize();
    
    // Verification de le connection avec l'IMU
    if(imu.doSelfTest())
    {
        cout << "MPU9250 connecté!" << endl;
    }
    else
    {
        cout << "MPU9250 non connecté!" << endl;
    }
    
    // Initialisation des variables
    bool start = true;
    char lastSecond(' ');
    char lastHour(' ');
    string toWrite;
    string path;
    
    // Boucle infinie de réception des données
    while(true)
    {
        // Recherche du temps actuel
        time_t startProgram = time(0);
        char* temp = ctime(&startProgram);
        string now = temp;
        
        /*
            Vérifier si l'heure a changé pour modifier le chemin vers le fichier
         */
        if(lastHour != now[12])
        {   
            // Changer le chemin du fichier
            path = searchPath();
            
            // Creation du fichier
            ofstream file(path.c_str(), ios::out | ios::trunc);
            if(file)
            {
                file << "";
            }
            file.close();
            lastHour = now[12];
            start = false;
        }
        
        /*
            Vérifie si la seconde à changer pour écrire dans le fichier
         */
        if(lastSecond != now[18])
        {
            // Ecrire dans le fichier
            ofstream file(path.c_str(), ios::out | ios::app);
            if(file)
            {
                file << toWrite;
                toWrite = "";
            }
            file.close();
            lastSecond = now[18];
        }
        
        // Réception des données de l'IMU
	float test[9] = {0,0,0,0,0,0,0,0,0};
	getData(imu, test);

	time_t nowData = time(0);
    	char* tempData = ctime(&nowData);
    
    	string dt = tempData;
    
    	string receive = dt.erase(dt.length()-1, 1) + "\t";
	receive += "Acc (g): " + to_string(test[0]) + "  " + to_string(test[1]) + "  " + to_string(test[2]) + "\t";
	receive += "Gyr (°/s): " + to_string(test[3]) + "  " + to_string(test[4]) + "  " + to_string(test[5]) + "\t";
	receive += "Mag (µT): " + to_string(test[6]) + "  " + to_string(test[7]) + "  " + to_string(test[8]) + "\n";

	cout << receive << endl;
	cout << path << endl;

        toWrite += receive;

	usleep(70000);
    }
    
    return 0;
}
