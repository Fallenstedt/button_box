#include "Arduino.h"
#include "BigSwitchTypeDef.h"
#include "BigSwitch.h"

BigSwitch::BigSwitch(uint8_t pin, uint8_t joybtn) {
    m_pin = pin;
    m_joybtn = joybtn;
    pinMode(m_pin, INPUT);
}

void BigSwitch::Begin() {
      pinMode(m_pin, INPUT);
}

void BigSwitch::CheckButtonState( checkButtonHookFn hook) {
    byte s = digitalRead(m_pin);
    if (s != m_state) {
      m_state = s;
      hook(m_joybtn, m_state);
      delay(1);          
    } 
}
