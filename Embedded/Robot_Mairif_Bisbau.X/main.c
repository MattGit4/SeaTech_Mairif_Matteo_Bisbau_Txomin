#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h" 
#include "robot.h"
#include "main.h"
#include "ADC.h"


int ADCValue0;
int ADCValue1;
int ADCValue2;
int ADCValue3;
int ADCValue4;

unsigned char stateRobot;

int main(void) {
    /***********************************************************************************************/
    //Initialisation oscillateur
    /***********************************************************************************************/
    InitOscillator();

    /***********************************************************************************************/
    // Configuration des input et output (IO)
    /***********************************************************************************************/
    InitIO();
    InitTimer1();
    //InitTimer23();
    InitTimer4();
    InitPWM();
    InitADC1();


    LED_BLANCHE_1 = 0;
    LED_BLEUE_1 = 0;
    LED_ORANGE_1 = 0;
    LED_ROUGE_1 = 0;
    LED_VERTE_1 = 0;


    LED_BLANCHE_2 = 0;
    LED_BLEUE_2 = 0;
    LED_ORANGE_2 = 0;
    LED_ROUGE_2 = 0;
    LED_VERTE_2 = 0;

    //BUTTON = 0;

    /***********************************************************************************************/
    // Boucle Principale
    /***********************************************************************************************/
    while (1) {
        if (ADCIsConversionFinished() == 1) {
            ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [1])* 3.3 / 4096;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result [2])* 3.3 / 4096;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [3])* 3.3 / 4096;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result [0])* 3.3 / 4096;
            robotState.distanceTelemetreSuperGauche = 34 / volts - 5;
            volts = ((float) result [4])* 3.3 / 4096;
            robotState.distanceTelemetreSuperDroit = 34 / volts - 5;
            ADCValue0 = robotState.distanceTelemetreGauche;
            ADCValue1 = robotState.distanceTelemetreCentre;
            ADCValue2 = robotState.distanceTelemetreDroit;
            ADCValue3 = robotState.distanceTelemetreSuperGauche;
            ADCValue4 = robotState.distanceTelemetreSuperDroit;
            if (ADCValue0 < 30) {
                LED_BLEUE_1 = 1;
            } else {
                LED_BLEUE_1 = 0;
            }
            if (ADCValue1 < 30) {
                LED_ORANGE_1 = 1;
            } else {
                LED_ORANGE_1 = 0;
            }
            if (ADCValue2 < 30) {
                LED_ROUGE_1 = 1;
            } else {
                LED_ROUGE_1 = 0;
            }
            if (ADCValue3 < 30) {
                LED_BLANCHE_1 = 1;
            } else {
                LED_BLANCHE_1 = 0;
            }
            if (ADCValue4 < 30) {
                LED_VERTE_1 = 1;
            } else {
                LED_VERTE_1 = 0;
            }
            /*if (timestamp > 60000) {
                PWMSetSpeedConsigne(0, MOTEUR_DROIT);
                PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
                LED_BLANCHE_2 = 0;
                LED_BLEUE_2 = 0;
                LED_ORANGE_2 = 0;
                LED_ROUGE_2 = 0;
                LED_VERTE_2 = 0;
            }*/
        }
    }
    // fin main
}

void OperatingSystemLoop(void) {
    if (timestamp > 60000) {
        PWMSetSpeedConsigne(0, MOTEUR_DROIT);
        PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
        LED_BLANCHE_2 = 0;
        LED_BLEUE_2 = 0;
        LED_ORANGE_2 = 0;
        LED_ROUGE_2 = 0;
        LED_VERTE_2 = 0;
    } 
    else {
        switch (stateRobot) {
            case STATE_ATTENTE:

                //timestamp = 0;
                PWMSetSpeedConsigne(0, MOTEUR_DROIT);
                PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
                stateRobot = STATE_ATTENTE_EN_COURS;

            case STATE_ATTENTE_EN_COURS:
                if (timestamp > 1000)
                    stateRobot = STATE_AVANCE;
                break;
            case STATE_AVANCE:
                PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
                PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
                stateRobot = STATE_AVANCE_EN_COURS;
                break;
            case STATE_AVANCE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;
            case STATE_TOURNE_GAUCHE:
                PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
                PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
                stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
                break;
            case STATE_TOURNE_GAUCHE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;
            case STATE_TOURNE_DROITE:
                PWMSetSpeedConsigne(0, MOTEUR_DROIT);
                PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
                stateRobot = STATE_TOURNE_DROITE_EN_COURS;
                break;
            case STATE_TOURNE_DROITE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;
            case STATE_TOURNE_L_DROITE:
                PWMSetSpeedConsigne(-7.5, MOTEUR_DROIT);
                PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
                stateRobot = STATE_TOURNE_L_DROITE_EN_COURS;
                break;
            case STATE_TOURNE_L_DROITE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;
            case STATE_TOURNE_L_GAUCHE:
                PWMSetSpeedConsigne(15, MOTEUR_DROIT);
                PWMSetSpeedConsigne(-7.5, MOTEUR_GAUCHE);
                stateRobot = STATE_TOURNE_L_GAUCHE_EN_COURS;
                break;
            case STATE_TOURNE_L_GAUCHE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;
            case STATE_TOURNE_SUR_PLACE_GAUCHE:
                PWMSetSpeedConsigne(12, MOTEUR_DROIT);
                PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
                stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
                break;
            case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;
            case STATE_TOURNE_SUR_PLACE_DROITE:
                PWMSetSpeedConsigne(-7.5, MOTEUR_DROIT);
                PWMSetSpeedConsigne(7.5, MOTEUR_GAUCHE);
                stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
                break;
            case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;
            default:
                stateRobot = STATE_ATTENTE;
                break;
        }
    }
}
unsigned char nextStateRobot = 0;

void SetNextRobotStateInAutomaticMode() {
    unsigned char positionObstacle = PAS_D_OBSTACLE;
    //ÈDtermination de la position des obstacles en fonction des ÈÈËtlmtres
    if (robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche > 30 &&
            robotState.distanceTelemetreSuperDroit > 20) //Obstacle ‡droite
        positionObstacle = OBSTACLE_A_DROITE;
    else if (robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche > 30 &&
            robotState.distanceTelemetreSuperDroit < 20) //Obstacle trËs ‡ droite
        positionObstacle = OBSTACLE_S_DROITE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche < 30 &&
            robotState.distanceTelemetreSuperGauche > 20) //Obstacle ‡gauche
        positionObstacle = OBSTACLE_A_GAUCHE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche < 30 &&
            robotState.distanceTelemetreSuperGauche < 20) //Obstacle ‡gauche
        positionObstacle = OBSTACLE_S_GAUCHE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche > 30 &&
            robotState.distanceTelemetreSuperDroit < 20) //Obstacle trËs ‡ droite
        positionObstacle = OBSTACLE_L_DROITE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche > 30 &&
            robotState.distanceTelemetreSuperGauche < 20)
        positionObstacle = OBSTACLE_L_GAUCHE;
    else if (robotState.distanceTelemetreCentre < 30) //Obstacle en face
        positionObstacle = OBSTACLE_EN_FACE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche > 30) //pas d?obstacle
        positionObstacle = PAS_D_OBSTACLE;
    /*else if (robotState.distanceTelemetreDroit < 10 ||
            robotState.distanceTelemetreCentre < 10 ||
            robotState.distanceTelemetreGauche < 10 ||                              CAS URGENCE A REVOIR
            robotState.distanceTelemetreSuperDroit < 10 ||
            robotState.distanceTelemetreSuperGauche < 10)
        positionObstacle = OBSTACLE_EN_FACE;*/
    //ÈDtermination de lÈ?tat ‡venir du robot
    if (positionObstacle == PAS_D_OBSTACLE)
        nextStateRobot = STATE_AVANCE;
    else if (positionObstacle == OBSTACLE_A_DROITE)
        nextStateRobot = STATE_TOURNE_GAUCHE;
    else if (positionObstacle == OBSTACLE_S_DROITE)
        nextStateRobot = STATE_TOURNE_GAUCHE;
    else if (positionObstacle == OBSTACLE_A_GAUCHE)
        nextStateRobot = STATE_TOURNE_DROITE;
    else if (positionObstacle == OBSTACLE_S_GAUCHE)
        nextStateRobot = STATE_TOURNE_DROITE;
    else if (positionObstacle == OBSTACLE_EN_FACE)
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
    else if (positionObstacle == OBSTACLE_S_DROITE)
        nextStateRobot = STATE_TOURNE_GAUCHE;
    else if (positionObstacle == OBSTACLE_L_DROITE)
        nextStateRobot = STATE_TOURNE_L_GAUCHE;
    else if (positionObstacle == OBSTACLE_L_GAUCHE)
        nextStateRobot = STATE_TOURNE_L_DROITE;
    //Si l?on n?est pas dans la transition de lÈ?tape en cours
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;

}
