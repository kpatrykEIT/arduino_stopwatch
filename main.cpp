#include <Arduino.h>
#include <LiquidCrystal.h>

#define BUTTON 8
#define LED_RED 9
#define LED_GREEN 10

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

unsigned long interval = 60000;
unsigned long startTime = 0, elapsedTime = 0, displayTime = 0;
unsigned int m, h;
  

int buttonState = 0;
int buttonRead = 0;
int counting = true;


void startMenu();
void redLED();
void greenLED(int delayTime);

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  lcd.begin(16, 2); 
  Serial.begin(9600);

 
}

void loop() {

  
  
  buttonRead = digitalRead(BUTTON);
 

  if(buttonRead == 0){
    delay(300);
    startTime = millis();
    buttonState ++;
  }



  if(buttonState == 0){
    m = 0;
    h = 0;
    startMenu();
    redLED();
  }

  else if(buttonState == 1){
  
   elapsedTime = millis() - startTime;

   unsigned int ms = elapsedTime % 1000;
   unsigned int s = elapsedTime / 1000;
   

   if(millis() - startTime >= interval ){
    startTime = millis();
    elapsedTime = 0;
    m ++;
   }

   if(m == 60){
    m = 0;
    h ++;
   }

   if(h == 24){
    h = 0;
    m = 0;
   }


  lcd.setCursor(0, 1);
  lcd.print(h < 10 ? "0" : ""); 
  lcd.print(h);
  lcd.print(":");
  lcd.print(m < 10 ? "0" : ""); 
  lcd.print(m);
  lcd.print(":");
  lcd.print(s < 10 ? "0" : ""); 
  lcd.print(s);
  lcd.print(".");
  if (ms < 100) lcd.print("0");
  
  lcd.print(ms);
  greenLED(0);
  }

 
  else if(buttonState == 2){
    
   greenLED(150);
    
  }

  
  else if(buttonState > 2){
    
    buttonState = 0;

  }
 
}

void startMenu()
{
  
  lcd.setCursor(0,0);
  lcd.print("Stoper");
  lcd.setCursor(0,1);
  lcd.print("00:00:00:000");
}

void greenLED(int delayTime)
{
  
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  delay(delayTime);
  digitalWrite(LED_GREEN, LOW);
  delay(delayTime);
  digitalWrite(LED_GREEN, HIGH);
  
}

void redLED(){

  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
}
