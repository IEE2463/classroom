#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include "buzzer/buzzer.h"

/*
 * My songs
 * Reference:
 * Imperial March: https://gist.github.com/tagliati/1804108
 * Megalovania: https://create.arduino.cc/projecthub/isaacnolt331/megalovania-on-piezo-fc263a
 * Eight Days a Week: https://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0134050
 *
 */
void ImperialMarch(void);
void Eight_days_a_week(void);
void Megalovania(void);


/*
 * Main
 *
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Modificar acorde al nombre creado en buzzer.h
    timer_XX_config();

    config_speaker_gpio();
    speaker_low();

    __enable_interrupt(); // Enable interrupts globally


    // Ajustar while(1) para los siguientes task.
    while(1)
    {
        ImperialMarch();
        noBeep(2000);
        Eight_days_a_week();
        noBeep(2000);
        Megalovania();
        noBeep(2000);
    }
}


void Eight_days_a_week(void) {
  int melody[] = {N_E5, N_D5, N_C5, N_D5, N_D5, N_A4, N_A4, N_C5, N_F5, N_F5,
                  N_E5, N_E5, N_D5, N_C5, N_D5, N_D5, N_A4, N_A4, N_C5, N_F5,
                  N_F5, N_E5,

                  // Hold me love me
                  N_E5, N_C5, N_D5, N_A4, N_E5, N_C5, N_D5, N_A4,

                  // Aint got nothing but love babe
                  N_E5, N_D5, N_C5, N_C5, N_D5, N_D5, N_A4,

                  // Eight days a week
                  N_F5, N_F5, N_F5, N_E5, N_D5, N_C5};

  int noteDurations[] = {500,  500,  500,  500,  1000, 1000, 500,  500,
                         500,  500,  2000, 500,  500,  500,  500,  1000,
                         1000, 500,  500,  500,  500,  1000,

                         1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
                         500,  500,  250,  250,  500,  1000, 1000,

                         500,  500,  500,  250,  250,  1000};

  unsigned int melody_len = sizeof(melody) / sizeof(melody[0]);

  unsigned int thisNote = 0;

  for (thisNote = 0; thisNote < melody_len; thisNote++) {
    unsigned int noteDuration = noteDurations[thisNote];
    beep(melody[thisNote], noteDuration, 20);

  }
}

void ImperialMarch(void) {
  int melody[] = {
      N_A4, N_A4, N_A4, N_F4, N_C5,  // 0,1,2,3,4
      N_A4, N_F4, N_C5, N_A4,  // 5,6,7,8
      // first bit
      N_E5, N_E5, N_E5, N_F5, N_C5,  // 13
      N_GS4, N_F4, N_C5, N_A4,  // 17
      // second bit...

      N_A5, N_A4, N_A4, N_A5, N_GS5, N_G5,  // 23
      N_FS5, N_F5, N_FS5,  // 26

      // delay(125)

      N_AS4, N_DS5, N_D5, N_CS5,  // 30

      // start of the interesting bit

      N_C5, N_B4, N_C5,  // 33

      // delay 125

      N_F4, N_GS4, N_F4, N_A4,  // 37

      N_C5, N_A4, N_C5, N_E5,  // 41

      N_A5, N_A4, N_A4, N_A5, N_GS5, N_G5,  // 47
      N_FS5, N_F5, N_FS5,  // 50

      // delay(125)

      N_AS4, N_DS5, N_D5, N_CS5,  // 54

      N_C5, N_B4, N_C5,  // 57

      // delay

      N_F4, N_GS4, N_F4, N_C5,  // 61
      N_A4, N_F4, N_C5, N_A4  // 65

  };

  int noteDurations[] = {500, 500, 500, 350,  150, 500, 350, 150, 1000,

                         500, 500, 500, 350,  150, 500, 350, 150, 1000,

                         500, 350, 150, 500,  350, 125, 125, 125, 250,

                         250, 500, 350, 125,  125, 125, 250,

                         250, 500, 375, 125,

                         500, 375, 125, 1000,

                         500, 350, 150, 500,  350, 125, 125, 125, 250,

                         250, 500, 350, 125,

                         125, 125, 250, 250,  500, 375, 125,

                         500, 375, 125, 1000};

  unsigned int melody_len = sizeof(melody) / sizeof(melody[0]);

  unsigned int thisNote = 0;

  for (thisNote = 0; thisNote < melody_len; thisNote++) {
    unsigned int noteDuration = noteDurations[thisNote];
    beep(melody[thisNote], noteDuration, 10);
    if ((thisNote == 26) || (thisNote == 33) || (thisNote == 50) ||
        (thisNote == 57)) {
      noBeep(300);
    }

  }
}

void Megalovania(void) {
  int const TEMPO = 1000;

  int melody[] = {
      N_D3,  N_D3,  N_D4,  N_A3,  0,     N_GS3, N_G3,  N_F3,  N_D3, N_F3, N_G3,
      N_C3,  N_C3,  N_D4,  N_A3,  0,     N_GS3, N_G3,  N_F3,  N_D3, N_F3, N_G3,
      N_B2,  N_B2,  N_D4,  N_A3,  0,     N_GS3, N_G3,  N_F3,  N_D3, N_F3, N_G3,
      N_AS2, N_AS2, N_D4,  N_A3,  0,     N_GS3, N_G3,  N_F3,  N_D3, N_F3, N_G3,
      N_D3,  N_D3,  N_D4,  N_A3,  0,     N_GS3, N_G3,  N_F3,  N_D3, N_F3, N_G3,
      N_C3,  N_C3,  N_D4,  N_A3,  0,     N_GS3, N_G3,  N_F3,  N_D3, N_F3, N_G3,
      N_B2,  N_B2,  N_D4,  N_A3,  0,     N_GS3, N_G3,  N_F3,  N_D3, N_F3, N_G3,
      N_AS2, N_AS2, N_D4,  N_A3,  0,     N_GS3, N_G3,  N_F3,  N_D3, N_F3, N_G3,
      N_D4,  N_D4,  N_D5,  N_A4,  0,     N_GS4, N_G4,  N_F4,  N_D4, N_F4, N_G4,
      N_C4,  N_C4,  N_D5,  N_A4,  0,     N_GS4, N_G4,  N_F4,  N_D4, N_F4, N_G4,
      N_B3,  N_B3,  N_D5,  N_A4,  0,     N_GS4, N_G4,  N_F4,  N_D4, N_F4, N_G4,
      N_AS3, N_AS3, N_D5,  N_A4,  0,     N_GS4, N_G4,  N_F4,  N_D4, N_F4, N_G4,
      N_D4,  N_D4,  N_D5,  N_A4,  0,     N_GS4, N_G4,  N_F4,  N_D4, N_F4, N_G4,
      N_C4,  N_C4,  N_D5,  N_A4,  0,     N_GS4, N_G4,  N_F4,  N_D4, N_F4, N_G4,
      N_B3,  N_B3,  N_D5,  N_A4,  0,     N_GS4, N_G4,  N_F4,  N_D4, N_F4, N_G4,
      N_AS3, N_AS3, N_D5,  N_A4,  0,     N_GS4, N_G4,  N_F4,  N_D4, N_F4, N_G4,
      N_F4,  N_F4,  N_F4,  N_F4,  N_F4,  N_D4,  N_D4,  N_D4,  N_F4, N_F4, N_F4,
      N_G4,  N_GS4, N_G4,  N_F4,  N_D4,  N_F4,  N_G4,  0,     N_F4, N_F4, N_F4,
      N_G4,  N_GS4, N_A4,  N_C5,  N_A4,  N_D5,  N_D5,  N_D5,  N_A4, N_D5, N_C5,
      N_F4,  N_F4,  N_F4,  N_F4,  N_F4,  N_D4,  N_D4,  N_D4,  N_F4, N_F4, N_F4,
      N_F4,  N_D4,  N_F4,  N_E4,  N_D4,  N_C4,  0,     N_G4,  N_E4, N_D4, N_D4,
      N_D4,  N_D4,  N_F3,  N_G3,  N_AS3, N_C4,  N_D4,  N_F4,  N_C5, 0,    N_F4,
      N_D4,  N_F4,  N_G4,  N_GS4, N_G4,  N_F4,  N_D4,  N_GS4, N_G4, N_F4, N_D4,
      N_F4,  N_F4,  N_F4,  N_GS4, N_A4,  N_C5,  N_A4,  N_GS4, N_G4, N_F4, N_D4,
      N_E4,  N_F4,  N_G4,  N_A4,  N_C5,  N_CS5, N_GS4, N_GS4, N_G4, N_F4, N_G4,
      N_F3,  N_G3,  N_A3,  N_F4,  N_E4,  N_D4,  N_E4,  N_F4,  N_G4, N_E4, N_A4,
      N_A4,  N_G4,  N_F4,  N_DS4, N_CS4, N_DS4, 0,     N_F4,  N_D4, N_F4, N_G4,
      N_GS4, N_G4,  N_F4,  N_D4,  N_GS4, N_G4,  N_F4,  N_D4,  N_F4, N_F4, N_F4,
      N_GS4, N_A4,  N_C5,  N_A4,  N_GS4, N_G4,  N_F4,  N_D4,  N_E4, N_F4, N_G4,
      N_A4,  N_C5,  N_CS5, N_GS4, N_GS4, N_G4,  N_F4,  N_G4,  N_F3, N_G3, N_A3,
      N_F4,  N_E4,  N_D4,  N_E4,  N_F4,  N_G4,  N_E4,  N_A4,  N_A4, N_G4, N_F4,
      N_DS4, N_CS4, N_DS4,
  };
  int noteDurations[] = {
      16, 16, 8,  6,  32, 8,  8,  8,  16, 16, 16, 16, 16, 8,  6,  32, 8,  8,
      8,  16, 16, 16, 16, 16, 8,  6,  32, 8,  8,  8,  16, 16, 16, 16, 16, 8,
      6,  32, 8,  8,  8,  16, 16, 16, 16, 16, 8,  6,  32, 8,  8,  8,  16, 16,
      16, 16, 16, 8,  6,  32, 8,  8,  8,  16, 16, 16, 16, 16, 8,  6,  32, 8,
      8,  8,  16, 16, 16, 16, 16, 8,  6,  32, 8,  8,  8,  16, 16, 16, 16, 16,
      8,  6,  32, 8,  8,  8,  16, 16, 16, 16, 16, 8,  6,  32, 8,  8,  8,  16,
      16, 16, 16, 16, 8,  6,  32, 8,  8,  8,  16, 16, 16, 16, 16, 8,  6,  32,
      8,  8,  8,  16, 16, 16, 16, 16, 8,  6,  32, 8,  8,  8,  16, 16, 16, 16,
      16, 8,  6,  32, 8,  8,  8,  16, 16, 16, 16, 16, 8,  6,  32, 8,  8,  8,
      16, 16, 16, 16, 16, 8,  6,  32, 8,  8,  8,  16, 16, 16, 8,  16, 8,  8,
      8,  8,  4,  16, 8,  16, 8,  8,  8,  16, 16, 16, 16, 16, 8,  8,  16, 8,
      8,  8,  8,  8,  8,  8,  8,  16, 16, 16, 2,  8,  16, 8,  8,  8,  8,  4,
      16, 8,  16, 8,  8,  8,  8,  8,  16, 8,  16, 8,  8,  8,  8,  8,  8,  8,
      16, 8,  15, 8,  8,  2,  3,  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
      16, 8,  2,  16, 8,  16, 8,  16, 16, 16, 16, 16, 16, 8,  8,  8,  8,  8,
      8,  16, 16, 16, 2,  8,  8,  8,  8,  4,  4,  4,  4,  4,  4,  2,  8,  8,
      8,  8,  2,  2,  3,  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8,
      2,  16, 8,  16, 8,  16, 16, 16, 16, 16, 16, 8,  8,  8,  8,  8,  8,  16,
      16, 16, 2,  8,  8,  8,  8,  4,  4,  4,  4,  4,  4,  2,  8,  8,  8,  8,
      2,  1};

  unsigned int melody_len = sizeof(melody) / sizeof(melody[0]);

  unsigned int thisNote = 0;

  for (thisNote = 0; thisNote < melody_len; thisNote++) {
    unsigned int noteDuration = TEMPO / noteDurations[thisNote];
    unsigned int pauseBetweenNotes = noteDuration * 0.4;
    beep(melody[thisNote], noteDuration, pauseBetweenNotes);
    noBeep(30);

  }
}


/*
 *
 * En esta zona seria un buen lugar para incorporar interrupciones de botones
 * que permitan controlar la logica del reproductor
 *
 */

