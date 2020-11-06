int delay_t=1000/12; //1 sekund delat med 12 lampor

void led_blink(int led) {
  digitalWrite(led, HIGH);
  delay(delay_t);
  digitalWrite(led, LOW);
}

void led_flash(int led) {
  for(int i=0;i<10; i++){
    digitalWrite(led, HIGH);
    delay(delay_t);
    digitalWrite(led, LOW);
    delay(delay_t);    
  }
}

void setup() {
/* * * * * 
  Serial.begin(9600);
  Serial.print("A2=");
  Serial.println(A2);
* * * * */
  //12 st röda led i en cirkel
  pinMode(A0, OUTPUT); //54
  pinMode(A1, OUTPUT); //55
  pinMode(A2, OUTPUT); //56
  pinMode(A3, OUTPUT); 
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT);  //63
  pinMode(A10, OUTPUT); //64
  pinMode(A11, OUTPUT); //65

  //10 st strömbrytare, pins default to inputs, but I want pullup-resistor enabled
  pinMode(53, INPUT_PULLUP);
  pinMode(51, INPUT_PULLUP);
  pinMode(49, INPUT_PULLUP);
  pinMode(47, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
  pinMode(43, INPUT_PULLUP);
  pinMode(41, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);

  //10 st led i strömbrytare
  pinMode(52, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(34, OUTPUT);
  
}

void loop() {
  int buttonState1;
  int buttonState2;
  int buttonState3;
  int buttonState4;
  int buttonState5;
  int buttonState6;
  int buttonState7;
  int buttonState8;
  int buttonState9;
  int buttonState10;
  
  led_blink(A0);
  led_blink(A1);
  led_blink(A2);
  led_blink(A3);
  led_blink(A4);
  led_blink(A5);
  led_blink(A6);
  led_blink(A7);  
  led_blink(A8);
  led_blink(A9);
  led_blink(A11);
  led_blink(A10);
  
  buttonState1 = digitalRead(53);
  led_blink(52);
  buttonState2 = digitalRead(51);
  led_blink(50);
  buttonState3 = digitalRead(49);
  led_blink(48);
  buttonState4 = digitalRead(47);
  led_blink(46);
  buttonState5 = digitalRead(45);
  led_blink(44);
  buttonState6 = digitalRead(43);
  led_blink(42);
  buttonState7 = digitalRead(41);
  led_blink(40);
  buttonState8 = digitalRead(39);
  led_blink(38);
  buttonState9 = digitalRead(37);
  led_blink(36);
  buttonState10 = digitalRead(35);
  led_blink(34);
  if (buttonState1 == LOW) led_flash(52);
  if (buttonState2 == LOW) led_flash(50);
  if (buttonState3 == LOW) led_flash(48);
  if (buttonState4 == LOW) led_flash(46);
  if (buttonState5 == LOW) led_flash(44);
  if (buttonState6 == LOW) led_flash(42);
  if (buttonState7 == LOW) led_flash(40);
  if (buttonState8 == LOW) led_flash(38);
  if (buttonState9 == LOW) led_flash(36);
  if (buttonState10 == LOW) led_flash(34);

  led_blink(34);
  led_blink(36);
  led_blink(38);
  led_blink(40);
  led_blink(42);
  led_blink(44);
  led_blink(46);
  led_blink(48);
  led_blink(50);
  led_blink(52);
  
}
