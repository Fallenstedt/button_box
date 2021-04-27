
#ifndef BigSwitch_h
#define BigSwitch_h
#include "BigSwitchTypeDef.h"


class BigSwitch
{
private:
    uint8_t m_pin;
    uint8_t m_joybtn;
    uint8_t m_state;
 
public:
    BigSwitch(uint8_t pin, uint8_t joybtn);
    void Begin();
    void CheckButtonState(checkButtonHookFn fn);
};

#endif /* BigSwitch_h */
