/* 
 * File:   ADC.h
 * Author: Table8-2
 *
 * Created on 7 octobre 2024, 11:33
 */

#ifndef ADC_H
#define	ADC_H
void InitADC1(void);
void ADC1StartConversionSequence();
void ADCClearConversionFinishedFlag(void);
void ADCClearConversionFinished();
unsigned char ADCIsConversionFinished(void);
unsigned int * ADCGetResult(void);


#endif	/* ADC_H */

