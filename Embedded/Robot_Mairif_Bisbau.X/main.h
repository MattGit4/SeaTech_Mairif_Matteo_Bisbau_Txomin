/* 
 * File:   main.h
 * Author: Table8-2
 *
 * Created on 18 octobre 2024, 11:09
 */

#ifndef MAIN_H
#define	MAIN_H
#define STATE_ATTENTE 0
#define STATE_ATTENTE_EN_COURS 1
#define STATE_AVANCE 2
#define STATE_AVANCE_EN_COURS 3
#define STATE_TOURNE_GAUCHE 4
#define STATE_TOURNE_GAUCHE_EN_COURS 5
#define STATE_TOURNE_DROITE 6
#define STATE_TOURNE_DROITE_EN_COURS 7
#define STATE_TOURNE_SUR_PLACE_GAUCHE 8
#define STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS 9
#define STATE_TOURNE_SUR_PLACE_DROITE 10
#define STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS 11
#define STATE_ARRET 12
#define STATE_ARRET_EN_COURS 13
#define STATE_RECULE 14
#define STATE_RECULE_EN_COURS 15
#define STATE_TOURNE_L_DROITE 16
#define STATE_TOURNE_L_GAUCHE 17
#define STATE_TOURNE_L_DROITE_EN_COURS 18
#define STATE_TOURNE_L_GAUCHE_EN_COURS 19
#define STATE_OUT_TIME 20
#define STATE_BLC 21
#define PAS_D_OBSTACLE 0
#define OBSTACLE_A_GAUCHE 1
#define OBSTACLE_A_DROITE 2
#define OBSTACLE_EN_FACE 3
#define OBSTACLE_S_DROITE 4
#define OBSTACLE_S_GAUCHE 5
#define OBSTACLE_L_DROITE 6
#define OBSTACLE_L_GAUCHE 7
#define OBSTACLE_TIME 8
#define SOS 9

void OperatingSystemLoop(void);
void SetNextRobotStateInAutomaticMode();



#endif	/* MAIN_H */

