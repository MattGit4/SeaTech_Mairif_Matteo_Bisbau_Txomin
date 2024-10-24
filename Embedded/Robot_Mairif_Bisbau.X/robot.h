/* 
 * File:   robot.h
 * Author: Table8-2
 *
 * Created on 2 octobre 2024, 12:24
 */

#ifndef ROBOT_H
#define ROBOT_H

typedef struct robotStateBITS {

    union {

        struct {
            unsigned char taskEnCours;
            float vitesseGaucheConsigne;
            float vitesseGaucheCommandeCourante;
            float vitesseDroiteConsigne;
            float vitesseDroiteCommandeCourante;
            float distanceTelemetreDroit;
            float distanceTelemetreCentre;  
            float distanceTelemetreGauche;
            float distanceTelemetreSuperDroit; 
            float distanceTelemetreSuperGauche;
        };
    };
} ROBOT_STATE_BITS;
extern volatile ROBOT_STATE_BITS robotState;
#endif /* ROBOT_H */

