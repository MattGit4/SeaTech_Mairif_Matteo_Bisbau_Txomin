/* 
 * File:   PWM.h
 * Author: Table8-2
 *
 * Created on 7 octobre 2024, 09:00
 */

#ifndef PWM_H
#define	PWM_H
#define MOTEUR_DROIT 0
#define MOTEUR_GAUCHE 1

void InitPWM();
void PWMSetSpeedConsigne(float vitesseEnPourcents, unsigned char moteur);
void PWMUpdateSpeed() ;
//void PWMSetSpeed(float, int);


#endif	/* PWM_H */

