#include <unistd.h>
#include "core_simulation.h"
#include "myactuators.h"
#include "mode.hpp"

// la fonction d'initialisation d'arduino
void Board::setup(){
    // on configure la vitesse de la liaison
    Serial.begin(9600);
    // on fixe les pin en entree et en sortie en fonction des capteurs/actionneurs mis sur la carte
    pinMode(1,INPUT);
    pinMode(0,OUTPUT);
    pinMode(2,INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
}

// la boucle de controle arduino
void Board::loop(){
    char buf[100];
    unsigned short val1, val2;
    int i=0;
    map<string,string>::iterator it;
    map<string,string> mySM;
    for(i=0;i<10;i++){
//        // lecture sur la pin 1 : capteur de temperature
        val1 = analogRead(1);
//        sprintf(buf,"temperature %d",val1);
//        Serial.println(buf);
//        // lecture sur la pin 2 : capteur de luminosité
        val2 = analogRead(2);
//        sprintf(buf,"luminosité %d",val2);
//        Serial.println(buf);

        sleep(1);
        sleep(2);
        
        // affichage de l'environnement extérieur
        sprintf(buf," EXTÉRIEUR:  %hu °, %hu LUX \n",val1, val2);
        bus.write(1,buf,100);
        
        // affichage de l'état des objets
        cout << ReturnStateMap();
    }
}


