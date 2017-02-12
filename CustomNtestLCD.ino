/*
  CustomCharacter.ino
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.
  Author:Loovee
  2013-9-18

  modif Xav1er 2017-02-12  --> Custom N Test it !
  
*/

#include <Wire.h>
#include "rgb_lcd.h"

/* is connected on DIGITAL :
                ========
 2  : input : Key3 = STOP )
 3  : input : Key4 = -1   )__( KEYPAD-1x4-MEM )
 4  : input : Key1 = +1   )
 5  : input : Key2 = GO   )
 
 */
  //declaration des * BOUTONS et VARIABLES *
  
  boolean Kon, K1 , K2 , K3 , K4, NouvelAppui , AppuiLong ;
  boolean clock = true;
  unsigned long  DebutAppui; 
  int i=0, j, k; 

  //  init LCD
  rgb_lcd lcd;
  
  // make some custom characters:

byte DegreC[8] = {
      0b00000,
      0b10000,
      0b00111,
      0b01000,
      0b01000,
      0b01000,
      0b01000,
      0b00111,
};

byte UP[8] = {
      0b00100,
      0b01110,
      0b11111,
      0b10101,
      0b00100,
      0b00100,
      0b00100,
      0b00100,
};

byte DOWN[8] = {
      0b00100,
      0b00100,
      0b00100,
      0b00100,
      0b10101,
      0b11111,
      0b01110,
      0b00100,
};
byte ROUE1[8] = {
      0b00000,
      0b01110,
      0b11101,
      0b11001,
      0b11001,
      0b11001,
      0b01110,
      0b00000,
};
byte ROUE2[8] = {
      0b00000,
      0b01110,
      0b11001,
      0b11001,
      0b11001,
      0b11101,
      0b01110,
      0b00000,
};
byte ROUE3[8] = {
      0b00000,
      0b01110,
      0b10011,
      0b10011,
      0b10011,
      0b10111,
      0b01110,
      0b00000,
};
byte ROUE4[8] = {
      0b00000,
      0b01110,
      0b10111,
      0b10011,
      0b10011,
      0b10011,
      0b01110,
      0b00000,
};
byte VALID[8] = {
      0b00000,
      0b00001,
      0b00001,
      0b11010,
      0b01010,
      0b01100,
      0b01100,
      0b01000,
};


void setup() 
{


//on initialise les boutons (entrées normalement haute R = 20k
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP); 
  pinMode(5, INPUT_PULLUP);
  
  
    lcd.begin(16, 2);
 #if 1   
    // create new characters
    lcd.createChar(0, ROUE1);
    lcd.createChar(1, ROUE2);
    lcd.createChar(2, ROUE3);
    lcd.createChar(3, ROUE4);
    lcd.createChar(4, DegreC);
    lcd.createChar(5, UP);
    lcd.createChar(6, DOWN);
    lcd.createChar(7, VALID);
#endif 
    // set up the lcd's number of columns and rows:
        
}

void loop() 
{

    // --------- CLAVIER 4 touches

  K1 = ! digitalRead(4);
  K2 = ! digitalRead(5);
  K3 = ! digitalRead(2);
  K4 = ! digitalRead(3);
  NouvelAppui = false;

   if ((!K1) && (!K2) && (!K3) && (!K4))  
      { Kon = false; AppuiLong = false;};               // si aucun bouton appuyé : raz des push
  
   if ((K1) or (K2) or (K3) or (K4))                   // si un bouton appuyé :
      { 
      if (!Kon){NouvelAppui = true; DebutAppui = millis();};
      Kon = true;
      if  ( (millis()- DebutAppui) > 1500 ){AppuiLong = true;};    // appui maintenu si 2s sans relacher :
      };

if ((NouvelAppui) or (AppuiLong))
    {
   if (K1) {clock= false; };
   if ((K1) && (AppuiLong)) {i=0;};
   if (K2) {i=--i;};
   if (K3) {i=++i;};
   if (K4) {clock= true; };
   };
   if (clock) {i=++i; };
   if (i==256) {i=0; };
   if (i==-1) {i=255; };   

      j = i % 4;
      k = i % 8;
      lcd.setCursor(0, 0); 
      lcd.write(j); 
      lcd.write("  CAR.num:    "); 
      lcd.setCursor(12, 0);  
      lcd.print(i);
      
     lcd.setCursor(2 * k, 1); 
     lcd.write("  __");
     lcd.setCursor(2 * k, 1);  
     lcd.write(i); 


     
     lcd.setCursor(12, 0);  
     lcd.write("   "); 
     lcd.setCursor(12, 0);  
     lcd.print(i); 

 delay(150);      
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
