#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//temperature
#define RT0 10000   // Ω
#define B 3977      // K
float a=A0;
#define VCC 5    //Supply voltage
#define R 10000  //R=10KΩ
float RT, VR, ln, Temp, T0, Read;

//ultrasonic
#define echoPin 2
#define trigPin 3
long duration;
int distance;

//keypad
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


//lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

void Setup_pins(){
  Serial.begin(9600);
  pinMode(A0,INPUT);
  T0 = 25 + 273.15;
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  lcd.begin();
  lcd.backlight();
}


bool got_patient(float dist){
  while(true){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH);
  
    distance = duration * 0.034 / 2;
    if(distance >= dist){
      return true;
    }
  }
}


float get_temperature(){
  Read = analogRead(A0);                //Acquisition analog value Read
  Read = (5.00 / 1023.00) * Read;      //Conversion to voltage
  VR = VCC - Read;
  RT = Read / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  Temp = (1 / ((ln / B) + (1 / T0))); //Temperature from sensor

  Temp = ((Temp - 273.15)*1.8)+32;    //Conversion to Farenheit

  return Temp;
}


void send_data(String phone_number, float body_temp, float oxygen_level, float heart_rate){
  Serial.print("[\"data\", \"" + phone_number + "\", " + body_temp + ", " + oxygen_level + ", " + heart_rate + "]\n");
}

void play_audio(String audio_filename){
  Serial.print("[\"audio\", \"" + audio_filename + "\"]\n");
}
