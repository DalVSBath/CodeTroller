#include "A_LED_controller.h"
#include <FastLED.h>

#pragma region Contructors

template<int... Pins>
LED_Controller<Pins>::LED_Controller() {
  this->LED_Strips = 1;
  this->Strip_Lengths = 1;

  this->reset();
}

template<int... Pins>
LED_Controller<Pins>::LED_Controller(int *led_pins) {

}

template<int... Pins>
void LED_Controller<Pins>::reset() {
  this->leds = malloc(LED_Strips * sizeof(CRGB *));
  this->existingState = malloc(LED_Strips * sizeof(CRGB *));
  for (int i=0; i<LED_Strips; i++) {
    this->leds[i] = malloc(Strip_Lengths * sizeof(CRGB));
    this->existingState[i] = malloc(Strip_Lengths * sizeof(CRGB));
  }

  for(int i = 0; i < LED_Strips; i++) {
    FastLED.addLeds<WS2812B, value[i]>(this->leds[i], Strip_Len);

    for (int j=0; j<Strip_Len; j++) {
      this->leds[i][j]=CRGB::Black;
    }
  }

  FastLED.setBrightness(254);

  this->brightness = 128;
}

#pragma endregion


#pragma region Public

template<int... Pins>
void LED_Controller<Pins>::Turn_On(bool hard) {
  
  for(int i = 0; i < LED_Strips; i++) {
    for (int j=0; j<Strip_Len; j++) {
      this->leds[i][j]=CRGB::White;
    }

    if(!hard) {
      this->pushChanges();
      delay(380);
    }
  }

  this->pushChanges();
}

template<int... Pins>
void LED_Controller<Pins>::Turn_Off(bool hard) {
  
  for(int i = 0; i < LED_Strips; i++) {
    for (int j=0; j<Strip_Len; j++) {
      this->leds[i][j]=CRGB::Black;
    }

    if(!hard) {
      this->pushChanges();
      delay(380);
    }
  }

  this->pushChanges();
}

template<int... Pins>
void LED_Controller<Pins>::SetColour(CRGB colour) {
  for(int i=0; i<LED_Strips; i++) {
    for(int j=0; j<Strip_Len; j++) {
      this->leds[i][j] = colour;
    }
  }
  this->pushChanges();
}
template<int... Pins>
void LED_Controller<Pins>::SetColour(CRGB *colours, int len) {
}

template<int... Pins>
void LED_Controller<Pins>::SetBrightness(int brightness) {
  if(brightness == 0) brightness = 1;
  
  for(int i=0; i<LED_Strips; i++) {
    for(int j=0; j<Strip_Len; j++) {
      this->leds[i][j] = this->existingState[i][j];
      this->leds[i][j] %= brightness;
    }
  }
  this->pushChanges();
}
template<int... Pins>
void LED_Controller<Pins>::SetBrightness(int *brighnesses, int len) {
}


#pragma endregion


#pragma region Private

template<int... Pins>
void LED_Controller<Pins>::pushChanges() {
  this->solvePowerRequirements();

  FastLED.show();
}


template<int... Pins>
void LED_Controller<Pins>::solvePowerRequirements() {
  FastLED.setBrightness(254);
}

template<int... Pins>
void LED_Controller<Pins>::animate() {
}

#pragma endregion