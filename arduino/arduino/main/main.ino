#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo1;//temp hand 11
Servo myservo2;//max3102 hand 10
Servo myservo3; //medicine hand 9
Servo myservo4; // glass hand 3

//tempeature
#define RT0 10000   // Ω
#define B 3977      // K
#define VCC 5    //Supply voltage
#define R 10000  //R=10KΩ
float RT, VR, ln, T0, Read;

//keypad
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {13, 12, 8, 7}; 
byte colPins[COLS] = {4, 2, A1, A2}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LiquidCrystal_I2C lcd(0x27,16,2);


//Sonar
#define echoPin 6
#define trigPin 5
float Temp = 0;
float duration;
float distance;


char key;
String Phone_number = "";
String Report = "";
String eye_check = "4854";
String seen_value = "";

float body_temperature = 0;

void setup(){
  Setup_pins();
  myservo1.attach(11);
  myservo2.attach(10);
  myservo3.attach(9);
  myservo4.attach(3);
  
  myservo1.write(0);  
  myservo2.write(0);
  myservo3.write(90);
  myservo4.write(0);
  delay(500);
  
  
  while(true){
    key = customKeypad.getKey();
     if (key == '1'){
      break;
     }
  }
}

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;
  
  if (distance < 65 && distance > 0){
    play_audio("1.wav"); //welcome audio
    
    delay(1000);
    lcd.print("Phone Number :  ");
    lcd.setCursor(1, 1);

    
    while(true){
      key = customKeypad.getKey();
     if(key){
       lcd.print(key);
       Phone_number += key;
       if(Phone_number.length() == 11){
         break;
       }
     } 
   }

    lcd.clear();
    play_audio("2.wav");  //ask for service and give option
    delay(1000);
    check_up();
    delay(5000);
  }
   delay(5); 
}

void check_up(){
  lcd.clear();
  lcd.print("Enter an Option:");
  lcd.setCursor(7, 1);
  while(true){
    key = customKeypad.getKey();
    if(key){
      lcd.print(key);
      delay(1000);
      break;
    }
  }
  lcd.clear();
  if(key == 'A'){
    lcd.print("Fever Checkup");
    play_audio("2.wav");
    myservo1.write(40);
    delay(500);
    for(int i = 0; i<100; i++){
        Read = analogRead(A0);                //Acquisition analog value Read
        Read = (5.00 / 1023.00) * Read;      //Conversion to voltage
        VR = VCC - Read;
        RT = Read / (VR / R);               //Resistance of RT
      
        ln = log(RT / RT0);
        Temp = (1 / ((ln / B) + (1 / T0))); //Temperature from sensor
      
        Temp = ((Temp - 273.15)*1.8)+41;    //Conversion to Farenheit   32
      Serial.println(Temp);
      delay(120);
    }
    lcd.clear();
    lcd.print("Body Temperature");
    lcd.setCursor(5, 1);
    lcd.print(Temp);
    if(Temp > 100){
      myservo3.write(0);
      delay(500);
      Report += "Napa - Each dose after 6 hours";
      myservo3.write(90);
      delay(500);
      play_audio("ksdmfksm.wav"); //Please receive your medicine audio
    }
  }
  
  else if(key == 'B'){
    lcd.clear();
    lcd.print("Cough Treatment");
    play_audio("vsd.wav");  //cough treatment audio
    myservo3.write(180);
    delay(500);
    Report += "\n Alatrol - One dose per day";
    myservo3.write(90);
    delay(500);
    play_audio("ksdmfksm.wav");//Please receive your medicine audio
  }

  else if(key == 'C'){
      play_audio("898.wav"); //eye glass ejection audio
      lcd.print("Eye Checkup");
      myservo4.write(35);
      delay(200);
      while(true){
        for(int c = 0; c < eye_check.length(); c++){
          while(true){
            key = customKeypad.getKey();
              if(key){
                seen_value += key;
                break; 
              }
            }
        }
        if(seen_value == eye_check){
          play_audio("mk.wav"); //correct glass audio
          lcd.clear();
          lcd.print("correct glass");
          break;
        }
        else{
          play_audio("sdfs.wav"); //take another glass
          lcd.clear();
          lcd.print("take another glass");
        }
      }
  }

  else if(key == 'D'){
    lcd.print("Heart Rate");
    enable_sensor();
    delay(100);
    play_audio("gd.wav"); // please put your hand
    myservo2.write(90);
    delay(200);
    while (Serial.available()){
      lcd.print(Serial.read());
      break;
    }
  }

  else if(key == '#'){
    lcd.print("Printing report");
    lcd.setCursor(0, 1);
    send_data(Phone_number, Temp, Report);
    delay(100);
    print_report();
    for(int cnt = 0; cnt < 10; cnt++){
      lcd.print(".");
      delay(1000);
    }
    return;
  }

  else{
    lcd.print("wrong key!");
    delay(1000);
    check_up();
  }

  play_audio("fd.wav"); // ask for further service
  while(true){
    key = customKeypad.getKey();
    if(key){
      if(key == '1'){
        check_up();
      }
      else{
        lcd.print("Printing report");
        lcd.setCursor(0, 1);
        send_data(Phone_number, Temp, Report);
        delay(100);
        print_report();
        for(int cnt = 0; cnt < 10; cnt++){
          lcd.print(".");
          delay(1000);
        }
        return;
      }
    }
  }
}

/*
customKeypad.getKey()
if (customKey){
    Serial.println(customKey);
  }

 lcd.print("Hello, world!");
 delay(1000);
  send_data("01760001377", 10, 1056, 5.55);
  delay(1000);
  play_audio("1.wav");

*/
