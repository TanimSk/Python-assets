void Setup_pins(){
  Serial.begin(9600);
  pinMode(A0,INPUT);
  T0 = 25 + 273.15;
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void send_data(String phone_number, float body_temp, String Report){
  Serial.print("{ \"type\": \"data\", \"phone_number\": \"" + phone_number + "\", \"body_temp\": \"" + body_temp + "\", \"report\": \"" + Report + "\"}\n");
}

void play_audio(String audio_filename){
  Serial.print("{ \"type\": \"audio\", \"filename\": \"" + audio_filename + "\"}\n");
}

void enable_sensor(){
  Serial.print("{\"type\": \"sensor\"}\n");
}

void print_report(){
  Serial.print("{\"type\": \"print\"}\n");
}
