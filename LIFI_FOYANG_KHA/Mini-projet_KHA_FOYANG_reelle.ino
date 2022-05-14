// Sur carte réelle
// auteurs : FOYANG Joël , KHA Alexandre
// groupe : 7
#include <TimerOne.h>
#include <LiquidCrystal.h>
#include <analogComp.h>
const byte pinLedRed =37; // set pin number for red LED
const byte pinBP = 18 ;
const byte pinLedGreen = 36;
const byte pinPhotoResistance = A0;
int iBP;
int but_Int;
const byte rs = 12;
const byte enable = 11;
const byte d4 = 5;
const byte d5 = 4;
const byte d6 = 3;
const byte d7 = 2;
char car;
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);
int ascii;
int tcar;
int delta_t = 400;
int t1;
int t0;
bool signal_recu = false;
int char_pos=0;
int ascii2;
int T;
int nb_car_read = 0;



void setup() {
  // put your setup code here, to run once:
pinMode ( pinLedRed , OUTPUT ); // set red LED pin as output
pinMode(pinLedGreen, OUTPUT);
analogComparator.setOn(INTERNAL_REFERENCE, A0);
analogComparator.enableInterrupt(photo_mesure, FALLING);
Serial.begin (115200); // setup the terminal monitor
Serial.println (" Ready " ); // ready to run
lcd.begin(16,2);
lcd.setCursor(0,0);
but_Int = digitalPinToInterrupt(pinBP);
attachInterrupt(but_Int, Clear, RISING);

}


void loop() {
  // put your main code here, to run repeatedly:
  if (nb_car_read ==0){
    t0=millis();
  }
  //if (nb_car_read ==17) {
  // nb_car_read = 0;
  //  char_pos = 0;
  //  lcd.clear();
  // }
  if (Serial.available()>0) {
    digitalWrite(pinLedGreen, LOW);
    lcd.setCursor(char_pos,0);
    car = Serial.read();
    ascii = int(car);
    ascii2 = 4*ascii;
    tcar = ascii2;
    nb_car_read ++;
    lcd.print(car);
    digitalWrite(pinLedRed, HIGH);
    delay(delta_t);
    digitalWrite(pinLedRed, LOW);
    delay(tcar);
  }
  if (Serial.available()==0){
    digitalWrite(pinLedGreen, HIGH);
    nb_car_read =0;
  }
  if (signal_recu){
      t1 = millis();
      lcd.setCursor(char_pos, 1);
      T = (t1-t0-delta_t)/4;
      lcd.print(char(T));
     //Serial.println(char_pos);
     //Serial.println(T);
     //Serial.println(char(T));
     //Serial.println();
      signal_recu = false;
    
    t0 = t1;
    char_pos ++;
    }
   }

void Clear() {
  lcd.clear();
  char_pos = 0;
  nb_car_read = 0;
  
}

void photo_mesure(){
  signal_recu = true;
  
  
}
