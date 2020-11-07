/*** Globals ***/
int delay_t=1000/12; //1 sekund delat med 12 lampor
int buttonStatePins[] = { 53, 51, 49, 47, 45, 43, 41, 39, 37, 35  };
int buttonLedPins[]   = { 52, 50, 48, 46, 44, 42, 40, 38, 36, 34 };
int buttonCount = sizeof(buttonLedPins)/sizeof(buttonLedPins[0]);
//A10 and A11 accidentaly connected in reverse
int redPins[] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A11, A10 };
int redCount = sizeof(redPins)/sizeof(redPins[0]);

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
  //12 st röda led i en cirkel
  for (int thisPin = 0; thisPin < redCount; thisPin++) {
    pinMode(redPins[thisPin], OUTPUT);
  }

  //10 st strömbrytare, pins default to inputs, but I want pullup-resistor enabled
  for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
    pinMode(buttonStatePins[thisPin], INPUT_PULLUP);
  }

  //10 st led i strömbrytare
  for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
    pinMode(buttonLedPins[thisPin], OUTPUT);
  }
}

void system_test() {
  int buttonStates[9];

  for (int thisPin = 0; thisPin < redCount; thisPin++) {
    led_blink(redPins[thisPin]);
  }

  for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
    led_blink(buttonLedPins[thisPin]);
    buttonStates[thisPin] = digitalRead(buttonStatePins[thisPin]);
  }

  for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
    if (buttonStates[thisPin] == LOW) led_flash(buttonLedPins[thisPin]);
  }

  for (int thisPin = buttonCount - 1; thisPin >= 0; thisPin--) {
    led_blink(buttonLedPins[thisPin]);
  }
}

void loop() {
  int buttonStates[9];
  for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
    buttonStates[thisPin] = digitalRead(buttonStatePins[thisPin]);
  }
  for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
    if (buttonStates[thisPin] == LOW) system_test();
  }
}
