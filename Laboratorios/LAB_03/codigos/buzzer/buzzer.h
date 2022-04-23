#ifndef BUZZER_H_
#define BUZZER_H_

/******************************************************************************************************
 ***************************            Buzzer library       ******************************************
 ******************************************************************************************************/
/* FOR STUDENTS:
 * 
 * This file will be given to you in an 'empty' state. The function bodies are
 * provided, but not their content. You are supposed to add the proper setup
 * code and complete these functions.
 *
 * Functions Beep, noBeep y Frequencies of Musical Notes: source 
 * https://create.arduino.cc/projecthub/isaacnolt331/megalovania-on-piezo-fc263a
 * 
 * This code its an adaption from public domain code. Created for educational purpose.
 *
 *
 */


/*
 *  Standard Library
 *
 */
#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Musical Note
 * Frequencies of Musical Notes

 *
 */
#define N_B0  31
#define N_C1  33
#define N_CS1 35
#define N_D1  37
#define N_DS1 39
#define N_E1  41
#define N_F1  44
#define N_FS1 46
#define N_G1  49
#define N_GS1 52
#define N_A1  55
#define N_AS1 58
#define N_B1  62
#define N_C2  65
#define N_CS2 69
#define N_D2  73
#define N_DS2 78
#define N_E2  82
#define N_F2  87
#define N_FS2 93
#define N_G2  98
#define N_GS2 104
#define N_A2  110
#define N_AS2 117
#define N_B2  123
#define N_C3  131
#define N_CS3 139
#define N_D3  147
#define N_DS3 156
#define N_E3  165
#define N_F3  175
#define N_FS3 185
#define N_G3  196
#define N_GS3 208
#define N_A3  220
#define N_AS3 233
#define N_B3  247
#define N_C4  262
#define N_CS4 277
#define N_D4  294
#define N_DS4 311
#define N_E4  330
#define N_F4  349
#define N_FS4 370
#define N_G4  392
#define N_GS4 415
#define N_A4  440
#define N_AS4 466
#define N_B4  494
#define N_C5  523
#define N_CS5 554
#define N_D5  587
#define N_DS5 622
#define N_E5  659
#define N_F5  698
#define N_FS5 740
#define N_G5  784
#define N_GS5 831
#define N_A5  880
#define N_AS5 932
#define N_B5  988
#define N_C6  1047
#define N_CS6 1109
#define N_D6  1175
#define N_DS6 1245
#define N_E6  1319
#define N_F6  1397
#define N_FS6 1480
#define N_G6  1568
#define N_GS6 1661
#define N_A6  1760
#define N_AS6 1865
#define N_B6  1976
#define N_C7  2093
#define N_CS7 2217
#define N_D7  2349
#define N_DS7 2489
#define N_E7  2637
#define N_F7  2794
#define N_FS7 2960
#define N_G7  3136
#define N_GS7 3322
#define N_A7  3520
#define N_AS7 3729
#define N_B7  3951
#define N_C8  4186
#define N_CS8 4435
#define N_D8  4699
#define N_DS8 4978

/*
 * Funcion beep
 *
 * Esta funcion se le entrega la frecuencia de la nota musical, el tiempo en milisegundos
 * y la pausa para marcar el termino de la nota definidas en milisegundos.
 *
 */
void beep (int frequencyInHertz, long timeInMilliseconds, long pausetimeInMilliseconds);


/*
 * Funcion noBeep
 *
 * La idea de esta funcion es realizar un silencio durante una cantidad de tiempo en milisegundos.
 *
 */
void noBeep(int time_ms);


/*
 * Función config speaker gpio
 *
 * Configura el pin de output para permitir el sonido del buzzer
 *
 */
void config_speaker_gpio(void);


/*
 * speaker high
 * Esta funcion permite mantener el pin de output para el buzzer en high
 *
 */
void speaker_high(void);


/*
 * speaker high
 * Esta funcion permite mantener el pin de output para el buzzer en low
 *
 */
void speaker_low(void);


/*
 * Configura el Timer XX, Puede ser A0, A1, B0...
 * 
 *
 */
void timer_XX_config(void);


/*
 * Configura la frecuencia del Timer XX
 * 
 *
 */
void config_timer_XX_frequency(int counter);


/*
 * Habilita el timer XX
 * 
 *
 */
void config_timer_XX_enable(void);

/*
 * Deshabilita el timer XX
 * 
 *
 */
void config_timer_XX_disable(void);

/* 
 *
 * Posiblemente requiera de uno o mas timers. En ese caso, recomendamos
 * que mantenga la misma estructura, cambiando el nombre de las funciones 
 * de la manera que corresponde.
 */


#endif /* BUZZER_H_ */
