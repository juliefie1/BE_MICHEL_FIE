#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include <fstream>
#include "mysensors.hpp"
#include "external_simulation.hpp"
#include "mode.hpp"
#include <map>

#define FILEPATH "Desktop/C++/BE_C++"

// exceptions
enum vecterr{mode_err};

// Classe mère des actionneurs
class Actuator: public Device {
protected:
    bool state;
    // temps entre 2 affichage de l etat de la led
    int temps;
public:
    Actuator();
    virtual ~Actuator(){};
    virtual void run()=0;
};

//*******************************************************************************************************
// LED qui s'allume lorsque l'alarme se déclenche
class DigitalActuatorLED: public Actuator {
public:
    void setStateLED(bool s){state = s;};
    DigitalActuatorLED();
    // thread representant l'actionneur et permettant de fonctionner independamment de la board
    virtual void run();
};

//*******************************************************************************************************
//logiciel d'alarme
class Alarm {
private:
    // state: 1 = alarme allumée, 0 = alarme éteinte
    bool state;
    // code de l'alarme, à comparer avec le code entré par l'utilisateur
    const int AlarmCode = 3140;
    // Détection d'une infraction : infraction = 1 (TRUE)
    bool infraction;
    // LED de l'alarme qui s'allume lors d'une infraction
    // AlarmLed allumée = l'alarme sonne
    DigitalActuatorLED * AlarmLed;
    // clavier permettant d'entrer le code de l'alarme
    I2CSensorKeyboard * AlarmKeyboard;
    Board * AlarmBoard;
public:
    Alarm();
    virtual ~Alarm(){};
    virtual void run();
    virtual void DisableAlarm();
    // Méthodes permettant d'ajouter les différents device à l'alarme
    void AddAlarmKeyboard(I2CSensorKeyboard * kb_add);
    void AddAlarmLed(DigitalActuatorLED * led);
    void AddAlarmBoard(Board * board);
};

//*******************************************************************************************************
class Gate : public Actuator {
private:
    // state: 0 = portail fermé, 1 = portail ouvert
    // code du portail, à comparer avec le code entré par l'utilisateur
    const int GateCode = 8010;
    // clavier permettant d'entrer le code du portail
    I2CSensorKeyboard * GateKeyboard;
    Board * GateBoard;
public:
    Gate();
    virtual ~Gate(){};
    virtual void run();
    void AddGateKeyboard(I2CSensorKeyboard * kb_add);
    void AddGateBoard(Board * board);
};

//*******************************************************************************************************
class Shutters : public Actuator {
private:
    // state: 1 = volets ouverts, 0 = volets fermés
    AnalogSensorLuminosity ShuttersSensor();
public:
    Shutters();
    virtual ~Shutters(){};
    virtual void run();
};

//*******************************************************************************************************
class HeatingSystem : public Actuator {
private:
    // state: 1 = chauffage allumé, 0 = chauffage éteint
    // Température du chauffage lorsqu'il est allumé
    const int temp = 20;
    AnalogSensorTemperature * HeatingSystemSensor();
public:
    HeatingSystem();
    virtual ~HeatingSystem(){};
    virtual void run();
};

//*******************************************************************************************************
// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorScreen : public Device {
protected:
    // memorise l'affichage de l'ecran
    char buf[I2C_BUFFER_SIZE];
public:
    // constructeur
    I2CActuatorScreen ();
    // thread representant le capteur et permettant de fonctionner independamment de la board
    virtual void run();
};

//*******************************************************************************************************
// fonction de vérification d'un code tapé au clavier
bool VerifyCode(int code, Board * b, int add_kb);

//*******************************************************************************************************
// Accesseur à StateMap
map<string,string> ReturnStateMap();

#endif
