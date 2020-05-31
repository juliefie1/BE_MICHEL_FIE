//
//  mode.cpp
//  ApplicationDomotique
//
//  Created by Julie Fié on 24/05/2020.
//  Copyright © 2020 Julie Fié. All rights reserved.
//

#include "mode.hpp"

Mode::Mode(){
    // par défaut, le mode actif est SEMAINE
    ActualMode = 2;
}

void Mode::SelectMode (int d, int w){
    
    // Tous les ans, la famille prend ses vacances une semaine en février
    // une pour Pâques, deux en juillet et deux pour Noël
    if (w == 7 || w == 17 || w == 30|| w == 31 || w == 51 || w == 52){
        ActualMode = 0;
        cout << "MODE ACTIF: " << mode[ActualMode] << endl << endl;
        return;
    }
    if (d < 6){
        ActualMode = 2;
    }
    else{
        ActualMode = 1;
    }
    cout << "MODE ACTIF: " << mode[ActualMode] << endl << endl;
}

map<string,string> InitStateMap(){
    // Map reliant les objets à leur état
    // Mis à jour à constamment dans les run de chaque objet
    map<string, string> StateMap;
    StateMap[" Alarme "]= "initialisation";
    StateMap[" Portail "]= "initialisation";
    StateMap[" LED "]= "initialisation";
    StateMap[" Volets "]= "initialisation";
    StateMap[" Chauffage "]= "initialisation";
    return StateMap;
}

// Redéfinition de l'opérateur << pour afficher une map
ostream& operator << (ostream &os, map<string,string> Map){
    // affichage de l'état des objets
    map<string,string>::iterator it;
    for (it=Map.begin(); it!=Map.end(); it++){
        cout << it->first << ": " << it->second << endl;
    }
    os << endl;
    return os;
}

