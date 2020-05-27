#include "core_simulation.h"
#include "mysensors.hpp"
#include "myactuators.h"
#include "external_simulation.hpp"

int main(){
    // creation d'une board
    Board esp8266;
    // achat des senseurs et actionneurs
    AnalogSensorTemperature temperature;
    DigitalActuatorLED AlarmLed;
    I2CActuatorScreen screen;
    AnalogSensorLuminosity luminosity(DELAY);
    Shutters volets;
    I2CSensorKeyboard AlarmKb(2);
    I2CSensorKeyboard GateKb(3);
    Alarm myAlarm;
    Gate myGate;
    Shutters myShutters;
    HeatingSystem myHeatingSystem;
    
    // branchement des capteurs actionneurs
    esp8266.pin(1,temperature);
    esp8266.pin(0, volets);
    esp8266.i2c(1,screen);
    esp8266.pin(2, luminosity);
    esp8266.i2c(2, AlarmKb);
    esp8266.i2c(3, GateKb);
    esp8266.pin(3, myGate);
    esp8266.pin(4, myShutters);
    esp8266.pin(5, myHeatingSystem);
    
    // Ajout des éléments de l'alarme
    myAlarm.AddAlarmKeyboard(&AlarmKb);
    myAlarm.AddAlarmLed(&AlarmLed);
    myAlarm.AddAlarmBoard(&esp8266);
    
    // Ajout des éléments du portail
    myGate.AddGateKeyboard(&GateKb);
    myGate.AddGateBoard(&esp8266);
    
    pthread_t thread_ext_simu;
    
    //VerifyCode(1234, &esp8266, 3);

    // Création du thread de simulation de l'environnement extérieur
    try{
        if (pthread_create(&thread_ext_simu, NULL, exterior_simulator, nullptr))
          {
              perror("Creation thread simulation exterieure\n");
              fprintf(stderr, "pthread_create() : %s\n", strerror(errno));
              exit(EXIT_FAILURE);
          }
        // allumage de la carte
        esp8266.run();
        myAlarm.run();
    }
    catch (vecterr er){
        switch (er){
            case mode_err:
                cout << "Erreur de mode" << endl;
                break;
//            case keyboard_err:
//                cout << "Erreur interaction clavier" << endl;
//                break;
        }
    }
    
    return 0;
}


