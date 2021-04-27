#include <Keypad.h>
#include <Joystick.h>
#include "BigSwitch.h"


//DEFINITIONS
#define NUMROWS 4 
#define NUMCOLS 4 
#define BIG_SWITCH_PIN 12


//BUTTON MATRIX
byte buttons[NUMROWS][NUMCOLS] = {
  {1, 2, 3, 4},
  {5, 6, 7, 8},
  {9, 10, 11, 12},
  {13, 14, 15, 16}
};
byte rowPins[NUMROWS] = {2, 3, 4, 5}; 
byte colPins[NUMCOLS] = {6, 7, 8, 9}; 

Keypad buttbx = Keypad( makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS);

//JOYSTICK SETTINGS
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_GAMEPAD,
                   18, //number of buttons
                   0, //number of hat switches
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



BigSwitch bigSwitch = BigSwitch(BIG_SWITCH_PIN, 17);


void setup() {
  Joystick.begin();
  bigSwitch.Begin();
}

void loop() {
  CheckAllButtons();
}


void CheckAllButtons(void) {

  bigSwitch.CheckButtonState(setBtn);
  
  if (buttbx.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++)
    {
      if ( buttbx.key[i].stateChanged )
      {
        switch (buttbx.key[i].kstate) {
          case PRESSED:
          case HOLD:
            setBtn(buttbx.key[i].kchar, 1);
            
            break;
          case RELEASED:
          case IDLE:
            setBtn(buttbx.key[i].kchar, 0);
            break;
        }
      }
    }
  }
}

void setBtn(uint8_t button, uint8_t value) {
  Joystick.setButton(button, value);
}
