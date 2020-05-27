//
//  mode.hpp
//  ApplicationDomotique
//
//  Created by Julie Fié on 24/05/2020.
//  Copyright © 2020 Julie Fié. All rights reserved.
//

#ifndef mode_hpp
#define mode_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <map>

using namespace std;

// Différents modes d'utilisation des élements selon plusieurs critères
// 3 modes: vacances, semaine et week-end
class Mode{
private:
    string mode[3] = {"vacation", "weekend", "week"};
    // 3 MODES: vacances (0), weekend(1), semaine(2)
    int ActualMode;
public:
    Mode();
    // Fonction automatisant le choix des modes
    void SelectMode (int d, int w);
    int getActualMode(){return ActualMode;};
};

// Initialisation de StateMap
map<string,string> InitStateMap();

// Redéfinition de l'opérateur <<
ostream& operator << (ostream &os, map<string,string> Map);



#endif /* mode_hpp */
