/* 
 * File:   IO.h
 * Author: TP-EO-5
 *
 * Created on 2 octobre 2024, 09:33
 */

#ifndef IO_H
#define IO_H

//Affectation des pins des LEDS    
#define LED_BLANCHE_1 _LATJ6
#define LED_BLEUE_1 _LATJ5
#define LED_ORANGE_1 _LATJ4 
#define LED_ROUGE_1 _LATJ11
#define LED_VERTE_1 _LATH10



#define LED_BLANCHE_2 _LATA0
#define LED_BLEUE_2 _LATA9
#define LED_ORANGE_2 _LATK15 
#define LED_ROUGE_2 _LATA10
#define LED_VERTE_2 _LATH3
// Prototypes fonctions
void InitIO();
void LockIO();
void UnlockIO();

//BUTTON!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define BUTTON _RH1
#endif /* IO_H */

