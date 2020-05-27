//
//  external_simulation.hpp
//  BE
//
//  Created by Julie Fié on 22/05/2020.
//  Copyright © 2020 Julie Fié. All rights reserved.
//

#ifndef exterior_simulation_hpp
#define exterior_simulation_hpp

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include "core_simulation.h"
#include "mode.hpp"
#include "myactuators.h"

// Simulateur extérieur
// Permet d'ajuster la luminosité extérieure selon jour/nuit
// Joue le rôle de calendrier pour les saisons pour ajuster la température extérieure
void *exterior_simulator(void *_arg);

// Retourne la température extérieure
short GetTempExt();

// Retourne la luminosité extérieure
short GetLumExt();

// Retourne le mode actif
int GetActualMode();

//Retourne l'heure
int GetHour();

#endif /* exterior_simulation_hpp */

