#include <FastLED.h>

#pragma once

template<int LED_Strips, int Strip_Len>
class LED_Controller {
private:
  void pushChanges();
  void solvePowerRequirements();
  void animate();
protected:
  int pins[LED_Strips];
  int length;
  ESPIChipsets chipset;
  CRGB leds[LED_Strips][Strip_Len];
  int brightness;
public:
  LED_Controller();
  LED_Controller(ESPIChipsets chip, int *led_pins);


  void Turn_On(bool hard);
  void Turn_Off(bool hard);


  void SetColour(CRGB colour);
  void SetColour(CRGB *colours, int len);

  void SetBrightness(int brightness);
  void SetBrightness(int *brighnesses, int len);
};


template class LED_Controller<1, 1>;
template class LED_Controller<5, 3>;
template class LED_Controller<5, 4>;
template class LED_Controller<5, 5>;
template class LED_Controller<5, 6>;