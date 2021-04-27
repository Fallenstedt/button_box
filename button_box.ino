#include <Keypad.h>
#include <Joystick.h>

//DEFINITIONS
#define NUMBUTTONS 16 //replace "?"with number of buttong you are using
#define NUMROWS 4 //replace "?" with number of rows you have
#define NUMCOLS 4 //replace "?" with number of columns you have

// BIG BUTTN
#define BIG_SWITCH_PIN 12
byte BIG_SWITCH_STATE = LOW;

//BUTTON MATRIX
//first change number of rows and columns to match your button matrix,
//then replace all "?" with numbers (starting from 0)
byte buttons[NUMROWS][NUMCOLS] = {
  {1, 2, 3, 4},
  {5, 6, 7, 8},
  {9, 10, 11, 12},
  {13, 14, 15, 16}
};

//BUTTON MATRIX PART 2
byte rowPins[NUMROWS] = {2, 3, 4, 5}; //change "?" to the pins the rows of your button matrix are connected to
byte colPins[NUMCOLS] = {6, 7, 8, 9}; //change "?" to the pins the rows of your button matrix are connected to

Keypad buttbx = Keypad( makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS);

//JOYSTICK SETTINGS
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_GAMEPAD,
                   18, //number of buttons
                   0, //number of hat switches
                   //Set as many axis to "true" as you have potentiometers for
                   false, // y axis
                   false, // x axis
                   false, // z axis
                   false, // rx axis
                   false, // ry axis
                   false, // rz axis
                   false, // rudder
                   false, // throttle
                   false, // accelerator
                   false, // brake
                   false); // steering wheel


void setup() {
  Serial.begin(9600);
  Joystick.begin();
  pinMode(BIG_SWITCH_PIN, INPUT);
}

void loop() {
  CheckAllButtons();
}


void CheckAllButtons(void) {
  byte s = digitalRead(BIG_SWITCH_PIN);
  if (s != BIG_SWITCH_STATE) {
    BIG_SWITCH_STATE = s;
    Joystick.setButton(17, BIG_SWITCH_STATE);
    delay(1);
    
  }
  
  if (buttbx.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++)
    {
      if ( buttbx.key[i].stateChanged )
      {
        switch (buttbx.key[i].kstate) {
          case PRESSED:
          case HOLD:
            Serial.println("press");
            Joystick.setButton(buttbx.key[i].kchar, 1);
            break;
          case RELEASED:
          case IDLE:
            Joystick.setButton(buttbx.key[i].kchar, 0);
            break;
        }
      }
    }
  }
}
