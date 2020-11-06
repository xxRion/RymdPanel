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
  pinMode(A0, OUTPUT);  //54
  pinMode(A1, OUTPUT);  //55
  pinMode(A2, OUTPUT);  //56
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT);  //63
  pinMode(A10, OUTPUT); //64
  pinMode(A11, OUTPUT); //65

  //10 st strömbrytare, pins default to inputs,
  //but I want pullup-resistor enabled
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
  int buttonStates[9];
  int buttonStatePins[] = {
    53, 51, 49, 47, 45, 43, 41, 39, 37, 35
  };
  int buttonLedPins[] = {
    52, 50, 48, 46, 44, 42, 40, 38, 36, 34
  };
  int buttonCount = 10;
  int redPins[] = {
    //10 and 11 accidentaly connected in reverse
    A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A11, A10
  };
  int redCount = 12;

  for (int thisPin = 0; thisPin < redCount; thisPin++) {
    led_blink(redPins[thisPin]);
  }

  for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
    buttonStates[thisPin] = digitalRead(buttonStatePins[thisPin]);
    led_blink(buttonLedPins[thisPin]);
  }

  for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
    if (buttonStates[thisPin] == LOW) led_flash(buttonLedPins[thisPin]);
  }

  // Something breaks if we led_blink(buttonLedPins[buttonCount-1])
  // two times in a row. Skip it by starting with -2 offset.
  for (int thisPin = buttonCount - 2; thisPin >= 0; thisPin--) {
    led_blink(buttonLedPins[thisPin]);
  }
}
