/*** Globals ***/
int delay_t=1000/12; //1 sekund delat med 12 lampor
int buttonStatePins[] = { 53, 51, 49, 47, 45, 43, 41, 39, 37, 35 };
int buttonLedPins[]   = { 52, 50, 48, 46, 44, 42, 40, 38, 36, 34 };
int buttonCount = sizeof(buttonLedPins)/sizeof(buttonLedPins[0]);
//A10 and A11 accidentaly connected in reverse
int redPins[] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A11, A10 };
int redCount = sizeof(redPins)/sizeof(redPins[0]);
int KeyStartPin = 9;
int KeyOnPin = 8;

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

void led_on_time(int led, int time) {
  digitalWrite(led, HIGH);
  delay(delay_t*time);
  digitalWrite(led, LOW);
  delay(delay_t);
}

void flash_ring() {
  int skip = 3;
  for (int thisPin = 0; thisPin < redCount; thisPin++) {
    if (thisPin % skip == 0) led_flash(redPins[thisPin]);
  }
}

void system_test() {
  int buttonStates[buttonCount];

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

int pressed_button_pin () {
  int buttonStates[buttonCount];
  while (true) {
    for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
      buttonStates[thisPin] = digitalRead(buttonStatePins[thisPin]);
    }
    for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
      if (buttonStates[thisPin] == LOW) {
        return(buttonLedPins[thisPin]);
      }
    }
  }
}

void simon_says () {
  // Light up random button, wait for user to do the same
  // Keep adding more and more buttons until user is unable
  // to replay the entire sequence.
  int maxsequence = 100;
  int sequence[maxsequence];
  int seqpos = 0;
  int flashtime = 5;

  // Game ends if you reach 100
  while (seqpos < maxsequence) {
    //Randomly select next button for sequence
    sequence[seqpos] = buttonLedPins[(int)random(buttonCount)];
    // Show current sequence
    for (int thisPos = 0; thisPos <= seqpos; thisPos++) {
      led_on_time(sequence[thisPos], flashtime);
    }
    // Read user input
    for (int thisPos = 0; thisPos <= seqpos; thisPos++) {
      // Blink if correct light selected
      if (pressed_button_pin() == sequence[thisPos]) {
        led_on_time(sequence[thisPos], flashtime);
      // "Die" if wrong one is pushed
      } else {
        flash_ring();
        return;
      }
    }
    seqpos++;
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

  // Start key pins
  pinMode(KeyStartPin, INPUT_PULLUP);
  pinMode(KeyOnPin, INPUT_PULLUP);

  //10 st led i strömbrytare
  for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
    pinMode(buttonLedPins[thisPin], OUTPUT);
  }

  system_test();
}

void loop() {
  int buttonStates[buttonCount];
  for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
    buttonStates[thisPin] = digitalRead(buttonStatePins[thisPin]);
  }
  for (int thisPin = 0; thisPin < buttonCount; thisPin++) {
    if (buttonStates[thisPin] == LOW) simon_says();
  }
  if (digitalRead(KeyOnPin) == LOW) led_blink(redPins[5]);
  if (digitalRead(KeyStartPin) == LOW) {
    led_blink(redPins[7]);
    system_test();
  }
}
