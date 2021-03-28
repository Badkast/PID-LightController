#include <FastLED.h>
#include <ADC.h>
#include <ADC_util.h>
#include <AccelStepper.h>

#define LED_PIN     12
#define NUM_LEDS    7

long previousMillis = 0;  
long interval = 1000; 

int left = HIGH;// We define PinDirection with left and right
int right = LOW;
int pinDirection = 13; // Define pindirection GPIO as pin 13
int SetSpeed = 100  ;  // Change speed of motor here so dont have to scroll through program all the time

const int setPoint = 3500;

CRGB leds[NUM_LEDS];

AccelStepper Zaxis(1, 14, 1);

int led = 0; // testLED

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(38400);
 
  pinMode(pinDirection,OUTPUT);
  Zaxis.setMaxSpeed(10000);  
  
  
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
//  fill_solid( leds, NUM_LEDS, CRGB(255,255,255));

  leds[0] = CRGB(255, 255, 255);
  FastLED.show();
  delay(1);
  leds[1] = CRGB(255, 255, 255);
  FastLED.show();
  delay(1);
  leds[2] = CRGB(255, 255, 255);
  FastLED.show();
  delay(1);
  leds[3] = CRGB(255, 255, 255);
  FastLED.show();
  delay(1);
  leds[4] = CRGB(255, 255, 255);
  FastLED.show();
  delay(500);
  leds[5] = CRGB(255, 255, 255);
  FastLED.show();
  delay(1);
  leds[6] = CRGB(255, 255, 255);
  FastLED.show();
  delay(1);
  
//  digitalWrite(pinDirection,left); 
//  Zaxis.setSpeed(SetSpeed);    
//  Zaxis.runSpeed();
  
}
void loop() {
  analogReadResolution(12);
  int avg =analogRead(A1) + analogRead(A2)+ analogRead(A3)+ analogRead(A4)+ analogRead(A5)+ analogRead(A6);
  
  if (avg > setPoint){
    digitalWrite(pinDirection,left); 
    Zaxis.runSpeed();
    Zaxis.setSpeed(SetSpeed); 
    digitalWrite(led,HIGH);
  }
  else if(avg < setPoint){
    digitalWrite(pinDirection,right);
    Zaxis.runSpeed();
    Zaxis.setSpeed(SetSpeed); 
    digitalWrite(led,LOW);
  }
  else{
    Zaxis.stop();
  }

  unsigned long currentMillis = millis();        
  if(currentMillis - previousMillis > interval) {
    Serial.println(avg);
    previousMillis = currentMillis;   
  
  }
}
