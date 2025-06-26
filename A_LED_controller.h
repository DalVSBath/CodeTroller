#include <FastLED.h>

#pragma once

template<int... Pins>
class LED_Controller {
private:
  static constexpr std::size_t count = sizeof...(Pins);
  static constexpr std::array<int, count> value{ Pins... };

  void pushChanges();
  void solvePowerRequirements();
  void animate();
  void reset();
protected:
  int LED_Strips, Strip_Lengths;

  CRGB **leds;
  CRGB **existingState;

  int brightness;
public:
  LED_Controller();
  LED_Controller(int *led_pins);


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