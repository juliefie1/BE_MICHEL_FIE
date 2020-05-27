
#include "myactuators.h"
#include "external_simulation.hpp"
#include "mysensors.hpp"

using namespace std;

// permet de savoir quand la famille est rentrée, grâce au portail
// 0: pas rentré, 1: rentré
static volatile bool BackHome;

// Map reliant les objets à leur état
// Mis à jour à constamment dans les run de chaque objet
map<string,string> myStateMap = InitStateMap();
map<string,string> ReturnStateMap(){return myStateMap;};

Actuator::Actuator(){
    state = 0;
    temps = 0;
}

//*******************************************************************************************************
//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED():Actuator(){}

void DigitalActuatorLED::run(){
    while(1){
        if(ptrmem!=NULL){
            state=*ptrmem;
            if (state)
                myStateMap[" LED "]= "allumée";
            else
                myStateMap[" LED "]= "éteinte";
        }
        sleep(temps);
    }
}
//*******************************************************************************************************
//Fonction de vérification d'un code entré au clavier
// argument, l'adresse du clavier 2 ou 3 (deux claviers différents)
// clavier 2: clavier de l'alarme
// clavier 3: clavier du portail
bool VerifyCode (int code, Board * b, int add_kb) {
    char buf[10];
    unsigned int compt = 0;
    cout << "Entrez le code svp" << endl;
    int UserCode;
    while (compt < 3){
        while (b->bus.isEmptyRegister(add_kb)){
            sleep(1);
        }
        UserCode = b->bus.requestFrom(add_kb,buf,1);
        cout << "code: " << UserCode << endl;
        if (UserCode == 2){
            cout << "bon code" << endl;
            return true; // Code vérifié OK
        }
        else{
            compt++;
            cout << "Code erroné, nombre d'essais restants: " << 3-compt << endl;
            if (3-compt != 0){
                cout << "Entrez le code svp" << endl;
            }
        }
    }
    return false; // Code non vérifié, 3 essais échoués
}
//*******************************************************************************************************
//classe Alarm
Alarm::Alarm(){
    infraction = 0;
    state = 0;
}

// Tâche de fond de l'alarme
void Alarm::run(){
    while(1){
        if (state){
            if (BackHome){
                DisableAlarm();
            }
            if(ifstream(string(FILEPATH)+"infraction.txt")){
                infraction = 1;
                AlarmLed->setStateLED(1); // l'alarme sonne
            }
            else{
                infraction = 0;
                AlarmLed->setStateLED(0);
            }
        }
        if (state)
            myStateMap[" Alarme "]= "allumée";
        else
            myStateMap[" Alarme "]= "éteinte";
    }
}

void Alarm::AddAlarmKeyboard(I2CSensorKeyboard * kb_add){
    AlarmKeyboard = kb_add;
}

void Alarm::AddAlarmLed(DigitalActuatorLED * led){
    AlarmLed = led;
}

void Alarm::AddAlarmBoard(Board * board){
    AlarmBoard = board;
}

// Fonction de désactivation de l'alarme
// Comparaison entre le code rentré par l'utilisateur et le code de l'alarme
void Alarm::DisableAlarm(){
    if (VerifyCode(AlarmCode, AlarmBoard, AlarmKeyboard->getAddr())){
        infraction = 0;
        state = 0; // on éteint l'alarme
    }
    else if (!VerifyCode(AlarmCode, AlarmBoard, AlarmKeyboard->getAddr())){
        infraction = 1;
        AlarmLed->setStateLED(1); // l'alarme sonne
    }
}

//*******************************************************************************************************
//classe Gate
Gate::Gate():Actuator(){};

// On part du principe que les modes sont respectés
// ie la famille rentre que le soir pour le mode semaine
// et qu'en fin de vacances pour le mode vacances
void Gate::run(){
    while(1){
        //if(ifstream(string(FILEPATH)+"voiture.txt")){
        if (ifstream(string(FILEPATH)+"voiture.txt")){
            if(VerifyCode(GateCode, GateBoard, GateKeyboard->getAddr())){
                state = 0; // on ouvre le portail
                BackHome = 1;
            }
            else if (!VerifyCode(GateCode, GateBoard, GateKeyboard->getAddr())){
                state = 1;
                // avertissement quand 3 codes erronés de suite
                cout << "ATTENTION, mauvais code portail entré 3 fois d'affilée" << endl;
            }
        }
        if (state)
            myStateMap[" Portail "]= "ouvert";
        else
            myStateMap[" Portail "]= "fermé";
    }
}

void Gate::AddGateKeyboard(I2CSensorKeyboard * kb_add){
    GateKeyboard = kb_add;
}

void Gate::AddGateBoard(Board * board){
    GateBoard = board;
}

//*******************************************************************************************************
// classe Shutters
Shutters::Shutters():Actuator(){};

void Shutters::run(){
    while(1){
        if (GetActualMode() == 0){ // MODE VACANCES
            state = 0;
        }
        else if (GetActualMode() == 1 || GetActualMode() == 2){ // MODE WEEKEND ET SEMAINE
            if (GetLumExt() < 40){ // nuit, on ferme les volets
                state = 0;
            }
            else{
                state = 1;
            }
        } else{
            cout << "probleme1" << GetActualMode() << endl;
            throw mode_err;
        }
        
        if (state)
            myStateMap[" Volets "]= "ouverts";
        else
            myStateMap[" Volets "]= "fermés";
       
    }
}

//*******************************************************************************************************
// classe HeatingSystem
HeatingSystem::HeatingSystem():Actuator(){};

void HeatingSystem::run(){
    while(1){
        if (GetActualMode()==0){ // MODE VACANCES
            state = 0;
        }
        else if (GetActualMode()==1){ // MODE WEEKEND
            if (GetTempExt() < 15){ // froid, on allume le chauffage
                state = 1;
            }
            else{
                state = 0;
            }
        }
        else if (GetActualMode()==2){ // MODE SEMAINE
            // chauffage éteint en journée pour faire des économies
            if (GetTempExt() < 15){
                if (GetHour() < 8 || GetHour() > 17){
                    state = 1;
                }
                else if ( 8 < GetHour() && GetHour() < 17){
                    state = 0;
                }
                    
            }
            else{
                state = 0;
            }
        }else{
            cout << "probleme2" << GetActualMode() << endl;
            throw mode_err;
        }
        
        if (state)
            myStateMap[" Chauffage "]= "allumé";
        else
            myStateMap[" Chauffage "]= "éteint";
    }
}

//*******************************************************************************************************
// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
}

void I2CActuatorScreen::run(){
    while(1){
        if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
            Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
            cout << "---"<< buf << endl;
        }
        sleep(1);
    }
}
    



