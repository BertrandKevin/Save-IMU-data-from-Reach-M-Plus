//
//  getData.cpp
//  Save IMU data from Reach M+
//
//  Created by Kevin Bertrand on 09/04/11.
//  Copyright © 2019 KevinBertrand. All rights reserved.
//

#include <sstream>
#include <string>

#include "../includes/getData.h"
#include "../includes/MPU9250.h"

using namespace std;

void getData(MPU9250 imu, float test[])
{
    // Initialisation des variables
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;
    
    // Réception des données
    imu.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);

    test[0] = ax;
    test[1] = ay;
    test[2] = az;
    test[3] = gx;
    test[4] = gy;
    test[5] = gz;
    test[6] = mx;
    test[7] = my;
    test[8] = mz;  

    return;
}
