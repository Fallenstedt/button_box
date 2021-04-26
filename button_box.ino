// https://github.com/MHeironimus/ArduinoJoystickLibrary
#include <Joystick.h>

//https://playground.arduino.cc/Code/Keypad/
#include <Keypad.h>

// Big Switch
const byte BIG_SWITCH_PIN = 13;
byte BIG_SWITCH_STATE = LOW;


// Keypad
const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  {'a', 'b', 'c', 'd'},
  {'e', 'f', 'g', 'h'},
  {'i', 'j', 'k', 'l'},
  {'m', 'n', 'o', 'p'},
};
byte rowPins[rows] = {2, 3, 4, 5};
byte colPins[cols] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

//initialize an Joystick with 16 buttons;
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_JOYSTICK, 16, 0,
                   false, false, false, false, false, false,
                   false, false, false, false, false);


void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:

  Joystick.begin();
  pinMode(BIG_SWITCH_PIN, INPUT);
}

void loop() {

  CheckAllButtons();

}


void CheckAllButtons(void) {
  if (!keypad.getKeys()) {
    return;
  }

  // Button Grid
  for (int i = 0; i < LIST_MAX; i++) {
    if (keypad.key[i].stateChanged) {
      switch (keypad.key[i].kstate) {
        case PRESSED:
        case HOLD:
          Joystick.setButton(keypad.key[i].kchar, 1);
          Serial.println(keypad.key[i].kchar);
          break;
        case RELEASED:
        case IDLE:
          Joystick.setButton(keypad.key[i].kchar, 0);
          break;
          
      }
    }
  }

      // Big Switch
  byte s = digitalRead(BIG_SWITCH_PIN);
  if (s != BIG_SWITCH_STATE) {
    BIG_SWITCH_STATE = s;
    delay(1);
    Serial.println(BIG_SWITCH_STATE);
  }

}
