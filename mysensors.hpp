//
//  mysensors.hpp
//  BE
//
//  Created by Julie Fié on 20/05/2020.
//  Copyright © 2020 Julie Fié. All rights reserved.
//

#ifndef mysensors_hpp
#define mysensors_hpp

#include <stdio.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include <fstream>

// Classe mère des capteurs
class Sensor: public Device {
protected:
    // valeur mesuree
    float val;
    // temps entre 2 prises de valeurs
    int temps;
public:
    Sensor();
    virtual ~Sensor(){};
    virtual void run()=0;
};

//*******************************************************************************************************
// Capteur de la température extérieure
class AnalogSensorTemperature: public Sensor {
public:
    //constructeur ne pas oublier d'initialiser la classe mere
    AnalogSensorTemperature();
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

//*******************************************************************************************************
// Capteur de la luminosité extérieure
class AnalogSensorLuminosity: public Sensor {
public:
    AnalogSensorLuminosity(bool dt);
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

//*******************************************************************************************************
// Capteur de clavier
class I2CSensorKeyboard: public Device {
protected:
    // memorise l'affichage de l'ecran
    char buf[10];
    // adresse du bus I2C
    int kb_addr;
public:
    I2CSensorKeyboard(int add);
    virtual void run();
    char * getBuf(){return buf;};
    int getAddr(){return kb_addr;};
};


#endif /* mysensors_hpp */
