#include "A_LED_controller.h"
#include <FastLED.h>

#pragma region Contructors

template<int LED_Strips, int Strip_Len>
LED_Controller<LED_Strips, Strip_Len>::LED_Controller() {
    FastLED.addLeds<WS2812B, 48>(this->leds[0], Strip_Len);
}

template<int LED_Strips, int Strip_Len>
LED_Controller<LED_Strips, Strip_Len>::LED_Controller(ESPIChipsets chip, int *led_pins) {
  for(int i = 0; i < LED_Strips; i++) {
    FastLED.addLeds<chip, 8>(this->leds[i], Strip_Len);

    for (int j=0; j<Strip_Len; j++) {
      this->leds[i][j]=CRGB::Black;
    }
  }

  FastLED.setBrightness(254);

  this->brightness = 128;
}

#pragma endregion


#pragma region Public

template<int LED_Strips, int Strip_Len>
void LED_Controller<LED_Strips, Strip_Len>::Turn_On(bool hard) {
  
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

template<int LED_Strips, int Strip_Len>
void LED_Controller<LED_Strips, Strip_Len>::Turn_Off(bool hard) {
  
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


template<int LED_Strips, int Strip_Len>
void LED_Controller<LED_Strips, Strip_Len>::SetColour(CRGB colour) {
  for(int i=0; i<LED_Strips; i++) {
    for(int j=0; j<Strip_Len; j++) {
      this->leds[i] = colour;
    }
  }
  this->pushChanges();
}
template<int LED_Strips, int Strip_Len>
void LED_Controller<LED_Strips, Strip_Len>::SetColour(CRGB *colours, int len) {
}

template<int LED_Strips, int Strip_Len>
void LED_Controller<LED_Strips, Strip_Len>::SetBrightness(int brightness) {
  for(int i=0; i<LED_Strips; i++) {
    for(int j=0; j<Strip_Len; j++) {
      this->leds[i][j].maximizeBrightness();
      this->leds[i] %= brightness;
    }
  }
  this->pushChanges();
}
template<int LED_Strips, int Strip_Len>
void LED_Controller<LED_Strips, Strip_Len>::SetBrightness(int *brighnesses, int len) {
}


#pragma endregion


#pragma region Private

template<int LED_Strips, int Strip_Len>
void LED_Controller<LED_Strips, Strip_Len>::pushChanges() {
  this->solvePowerRequirements();

  FastLED.show();
}


template<int LED_Strips, int Strip_Len>
void LED_Controller<LED_Strips, Strip_Len>::solvePowerRequirements() {
  FastLED.setBrightness(254);
}

template<int LED_Strips, int Strip_Len>
void LED_Controller<LED_Strips, Strip_Len>::animate() {
}

#pragma endregion