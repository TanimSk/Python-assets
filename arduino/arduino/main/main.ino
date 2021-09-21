char key;
String Phone_number = "";

void setup(){
  Setup_pins();
  while(true){
    key = customKeypad.getKey();
     if (customKey == '1'){
      break;
     }
  }
}


void loop(){
  got_patient(65){
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
    play_audio("1.wav");  //ask for service
    
    
  }
}

void check_up(){
  
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
