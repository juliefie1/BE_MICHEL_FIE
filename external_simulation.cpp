//
//  external_simulation.cpp
//  BE
//
//  Created by Julie Fié on 22/05/2020.
//  Copyright © 2020 Julie Fié. All rights reserved.
//

#include "external_simulation.hpp"
// TEMPS ADAPTÉS POUR LA SIMULATION
// une journée en secondes
#define JOURNEE 86400
// une heure en secondes
#define HEURE 3600

static volatile unsigned short luminosite_ext;
static volatile unsigned short temperature_ext;
static volatile unsigned int hour = 0;
static Mode modeActif;

// On décide de commencer la simulation le vendredi de la 6eme semaine de l'année
// On peut de cette façon observer le déroulement de tous les modes
// Semaine (vendredi), Weekend (Samedi,Dimanche), et Vacances (semaine 7)
void *exterior_simulator(void *_arg)
{
    static unsigned long long int t = 0;
    static unsigned int day = 4;
    static unsigned int week = 6;
    map<string,string>::iterator it;
    // pas d'echantillonage
    static unsigned int delta = HEURE/1000;
    while(1){
        luminosite_ext = 100 * sin((2*M_PI*t)/(JOURNEE/3000));
        if (luminosite_ext > 100){
            luminosite_ext = 100;
        }
        temperature_ext = 25 * sin((2*M_PI*t)/(JOURNEE/300));
        t+=delta;
        sleep(HEURE/1000);
        if ((1000*t)%HEURE)
            hour++;
        if ((1000*t)%JOURNEE){
            day++;
            hour = 0;
        }
        if(day > 7){
            week++;
            day = 1;
        }
        cout << "SEMAINE " << week << " JOUR " << day << endl << endl;
        modeActif.SelectMode(day, week);
    }
    //pthread_exit(NULL);
}

short GetTempExt(){
    return temperature_ext;
}

short GetLumExt(){
    return luminosite_ext;
}

int GetActualMode(){
    return modeActif.getActualMode();
}

int GetHour(){
    return hour;
}

