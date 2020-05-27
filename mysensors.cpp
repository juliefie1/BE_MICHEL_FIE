//
//  mysensors.cpp
//  BE
//
//  Created by Julie Fié on 20/05/2020.
//  Copyright © 2020 Julie Fié. All rights reserved.
//

#include "mysensors.hpp"
#include "external_simulation.hpp"

Sensor::Sensor(){
    Device();
    val = 0;
    temps = 0;
}

//*******************************************************************************************************
//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature():Sensor(){val = GetTempExt();}

void AnalogSensorTemperature::run(){
    while(1){
        if(ptrmem!=NULL)
            *ptrmem=GetTempExt();
        sleep(temps);
    }
}

//*******************************************************************************************************
//classe AnalogSensorLuminosity
AnalogSensorLuminosity::AnalogSensorLuminosity(bool dt):Sensor(){
    val = GetLumExt();
    dt = 1;
}

void AnalogSensorLuminosity::run(){
    while(1){
        if(ptrmem!=NULL){
            *ptrmem=GetLumExt();
        }
        sleep(temps);
    }
}

//*******************************************************************************************************
// classe I2CSensorKeyboard
I2CSensorKeyboard::I2CSensorKeyboard (int add):Device(){
    kb_addr = add;
}

void I2CSensorKeyboard::run(){
    while(1){
        cin >> buf;
        Device::i2cbus->write(kb_addr, buf, 10);
        sleep(1);
    }
}


